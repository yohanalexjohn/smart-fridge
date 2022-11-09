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
    Serial.println("HAL Initialised");
    delay(100);
}

bool get_halState(void)
{
    bool halState;

    halState = digitalRead(HAL_SWITCH);
    delay(1000);
    Serial.println(halState);
    return halState;
}
