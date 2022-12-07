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

// Macros for load sensor
#define CALWEIGHT               3.00
#define DEFAULT_CALIFACTOR      -7050
#define BAD_VALUE               1.97
#define SAMPLE_COUNT            10
#define FRIDGE_EMPTY            0.00

// Direction Data
#define DIRECTION_NO_CHANGE     0       // Object weight leaving and entering the fridge is the same
#define DIRECTION_LEAVE_FRIDGE  1       // Object left the fridge as weight drops to 0
#define DIRECTION_ENTER_FRIDGE  2       // New Object has entered the fridge as weight is different to previous object

HX711 scale;

// PRIVATE FUNCTION DECLARATION
/**
 * @brief Get the Weight of the object
 *
 * @return weight
 */
float get_Weight(void);

// PRIVATE FUNCTION DEFINITION

float get_Weight(void)
{
    float newData = abs(scale.get_units());
    static float oldData = 0.00; // static is used so that the newData can take the old datas value if BAD_VALUE is received

    if (0.0000 - newData > 0.0001)
        newData = 0.00; // reset to zero

    newData = newData - 10;
    newData = abs(newData);

    if (BAD_VALUE == newData)
    {
        newData = oldData;
    }

    oldData = newData;

    /**
     * for debugging purposese
     *
     */
    // if ( newData == BAD_VALUE)
    // {
    //     Serial.println("your logic sucks");
    // }

    return newData;
}

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

int get_direction(void)
{
    static float oldAvgWeight = 0.00;
    float newAvgWeight = 0.00;
    float sumWeight = 0.00;

    int direction = DIRECTION_NO_CHANGE;

    // Collect the sum of the weights for the give Sample Count
    for (int i = 0; i < SAMPLE_COUNT; i++)
    {
        float currentWeight = get_Weight();
        sumWeight = sumWeight + currentWeight;
    }

    // Calculate the average weight 
    newAvgWeight = sumWeight / SAMPLE_COUNT;

    // Using the average weight find the distance 

    if (newAvgWeight == FRIDGE_EMPTY)
    {
        direction = DIRECTION_LEAVE_FRIDGE;
    }

    if ((newAvgWeight > oldAvgWeight) || (newAvgWeight < oldAvgWeight))
    {
        direction = DIRECTION_ENTER_FRIDGE;
    }

    // The current weight now becomes the old weight which is used as comparision the next time the function is called 
    oldAvgWeight = newAvgWeight; 

    return direction;
}