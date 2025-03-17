/*
 * Module: Buzzer
 *
 * File Name: Buzzer.h
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/* Standard types */
#include "../../MCAL/std_types.h"

/* Enum to set buzzer active state (high or low) */
typedef enum {
	BUZZER_ACTIVE_HIGH,
	BUZZER_ACTIVE_LOW
} BUZZER_state;

/* Struct for buzzer configuration: port, pin, and active state */
typedef struct {
	uint8 PORT :2;  /* Port number (0-3) */
	uint8 PIN :3;   /* Pin number (0-7) */
	BUZZER_state state :1;  /* Active state (high/low) */
} BUZZER;

/* External buzzer variable */
extern BUZZER Alarm;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initialize the buzzer pin as output */
void Buzzer_init(BUZZER *buzz);

/* Turn on the buzzer */
void Buzzer_on(BUZZER *buzz);

/* Turn off the buzzer */
void Buzzer_off(BUZZER *buzz);

/* Toggle the buzzer state */
void Buzzer_toggle(BUZZER *buzz);

#endif /* BUZZER_H_ */
