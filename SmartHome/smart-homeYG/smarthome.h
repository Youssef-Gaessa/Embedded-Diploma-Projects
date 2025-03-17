/*
 * Module: Smarthome
 *
 * File Name: smarthome.h
 *
 * Created on: 10 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#ifndef SMARTHOME_H_
#define SMARTHOME_H_

/*******************************************************************************
 *                              Drivers Including                              *
 *******************************************************************************/
#include "MCAL/GPIO/gpio.h"
#include "MCAL/ADC/ADC.h"
#include "MCAL/PWM/PWM.h"
#include "MCAL/common_macros.h"
#include "HAL/LCD/LCD.h"
#include "HAL/LM35/lm35_sensor.h"
#include "HAL/LDR/LDR.h"
#include "HAL/LED/LED.h"
#include "HAL/FlameSensor/Flame_Sensor.h"
#include "HAL/Buzzer/BUZZER.h"
#include "HAL/DcMotor/Motor.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Temperature thresholds for fan control */
#define TEMP_THRESHOLD_LOW 25
#define TEMP_THRESHOLD_MEDIUM 30
#define TEMP_THRESHOLD_HIGH 35
#define TEMP_THRESHOLD_MAX 40

/* Light intensity thresholds for lighting control */
#define LIGHT_HIGH_INTENSITY 70
#define LIGHT_MEDIUM_INTENSITY 51
#define LIGHT_LOW_INTENSITY 16
#define LIGHT_MIN_INTENSITY 15

/* Macro for LCD string literals */
#define STRING(str) ((const uint8 *)str)

/* Predefined messages for LCD */
#define FAN_ON_STRING ((const uint8 *)"   FAN is ON   ")
#define FAN_OFF_STRING ((const uint8 *)"   FAN is OFF  ")

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

/*
 *  Initializes hardware components (LEDs, Fan, Buzzer, etc.).
 */
void hardware_init(void);

/*
 * Controls LEDs based on light intensity.
 */
void handle_lighting_control(uint8 Light_intensity);

/*
 * Updates LCD with fan status, temperature, and light intensity.
 */
void display_control(uint8 temperature, uint8 intensity);

/*
 * Adjusts fan speed based on temperature.
 */
void automatic_Fan_speed_control(uint8 Temprature);

#endif /* SMARTHOME_H_ */
