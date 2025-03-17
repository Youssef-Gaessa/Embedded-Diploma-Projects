/*
 * Module: Smarthome
 *
 * File Name: smarthome.c
 *
 * Created on: 10 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "smarthome.h"


/*******************************************************************************
 *                         Function Implementations                            *
 *******************************************************************************/

/*
 * Initializes the necessary hardware components: LEDs, motor for fan, buzzer, flame sensor, ADC, and LCD.
 */
void hardware_init(void) {
    LED_init(&Green);
    LED_init(&Blue);
    LED_init(&Red);
    DcMotor_init(&Fan);
    Buzzer_init(&Alarm);
    FlameSensor_init(&flame_sensor1);
    ADC_init();
    LCD_init();
}

/*
 * Controls the LEDs based on the current light intensity.
 */
void handle_lighting_control(uint8 Light_intensity) {
    if (Light_intensity > LIGHT_HIGH_INTENSITY) {
        LED_off(&Green);
        LED_off(&Blue);
        LED_off(&Red);
    } else if (Light_intensity >= LIGHT_MEDIUM_INTENSITY) {
        LED_off(&Green);
        LED_off(&Blue);
        LED_on(&Red);
    } else if (Light_intensity >= LIGHT_LOW_INTENSITY) {
        LED_on(&Green);
        LED_off(&Blue);
        LED_on(&Red);
    } else {
        LED_on(&Green);
        LED_on(&Blue);
        LED_on(&Red);
    }
}

/*
 * Adjusts the fan speed based on the current temperature reading.
 */
void automatic_Fan_speed_control(uint8 Temprature) {
    uint8 speed = 0;
    DcMotor_State state = Clock_Wise;

    if (Temprature >= TEMP_THRESHOLD_MAX) {
        speed = 100;
    } else if (Temprature >= TEMP_THRESHOLD_HIGH) {
        speed = 75;
    } else if (Temprature >= TEMP_THRESHOLD_MEDIUM) {
        speed = 50;
    } else if (Temprature >= TEMP_THRESHOLD_LOW) {
        speed = 25;
    } else {
        /* Stop the fan if the temperature is below the lowest threshold */
        DcMotor_STOP(&Fan);
        return;
    }

    /* Rotate the fan motor at the calculated speed */
    DcMotor_Rotate(&Fan, state, speed);
}

/*
 * Updates the LCD display with the current fan status, temperature, and light intensity.
 */
void display_control(uint8 temperature, uint8 intensity) {
    /* Display fan status (ON or OFF) based on temperature */
    LCD_MoveCursor(0, 0);
    if (temperature >= TEMP_THRESHOLD_LOW) {
        LCD_DisplayString(FAN_ON_STRING);
    } else {
        LCD_DisplayString(FAN_OFF_STRING);
    }

    /* Display temperature and light intensity values */
    LCD_MoveCursor(1, 0);
    LCD_DisplayString(STRING("TEMP="));
    LCD_intgerToString(temperature);
    if (temperature < 100) {
        LCD_DisplayString(STRING(" "));
    }

    LCD_DisplayString(STRING("LDR="));
    LCD_intgerToString(intensity);
    LCD_DisplayCharacter('%');
    if (intensity < 100) {
        LCD_DisplayString(STRING("  "));
    }
}
