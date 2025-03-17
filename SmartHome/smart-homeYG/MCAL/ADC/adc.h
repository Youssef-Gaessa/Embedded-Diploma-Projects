/*
 * Module: ADC
 *
 * File Name: ADC.h
 *
 *  Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */
#ifndef ADC_H_
#define ADC_H_
/*
 * Include Standard Types
 */
#include  "../std_types.h"

/*
 * Definitions
 */
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56
/*
 * Functions
 */

/* Function to Initialize ADC */
void ADC_init(void);

/* Function to read the analog signal from a given channel */
uint16 ADC_readChannel(uint8 ch_num);

#endif /* ADC_H_ */
