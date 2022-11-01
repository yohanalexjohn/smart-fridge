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
#include "espCam.h"

float objectWeight;
bool switchState;
String pictureToSend;

// PRIVATE FUNCTION DECLARTATIONS

/**
 * @brief Get the Weight Data object
 *
 * @param pvParameters
 */
static void getWeightData(void *pvParameters);

/**
 * @brief Get the get halState object
 *
 * @param pvParameters
 */
static void getHalState(void *pvParameters);

/**
 * @brief Get the Picture object
 *
 * @param pvParameters
 */
static void getPicture(void *pvParameters);

/**
 * @brief Send the data to the Pi
 *
 * @param pvParameters
 */
// static void sendData(void *pvParameters);

// PRIVATE FUNCTION DEFINITIONS

void getWeightData(void *pvParameters)
{
    for (;;)
    {
        Serial.println("taking weight task");
        objectWeight = get_Weight();
    }
}

void getHalState(void *pvParameters)
{
    for (;;)
    {
        Serial.println("taking switch task");
        switchState = get_halState();
    }
}

void getPicture(void *pvParameters)
{
    for (;;)
    {
        String pictureToSend;
        Serial.println("taking picture task");
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        Serial.println(pictureToSend);


        pictureToSend = takePicture();

        vTaskDelay( 1000/ portTICK_PERIOD_MS );
    }
}

// void sendData(void *pvParameters)
// {
//     for (;;)
//     {
//         // Create the JSON document
//         StaticJsonDocument<200> doc;
//         doc["weight"] = objectWeight;
//         doc["switch"] = switchState;

//         // Send the JSON document over the "link" serial port
//         serializeJson(doc, Serial1);
//     }
// }

// PUBLIC FUNCTION DEFINITIONS

// Create tasks
void taskCreate(void)
{
    xTaskCreate(
        getWeightData,
        " Gather Weight ",
        1000,
        NULL,
        1,
        NULL);

    xTaskCreate(
        getHalState,
        " Get the HAL state ",
        1000,
        NULL,
        1,
        NULL);

    xTaskCreate(
        getPicture,
        " Get the picture and convert it base64 ",
        10000,
        NULL,
        1,
        NULL);

    // xTaskCreate(
    //     sendData,
    //     " Send data to pi",
    //     1000,
    //     NULL,
    //     0,
    //     NULL);
    vTaskDelete(NULL);
}