/*
 * Module: LED
 *
 * File Name: LED.h
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#ifndef LED_H_
#define LED_H_

/* Include Standard Types */
#include "../../MCAL/std_types.h"

/* Enum to Define LED State */
typedef enum {
	ACTIVE_HIGH, ACTIVE_LOW
} ACTIVE_STATE;

/*
 * Struct for LED configuration contains: PORT, PIN, state of LED (Active High / Active Low )
 */
typedef struct {
	uint8 LED_PORT;
	uint8 LED_PIN;
	ACTIVE_STATE STATE;
} LED_ID;

/* Extern the 3 LEDs objects */
extern LED_ID Green, Blue, Red;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/*
 * Function to initialize the LED (PORT, PIN, State)
 */
void LED_init(LED_ID *id);
/*
 * Function to turn LED on
 */
void LED_on(LED_ID *id);
/*
 * Function to turn of LED
 */
void LED_off(LED_ID *id);

#endif /* LED_H_ */
