/**
 * @file buzzer.h.h
 * @author Smart-Fridge
 * @brief Header file to declare the functions for the buzzer
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief Initialise the Buzzer as an output
 * 
 */
void buzzerInit(void);

/**
 * @brief Buzz at a set interval using PWM 
 * 
 */
void buzzActive(void);