/**
 * @file weightSensor.h
 * @author Smart-Fridge
 * @brief Declare the Public functions to be used for the weight sensor 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "boardConfig.h"

/**
* @brief Initialises the weight sensor 
*
*/
void weightSensorInit( void );

/**
 * @brief Get the direction of the object
 *        The system should run for about 5 seconds before readings become accurate
 * 
 * @return int (message data)
 */
int get_direction(void);
