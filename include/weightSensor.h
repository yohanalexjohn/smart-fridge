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
*@brief Initialises the weight sensor 
*@return void
*/
void weightSensorInit( void );

/**
 * @brief Get the Weight of the object
 * 
 * @return float 
 */
float get_Weight(void);
