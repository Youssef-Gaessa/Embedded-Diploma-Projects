/*
 * Ultrasonic.h
 *
 *  Created on: 4 Apr 2025
 *      Author: TRXoJO
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

#include "../../MCAL/std_types.h"

/* Define an error margin for distance calculation, this value needs calibration */
#define ERROR_MARGIN 95

/* Structure to hold ultrasonic sensor pin configurations */
typedef struct {
	uint8 TRIGGER_PORT :2;
	uint8 TRIGGER_PIN :3;
	uint8 ECHO_PORT :2;
	uint8 ECHO_PIN :3;
} Ultrasonic_t;

/* External declaration for ultrasonic sensor configuration */
extern Ultrasonic_t distance_sensor;

/* Function prototypes */
void Ultrasonic_init(Ultrasonic_t *Usonic); /* Initialize ultrasonic sensor */
void Ultrasonic_Trigger(Ultrasonic_t *Usonic); /* Trigger ultrasonic sensor */
uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic); /* Read distance measured */
void Ultrasonic_edgeProcessing(void); /* Handle edge processing for echo signal */

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
