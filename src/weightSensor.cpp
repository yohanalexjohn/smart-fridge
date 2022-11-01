/**
 * @file weightSensor.cpp
 * @author Smart-fridge
 * @brief Define the private and public functions
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "weightSensor.h"
#include "HX711.h"

// STATIC FUNCTIONS DECLARATION
/**
 * @brief Calibrate the weight sensor to return weight in grams
 *
 */
// static void weightSensorCalilbration( void );

HX711 scale;

// STATIC FUNCTION DEFINITION

// void weightSensorCallibration(void)
// {
//     // TODO
// }

// PUBLIC FUNCTIONS DEFINITION

void weightSensorInit(void)
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    // weightSensorCalilbration();
    delay(1000);
    Serial.println("weight sensor callibrated");
}

float get_Weight(void)
{
    float reading = scale.read();
    Serial.println(reading);
    //digitalWrite(RED_LED, HIGH);
    delay(2000);
    //digitalWrite(RED_LED, LOW);
    return reading;
}
