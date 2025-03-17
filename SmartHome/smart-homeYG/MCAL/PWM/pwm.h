/*
 * Module: ADC
 *
 * File Name: PWM.h
 *
 *  Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */
#ifndef PWM_H_
#define PWM_H_

/* Includes Standard Types */
#include "../std_types.h"

/*
 * Function to generate signal with a given duty cycle
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
