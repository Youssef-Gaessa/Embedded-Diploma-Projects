/*
 * Module: DcMotor
 *
 * File Name: Motor.h
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "../../MCAL/std_types.h"

/* Enable motor control via enable pin */
#define DCMOTOR_ENABLE_EN TRUE

/* Enum for motor rotation direction */
typedef enum {
	Clock_Wise, Anti_Clock_Wise
} DcMotor_State;

/* Struct for motor configuration: direction and enable pins */
typedef struct {
	uint8 DcMotor_DIR_PORT :2;   /* Direction port */
	uint8 DcMotor_DIR_PINA :3;   /* Direction pin A */
	uint8 DcMotor_DIR_PINB :3;   /* Direction pin B */
#if(DCMOTOR_ENABLE_EN == TRUE)
	uint8 DCMotor_EN_PORT :2;    /* Enable port */
	uint8 DcMotor_EN_PIN :3;     /* Enable pin */
#endif
} DcMotor;

/* External motor object (Fan) */
extern DcMotor Fan;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Initialize motor pins */
void DcMotor_init(DcMotor *Motor);

/* Rotate motor in the specified direction with speed */
void DcMotor_Rotate(DcMotor *Motor, DcMotor_State state, uint8 speed);

/* Stop the motor */
void DcMotor_STOP(DcMotor *Motor);

#endif /* MOTOR_H_ */
