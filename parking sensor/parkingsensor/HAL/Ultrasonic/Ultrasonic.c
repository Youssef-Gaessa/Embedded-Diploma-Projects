/*
 * Ultrasonic.c
 *
 *  Created on: 3 Apr 2025
 *      Author: TRXoJO
 */

/*
 * Modules Includes
 */
#include "Ultrasonic.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ICU/icu.h"
#include "util/delay.h"


/* ICU configuration structure */
ICU_ConfigType ICU_config = {.clock = F_CPU_8, .edge = RAISING };

/* Variables to store edge count and pulse duration */
uint8 edge_count = 0;
uint32 time_high = 0;

/* Ultrasonic sensor configuration structure */
Ultrasonic_t distance_sensor = { .TRIGGER_PORT = PORTD_ID, .TRIGGER_PIN = PIN7_ID,
                                 .ECHO_PORT = PORTD_ID, .ECHO_PIN = PIN6_ID };

/* Initialize the ultrasonic sensor */
void Ultrasonic_init(Ultrasonic_t *Usonic) {
	ICU_init(&ICU_config); /* Initialize ICU with configuration */
	ICU_setCallBack(Ultrasonic_edgeProcessing); /* Set callback for edge processing */
	GPIO_setupPinDirection(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, PIN_OUTPUT); /* Set trigger pin as output */
}

/* Send trigger pulse to the ultrasonic sensor for 10 us */
void Ultrasonic_Trigger(Ultrasonic_t *Usonic) {
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_HIGH); /* Set the trigger pin */
	_delay_us(10); /* Wait for 10 microseconds */
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_LOW); /* clear the trigger pin */
}

/* Read the distance measured by the ultrasonic sensor */
uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic) {
	Ultrasonic_Trigger(Usonic); /* Trigger the sensor */
	if (edge_count == 2) { /* Check if both edges have been captured */
		edge_count = 0; /* Reset edge count */
		return ((time_high + ERROR_MARGIN) * 0.008575); /* Calculate and return distance */
	}
}

/* Handle the edge detection and timing for the ultrasonic sensor */
void Ultrasonic_edgeProcessing(void) {
	edge_count++; /* Increment edge count */
	if (edge_count == 1) {
		ICU_clearTimerValue(); /* Clear timer on first edge */
		ICU_setEdgeDetectionType(FALLING); /* Set edge detection to falling */
	} else if (edge_count == 2) {
		time_high = ICU_getInputCaptureValue(); /* Capture pulse duration */
		ICU_setEdgeDetectionType(RAISING); /* Set edge detection back to rising */
	}
}
