/**
 * @file createTasks.cpp
 * @author Smart-Fridge
 * @brief Define the private and public functions
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <ArduinoJson.h>
#include "createTasks.h"
#include "boardConfig.h"
#include "weightSensor.h"
#include "halSwitch.h"
#include "createTasks.h"
#include "buzzer.h"

#define QUEUE_LENGTH 10

// PRIVATE MEMBERS

// Time to wait for to check if door still is open 
// Set time of delay to 60 seconds (Current timer is set to 6 seconds for testing) 
static const TickType_t dim_delay = 6000 / portTICK_PERIOD_MS;

// Name of the software timer handler
static TimerHandle_t one_shot_timer = NULL;

// Send data from producer to consumer
QueueHandle_t msg_queue;


/**
 * @brief store the sensor data
 *
 */
struct sensorData
{
    float objectWeight;
    bool switchState;
    bool alarmStatus;
};

// PRIVATE FUNCTION DECLARTATIONS

/**
 * @brief Get the Weight Data object
 *
 * @param pvParameters
 */
static void getSensorData(void *pvParameters);

/**
 * @brief Send the data to the Pi
 *
 * @param pvParameters
 */
static void sendData(void *pvParameters);

/**
 * @brief Turn on the Buzzer with a toggle of 1 second
 *        Blink the LEDs to indicate the door is open for too long
 *
 * @param [in] xTimer Time Handler to active a set timer (DEFAULT AT 0)
 */
static void timeDoorCheck(TimerHandle_t xTimer);

/**
 * @brief Activates the buzzer if the door is left open for more than 60 seconds
 *
 */
// static void activateAlarm(void *pvParameters);

// PRIVATE FUNCTION DEFINITIONS
void getSensorData(void *pvParameters)
{
    (void)pvParameters;

    sensorData sendSensorValues;

    sendSensorValues.alarmStatus = false;

    for (;;)
    {

        sendSensorValues.switchState = get_halState();

        // If the door is open get object weight and start timer
        if (sendSensorValues.switchState)
        {
            // Serial.println(sendSensorValues.switchState);
            // Serial.println(sendSensorValues.objectWeight);

            sendSensorValues.objectWeight = get_Weight();

            // Check if the timer has not already been started
            if (!xTimerIsTimerActive(one_shot_timer))
            {
                // Start timer
                Serial.println("Start Timer");
                xTimerStart(one_shot_timer, portMAX_DELAY);
            }
        }

        else
        {
            // Reset alarm status so the buzzer is not activated 
            sendSensorValues.alarmStatus = false;
        }

        // Send sensor values to the structure
        xQueueSend(msg_queue, &sendSensorValues, portMAX_DELAY);

        // Delay task for 100ms to give time
        vTaskDelay(100);
    }
}

void sendData(void *pvParameters)
{
    (void)pvParameters;

    sensorData getSensorValues;

    for (;;)
    {
        // Create the JSON document
        StaticJsonDocument<50> doc;

        // Checks if the Item was recieved from the queue to be packaged and sent to the Pi
        if (xQueueReceive(msg_queue, &getSensorValues, portMAX_DELAY) == pdPASS)
        {
            doc["weight"] = getSensorValues.objectWeight;
            doc["switch"] = getSensorValues.switchState;
            doc["alarm"] = getSensorValues.alarmStatus;

            if (getSensorValues.alarmStatus)
            {
                buzzActive();
            }

            // Send the JSON document over the "link" serial port
            // This better work idk why it wont
            serializeJson(doc, Serial2);
            Serial.println("JSON packet sent");
        }

        // Delay task for 1000 to give time for sensor readings to be updated
        vTaskDelay(1000);
    }
}

void timeDoorCheck(TimerHandle_t xTimer)
{
    sensorData doorChangeState;

    // if door still open after the timer has expired change the Alarm Status to true
    if (doorChangeState.switchState)
    {
        doorChangeState.alarmStatus = true;
    }

    xQueueSend(msg_queue, &doorChangeState, portMAX_DELAY);

    Serial.println("timer expired");
}


// PUBLIC FUNCTION DEFINITIONS

// Create tasks
void taskCreate(void)
{
    xTaskCreate(
        getSensorData,
        " Gather Data ",
        1000,
        NULL,
        1,
        NULL);

    xTaskCreate(
        sendData,
        " Send data to pi",
        1000,
        NULL,
        1,
        NULL);

    // Create a one-shot timer
    one_shot_timer = xTimerCreate(
        "One-shot timer", // Name of timer
        dim_delay,        // Period of timer (in ticks)
        pdFALSE,          // Auto-reload
        (void *)0,        // Timer ID
        timeDoorCheck);   // Callback function

    // Setup the message queue
    msg_queue = xQueueCreate(QUEUE_LENGTH,
                             sizeof(sensorData));

    vTaskDelete(NULL);
}