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

 void buzzerInit(void)
 {
    pinMode(BUZZER,OUTPUT); 
    delay(100);
 }

 void buzzActive(void)
 {
    tone(BUZZER,1000);
 }