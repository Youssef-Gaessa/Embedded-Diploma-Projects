/*
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Created on: 9 Mar 2025
 *
 * Author: Youssef Gaessa
 */

#include "../common_macros.h"
#include "../GPIO/gpio.h"
#include "ADC.h"
#include "avr/io.h"

void ADC_init(void) {
	/* internal 2.56 */
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);

	/* Enable ADC */
	SET_BIT(ADCSRA, ADEN);

	/* Pre-scaler 128 */
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
}

uint16 ADC_readChannel(uint8 ch_num) {
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x1F); 	/* Insert Channel Number */
	SET_BIT(ADCSRA, ADSC);						/* Start Conversion */
	while (GET_BIT(ADCSRA,ADIF) == 0);			/* Pollin Until ADIF = 1 */
	SET_BIT(ADCSRA, ADIF);						/* Clear ADIF Flag */
	return ADC;									/* Return Digital Value */
}
