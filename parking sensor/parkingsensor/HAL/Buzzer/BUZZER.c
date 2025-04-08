/*
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "BUZZER.h"
#include "../../MCAL/GPIO/gpio.h"

/* Initialize the buzzer object with default values */
BUZZER Alarm = { .PORT = PORTC_ID, .PIN = PIN5_ID, .state = BUZZER_ACTIVE_HIGH };

/* Set the buzzer pin as output */
void Buzzer_init(BUZZER *buzz) {
    GPIO_setupPinDirection(buzz->PORT, buzz->PIN, PIN_OUTPUT);
}


/* Turn on the buzzer */
void Buzzer_on(BUZZER *buzz) {
    GPIO_writePin(buzz->PORT, buzz->PIN, (LOGIC_HIGH ^ buzz->state));
}

/* Turn off the buzzer */
void Buzzer_off(BUZZER *buzz) {
    GPIO_writePin(buzz->PORT, buzz->PIN, (LOGIC_LOW ^ buzz->state));
}
