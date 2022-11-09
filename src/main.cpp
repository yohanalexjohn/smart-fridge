/**
 * @file main.cpp
 * @author Smart-Fridge
 * @brief Main file
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "boardConfig.h"
#include "weightSensor.h"
#include "halSwitch.h"
#include "createTasks.h"
#include "buzzer.h"

void setup()
{

  Serial.begin(115200);
  Serial1.begin(9600);

  weightSensorInit();
  halSensorInit();
  buzzActive();
  taskCreate();
}

void loop()
{

}