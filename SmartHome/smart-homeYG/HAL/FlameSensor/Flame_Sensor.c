/*
 * Module: Flame Sensor
 *
 * File Name: flame_sens.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "../../MCAL/GPIO/gpio.h"
#include "Flame_Sensor.h"

/* Initialize the sensor object */
FlameSensor flame_sensor1 = { .PORT = PORTD_ID, .PIN = PIN2_ID };

/* Initialize the sensor */
void FlameSensor_init(FlameSensor *flame) {
	GPIO_setupPinDirection(flame->PORT, flame->PIN, PIN_INPUT);
}

/* return the value of the flame sensor */
uint8 FlameSensor_getValue(FlameSensor *flame) {
	return (GPIO_readPin(flame->PORT, flame->PIN));
}
