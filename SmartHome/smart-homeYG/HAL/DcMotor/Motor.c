/*
 * Module: DcMotor
 *
 * File Name: Motor.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "Motor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/PWM/PWM.h"

// Initialize the Fan motor settings
DcMotor Fan = { .DcMotor_DIR_PORT = PORTB_ID, .DcMotor_DIR_PINA = PIN0_ID,
		.DcMotor_DIR_PINB = PIN1_ID, .DCMotor_EN_PORT = PORTB_ID,
		.DcMotor_EN_PIN = PIN3_ID };

/*
 * Function: DcMotor_init
 * Description: Set up motor direction pins and enable pin.
 * Parameters: Pointer to structure of the Fan motor.
 * Return: void
 */
void DcMotor_init(DcMotor *Motor) {
	GPIO_setupPinDirection(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINA, PIN_OUTPUT);
	GPIO_setupPinDirection(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINB, PIN_OUTPUT);
#if(DCMOTOR_ENABLE_EN == TRUE)
	GPIO_setupPinDirection(Motor->DCMotor_EN_PORT, Motor->DcMotor_EN_PIN, PIN_OUTPUT);
#endif
}

/*
 * Function: DcMotor_Rotate
 * Description: Control motor rotation direction and speed.
 * Parameters: Pointer to structure of the Fan motor.
 * Return: void
 */
void DcMotor_Rotate(DcMotor *Motor, DcMotor_State state, uint8 speed) {
	PWM_Timer0_Start(speed); // Start PWM with specified speed

	switch (state) {
	case Clock_Wise:
		GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINA, LOGIC_HIGH);
		GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINB, LOGIC_LOW);
		break;
	case Anti_Clock_Wise:
		GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINA, LOGIC_LOW);
		GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINB, LOGIC_HIGH);
		break;
	default:
		DcMotor_STOP(Motor); // Stop motor if state is invalid
		break;
	}
}

/*
 * Function: DcMotor_STOP
 * Description: Stop the motor by setting direction pins to low.
 * Parameters: Pointer to structure of the Fan motor.
 * Return: void
 */
void DcMotor_STOP(DcMotor *Motor) {
	GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINA, LOGIC_LOW);
	GPIO_writePin(Motor->DcMotor_DIR_PORT, Motor->DcMotor_DIR_PINB, LOGIC_LOW);
}
