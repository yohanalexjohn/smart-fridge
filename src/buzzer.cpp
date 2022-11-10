/**
 * @file buzzer.cpp
 * @author Smart-Fridge
 * @brief Buzzer code with a timer
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "boardConfig.h"
#include "buzzer.h"

#define PULSE_TIME 1000
#define FREQUENCY 1000

void buzzerInit(void)
{
   pinMode(BUZZER, OUTPUT);
   delay(100);
}

void buzzActive(void)
{
   // This will activate the buzzer at a 1000hz at a pulse rate of 1 sec
   tone(BUZZER, FREQUENCY, PULSE_TIME);
}