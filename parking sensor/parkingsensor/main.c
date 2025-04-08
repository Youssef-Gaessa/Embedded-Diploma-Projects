/*
 * main.c
 *
 *  Created on: 3 Apr 2025
 *      Author: TRXoJO
 */


#include "MCAL/std_types.h"
#include "MCAL/common_macros.h"
#include "MCAL/GPIO/gpio.h"
#include "MCAL/ICU/icu.h"
#include "HAL/Buzzer/BUZZER.h"
#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"
#include "HAL/Ultrasonic/Ultrasonic.h"
#include "util/delay.h"

#define FLASHING_DELAY 150
#define LCD_STRING(str) ((const uint8 *)(str))

/*
 * Prototypes
 */
void displayDistance(uint16 distance);
void handleDistanceActions(uint16 distance);

int main(void) {
	/* Initialize components */
	LCD_init();
	LED_init(&Blue);
	LED_init(&Green);
	LED_init(&Red);
	Buzzer_init(&Alarm);
	Ultrasonic_init(&distance_sensor);

	uint16 reading = 0;

	/* Keep checking until the ultrasonic sensor gives a valid reading */
	do {
		Ultrasonic_Trigger(&distance_sensor);
		reading = Ultrasonic_readDistance(&distance_sensor);
		_delay_ms(20);
	} while (reading == 0);

	/* Main loop */
	for (;;) {
		/* Trigger ultrasonic sensor and get the distance */
		Ultrasonic_Trigger(&distance_sensor);
		reading = Ultrasonic_readDistance(&distance_sensor);

		/* Display the distance on the LCD and take appropriate actions */
		handleDistanceActions(reading);

		/* Add a small delay for stability */
		_delay_ms(20);
	}
	return 0;
}

/**
 * Function to display the distance on the LCD.
 */
void displayDistance(uint16 distance) {
	LCD_MoveCursor(0, 0);
	LCD_DisplayString(LCD_STRING("Distance= "));
	LCD_intgerToString(distance);
	LCD_DisplayString(LCD_STRING(" CM    "));
}

/**
 * Function to handle the actions based on the measured distance.
 */
void handleDistanceActions(uint16 distance) {
	if (distance <= 5) {
		LED_on(&Blue);
		LED_on(&Green);
		LED_on(&Red);
		Buzzer_on(&Alarm);
		_delay_ms(FLASHING_DELAY);
		LED_off(&Blue);
		LED_off(&Green);
		LED_off(&Red);
		Buzzer_off(&Alarm);
		_delay_ms(FLASHING_DELAY);

		displayDistance(distance);
		LCD_DisplayStringRowColumn(1, 0, LCD_STRING("      STOP      "));
	} else if (distance <= 10) {
		Buzzer_off(&Alarm);
		LED_on(&Blue);
		LED_on(&Green);
		LED_on(&Red);
		displayDistance(distance);
		LCD_DisplayStringRowColumn(1, 0, LCD_STRING("                "));
	} else if (distance <= 15) {
		Buzzer_off(&Alarm);
		LED_off(&Blue);
		LED_on(&Green);
		LED_on(&Red);
		displayDistance(distance);
	} else if (distance <= 20) {
		Buzzer_off(&Alarm);
		LED_off(&Blue);
		LED_off(&Green);
		LED_on(&Red);
		displayDistance(distance);
	} else {
		Buzzer_off(&Alarm);
		LED_off(&Blue);
		LED_off(&Green);
		LED_off(&Red);
		displayDistance(distance);
	}
}
