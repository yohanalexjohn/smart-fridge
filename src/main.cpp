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
#include "led.h"

void setup()
{
  // Begin all the serial comms between the sensors and the esp32 with the Pi
  Serial.begin(115200);
  Serial1.begin(9600);//, SERIAL_8N1, 18, 17);

  // Initialise all the sensors and tasks
  weightSensorInit();
  halSensorInit();
  buzzerInit();
  taskCreate();
}

void loop()
{
}
