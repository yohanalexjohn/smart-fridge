/**
 * @file weightSensor.cpp
 * @author Smart-fridge
 * @brief Define the private and public functions
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "weightSensor.h"
#include "HX711.h"

#define CALWEIGHT 3.00
#define DEFAULT_CALIFACTOR -7050

HX711 scale;

// PUBLIC FUNCTIONS DEFINITION

void weightSensorInit(void)
{
    long currentOffset = 0;
    float calibration_factor = DEFAULT_CALIFACTOR;
    
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

    scale.set_offset(currentOffset);
    scale.set_scale(calibration_factor / 0.45352);

    delay(1000);
}

float get_Weight(void)
{
    float data = abs(scale.get_units());

    if (0.0000 - data > 0.0001)
        data = 0.00; // reset to zero

    data = data - 10;
    data = abs(data);

    return data;
}
