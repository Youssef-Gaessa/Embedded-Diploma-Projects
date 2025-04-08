/*
 * LCD.c
 *
 *  Created on: 3 Mar 2025
 *      Author: Youssef Gaessa
 */

#include "LCD.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/common_macros.h"
#include <util/delay.h>
#include <stdlib.h>

void LCD_SendCommand(uint8 Command) {
	/* Set RS pin to zero */
	GPIO_writePin(LCD_RS_PORT, LCD_RS_Pin, LOGIC_LOW);
	_delay_ms(1); /* Delay 1 us */
	/* Set Enable to LOGIC_HIGH */
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);
	/* Send Command*/
#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(Command, 4));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(Command, 5));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(Command, 6));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(Command, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(Command, 0));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(Command, 1));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(Command, 2));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(Command, 3));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT, Command);
	_delay_ms(1); /* Delay 1 us */
	/* Set Enable to zero */
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	/* Delay 1 us */
	_delay_ms(1);
#endif
}
void LCD_DisplayCharacter(uint8 Data) {
	/* Set RS pin to zero */
	GPIO_writePin(LCD_RS_PORT, LCD_RS_Pin, LOGIC_HIGH);
	_delay_ms(1); /* Delay 1 us */
	/* Set Enable to LOGIC_HIGH */
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);
	/* Send Command*/
#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(Data, 4));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(Data, 5));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(Data, 6));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(Data, 7));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT, LCD_DB4_PIN, GET_BIT(Data, 0));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB5_PIN, GET_BIT(Data, 1));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB6_PIN, GET_BIT(Data, 2));
	GPIO_writePin(LCD_DATA_PORT, LCD_DB7_PIN, GET_BIT(Data, 3));
	_delay_ms(1);
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	_delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(LCD_DATA_PORT, Data);
	_delay_ms(1); /* Delay 1 us */
	/* Set Enable to zero */
	GPIO_writePin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, LOGIC_LOW);
	/* Delay 1 us */
	_delay_ms(1);
#endif
}

void LCD_init(void) {
	GPIO_setupPinDirection(LCD_RS_PORT, LCD_RS_Pin, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_ENABLE_PORT, LCD_ENABLE_PIN, PIN_OUTPUT);
	_delay_ms(20);
#if (LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DB4_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DB5_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DB6_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT, LCD_DB7_PIN, PIN_OUTPUT);

	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
	LCD_SendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
	LCD_SendCommand(LCD_CURSOR_OFF);
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_DisplayString(const uint8 *string) {
	uint8 counter = 0;
	for (counter = 0; string[counter] != '\0'; counter++) {
		LCD_DisplayCharacter(string[counter]);
	}
}

void LCD_MoveCursor(uint8 row, uint8 col) {
	uint8 lcd_memory_address;
	switch (row) {
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col + 0x40;
		break;
	case 2:
		lcd_memory_address = col + 0x10;
		break;
	case 3:
		lcd_memory_address = col + 0x50;
		break;
	}
	LCD_SendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_DisplayStringRowColumn(uint8 row, uint8 col, const uint8 *Str) {
	LCD_MoveCursor(row, col);
	LCD_DisplayString(Str);
}

void LCD_intgerToString(int data) {
	char buff[16];
	itoa(data, buff, 10);
	LCD_DisplayString(buff);
}

void LCD_clearScreen(void) {
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}
