/*
 * Module: LED
 *
 * File Name: LED.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "LED.h"
#include "util/delay.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/common_macros.h"
/*
 * Define LEDS Parameters
 */
LED_ID Green = { .LED_PORT = PORTC_ID, .LED_PIN = PIN1_ID, ACTIVE_HIGH };
LED_ID Blue = { .LED_PORT = PORTC_ID, .LED_PIN = PIN2_ID, ACTIVE_HIGH };
LED_ID Red = { .LED_PORT = PORTC_ID, .LED_PIN = PIN0_ID, ACTIVE_HIGH };

/*
 * Function to initialize the LED
 */
void LED_init(LED_ID *id) {
	GPIO_setupPinDirection(id->LED_PORT, id->LED_PIN, PIN_OUTPUT);
	LED_off(id);
}
/*
 * Function to Turn LED on
 */
void LED_on(LED_ID *id) {
	GPIO_writePin(id->LED_PORT, id->LED_PIN, (LOGIC_HIGH ^ id->STATE));
}
/*
 * Function to Turn LED off
 */
void LED_off(LED_ID *id) {
	GPIO_writePin(id->LED_PORT, id->LED_PIN, (LOGIC_LOW ^ id->STATE));
}
void LED_toggle(LED_ID *id,uint8 delaytime) {
	LED_on(id);
	_delay_ms(delaytime);
	LED_off(id);
	_delay_ms(delaytime);
}
