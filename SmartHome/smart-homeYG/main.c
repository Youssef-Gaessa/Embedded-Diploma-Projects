/*
 * Module: Main Application
 *
 * File Name: main.c
 *
 * Created on: 10 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "smarthome.h"

int main(void) {
	/* Initialize hardware components */
	hardware_init();

	while (TRUE) {
		/* Check for if there is flame or not */
		uint8 Flame = FlameSensor_getValue(&flame_sensor1);
		/* If flame is detected, activate the alarm and display a critical alert */
		if (Flame) {
			Buzzer_on(&Alarm);
			LCD_DisplayStringRowColumn(0, 0, STRING("Critical alert!     "));
			LCD_DisplayStringRowColumn(1, 0, STRING("                    "));
		} else {
			/* Turn off the alarm if no flame is detected */
			Buzzer_off(&Alarm);
			/* If no flame is detected, proceed with normal operation */

			/* Read the light intensity and temperature */
			uint8 Light_intensity = LDR_getLightIntensity(LDR_sensor);
			uint8 Temprature = LM35_getTemperature(temp_sensor);

			/* Handle lighting based on light intensity */
			handle_lighting_control(Light_intensity);

			/* Control fan speed based on temperature */
			automatic_Fan_speed_control(Temprature);

			/* Display temperature and light intensity on the LCD */
			display_control(Temprature, Light_intensity);
		}
	}
	return 0;
}
