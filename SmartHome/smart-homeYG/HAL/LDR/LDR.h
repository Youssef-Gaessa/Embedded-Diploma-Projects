/*
 * Module: LDR
 *
 * File Name: LDR.h
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#ifndef LDR_H_
#define LDR_H_

/* Includes Standard Types */
#include "../../MCAL/std_types.h"

/*
 * Definitions
 */
#define LDR_SENSOR_CHANNEL_ID 0
#define LDR_SENSOR_MAX_VOLT_VALUE 2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY 100

/*
 * Create an LDR data type for LDR Channel
 * - This to increase the code readability
 */
typedef uint8 LDR;

/* Extern object of the LDR_sensor */
extern LDR LDR_sensor;

/*Function to get the light intensity */
uint8 LDR_getLightIntensity(LDR LDR_Channel);

#endif /* LDR_H_ */
