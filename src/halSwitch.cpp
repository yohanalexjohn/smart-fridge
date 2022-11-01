/**
 * @file halSwitch.cpp
 * @author Smart-Fridge
 * @brief Define the Public Functions
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "halSwitch.h"

void halSensorInit(void)
{
    pinMode(HAL_SWITCH, INPUT);
    pinMode(YELLOW_LED,OUTPUT);
    Serial.println("HAL Callibrated");
    delay(100);
}

bool get_halState(void)
{
    bool halState;

    halState = digitalRead(HAL_SWITCH);
    digitalWrite(YELLOW_LED, HIGH);
    delay(1000);
    digitalWrite(YELLOW_LED, LOW);
    Serial.println(halState);
    return halState;
}
