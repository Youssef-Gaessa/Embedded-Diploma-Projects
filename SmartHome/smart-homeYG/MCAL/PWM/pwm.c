/*
 * Module: ADC
 *
 * File Name: PWM.c
 *
 *  Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "PWM.h"
#include <avr/io.h>

/*
 *  Initializes Timer0 for PWM mode and sets the duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle) {
	DDRB |= (1 << PB3);  /* Set PB3 as output for PWM */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01); /* Set Fast PWM mode and clear on compare match */
	TCCR0 |= (1 << CS00) | (1 << CS02);  /* Start Timer0 with prescaler of 1024 */
	OCR0 = (uint8) (((uint16) duty_cycle * 255) / 100); /* Set the duty cycle when the given is percentage (0/100)% */
}
