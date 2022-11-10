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
static const TickType_t dim_delay = 60000 / portTICK_PERIOD_MS;

// Name of the software timer handler
static TimerHandle_t one_shot_timer = NULL;

// Send data from producer to consumer
QueueHandle_t msg_queue;

TaskHandle_t alarmTaskHandler;

/**
 * @brief store the sensor data
 *
 */
struct sensorData
{
    float objectWeight;
    bool switchState;
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
static void activateAlarm(void *pvParameters);

// PRIVATE FUNCTION DEFINITIONS
void getSensorData(void *pvParameters)
{
    (void)pvParameters;

    sensorData sendSensorValues;

    for (;;)
    {
        Serial.println("Get Sensor Data");

        sendSensorValues.switchState = get_halState();

        // If the door is open get object weight and start timer
        if (sendSensorValues.switchState)
        {
            sendSensorValues.objectWeight = get_Weight();

            // Check if the timer has not already been started
            if (!xTimerIsTimerActive(one_shot_timer))
            {
                // Start timer
                xTimerStart(one_shot_timer, portMAX_DELAY);
            }
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
        StaticJsonDocument<200> doc;

        // Checks if the Item was recieved from the queue to be packaged and sent to the Pi
        if (xQueueReceive(msg_queue, &getSensorValues, portMAX_DELAY) == pdPASS)
        {
            doc["weight"] = getSensorValues.objectWeight;
            doc["switch"] = getSensorValues.switchState;

            // Send the JSON document over the "link" serial port
            serializeJson(doc, Serial1);
            Serial.println("JSON packet sent");
        }

        // Delay task for 1000 to give time for sensor readings to be updated
        vTaskDelay(1000);
    }
}

void timeDoorCheck(TimerHandle_t xTimer)
{
    vTaskResume(alarmTaskHandler);
}

void activateAlarm(void *pvParameters)
{
    sensorData checkDoorStatus;

    // Check if the data for the structure is full and check if the door is open and buzz till door is
    if (xQueueReceive(msg_queue, &checkDoorStatus, portMAX_DELAY) == pdPASS)
    {
        // Keep buzzing at an intreval as long as the door is open
        while (checkDoorStatus.switchState)
        {
            buzzActive();
        }
    }

    // Suspend this task when the door is closed
    vTaskSuspend(NULL);
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
        2,
        NULL);

    xTaskCreate(
        activateAlarm,
        "Activate the alarm",
        1000,
        NULL,
        3,
        &alarmTaskHandler);

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