/**
 * @file boardConfig.h
 * @author Smart-Fridge
 * @brief Declare the Macros to be used 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>

// HX711 pin config
#define  LOADCELL_DOUT_PIN   15
#define  LOADCELL_SCK_PIN    0

// HAL effect switch pin config 
#define HAL_SWITCH           2

// Camera config
#define EEPROM_SIZE          1

#define PWDN_GPIO_NUM       -1
#define RESET_GPIO_NUM      -1
#define XCLK_GPIO_NUM       21
#define SIOD_GPIO_NUM       26
#define SIOC_GPIO_NUM       27

#define Y9_GPIO_NUM         35
#define Y8_GPIO_NUM         34
#define Y7_GPIO_NUM         39
#define Y6_GPIO_NUM         36
#define Y5_GPIO_NUM         19
#define Y4_GPIO_NUM         18
#define Y3_GPIO_NUM         5
#define Y2_GPIO_NUM         4
#define VSYNC_GPIO_NUM      25
#define HREF_GPIO_NUM       23
#define PCLK_GPIO_NUM       22

// LED's for testing
#define RED_LED             1
#define YELLOW_LED          3
#define GREEN_LED           14
