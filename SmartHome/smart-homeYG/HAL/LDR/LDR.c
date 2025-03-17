/*
 * Module: LDR
 *
 * File Name: LDR.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "LDR.h"
#include "../../MCAL/ADC/ADC.h"

/* Define LDR Sensor Channel */

LDR LDR_sensor = 0;

/* Function to calculate and return the Light Intensity */
uint8 LDR_getLightIntensity(LDR LDR_Channel)
{

	uint8 light_intensity = 0;
	uint16 ADC_value = 0;

	ADC_value = ADC_readChannel(LDR_Channel);
	light_intensity = (uint8) (((uint32) ADC_value
			* LDR_SENSOR_MAX_LIGHT_INTENSITY * ADC_REF_VOLT_VALUE)
			/ (ADC_MAXIMUM_VALUE * LDR_SENSOR_MAX_VOLT_VALUE));

	return light_intensity;
}
