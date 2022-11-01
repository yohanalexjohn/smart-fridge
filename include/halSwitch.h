/**
 * @file halSwitch.h
 * @author Smart-Fridge
 * @brief Declare the Public functions to be used for the Hal Switch 
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "boardConfig.h"

/**
 * @brief Initalises the Hal sensor
 *
 */

void halSensorInit(void);

/**
 * @brief Get the halState of the sensor
 *
 * @return true when the door is open
 * @return false when the door is closed
 */
bool get_halState(void);