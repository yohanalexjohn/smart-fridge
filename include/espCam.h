/**
 * @file espCam.h
 * @author Smart-Fridge
 * @brief Declare the Public functions to be used for the camera 
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "boardConfig.h"

/**
 * @brief Initialise the Camera 
 * 
 */
void cameraInit(void);

/**
 * @brief Take the picture and store it in a string 
 * 
 */
String takePicture(void);