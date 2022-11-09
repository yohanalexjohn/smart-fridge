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

// Settings
static const TickType_t dim_delay = 60000 / portTICK_PERIOD_MS;

float objectWeight;
bool switchState;

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


// Turn off LED when timer expires
static void timeDoorCheck(TimerHandle_t xTimer);

// PRIVATE FUNCTION DEFINITIONS

void getSensorData(void *pvParameters)
{
    for (;;)
    {
        Serial.println("Get Sensor Data");
        
        switchState = getHalState();

        if(switchState)
        {
            objectWeight = get_Weight();
            // Start timer
            xTimerStart(one_shot_timer, portMAX_DELAY);
        }
    }
}

void sendData(void *pvParameters)
{
    for (;;)
    {
        // Create the JSON document
        StaticJsonDocument<200> doc;
        doc["weight"] = objectWeight;
        doc["switch"] = switchState;

        // Send the JSON document over the "link" serial port
        serializeJson(doc, Serial1);
    }
}

void timeDoorCheck(TimerHandle_t xTimer)
{
    buzzActive();
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
        0,
        NULL);

    // Create a one-shot timer
    one_shot_timer = xTimerCreate(
                      "One-shot timer",     // Name of timer
                      dim_delay,            // Period of timer (in ticks)
                      pdFALSE,              // Auto-reload
                      (void *)0,            // Timer ID
                      autoDimmerCallback);  // Callback function

    vTaskDelete(NULL);
}