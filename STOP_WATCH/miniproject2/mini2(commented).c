/*
 * main.c
 *
 *  Created on: Fep 12, 2025
 *      Author: Youssef Gaessa
 *
 */

#include <avr/io.h>               // Include AVR I/O library for port operations
#include <util/delay.h>           // Include delay library
#include <avr/interrupt.h>        // Include interrupt library

	unsigned char num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0, togbit = 0, mode = 0;  // Variables for counters, toggle bit, and mode

void INT0_Init(void); //RESET
void INT1_Init(void); //PAUSE
void INT2_Init(void); //RESUME
void Timer1_compare_Init(void);  // Initialize Timer1
void disp_7seg(void);            // Display function for 7-segment display
void up_counter(void);           // Function for counting up
void down_counter(void);         // Function for counting down
void control_unit(void);         // Function to control the counter
void mode_control(void);         // Function to control the mode
void all_ports(void);            // Function to initialize all ports

int main()
{
	SREG |= (1 << 7);  // Enable global interrupt flag

	all_ports();            // Initialize all ports
	Timer1_compare_Init();  // Initialize Timer1 for counting
	INT0_Init();            // Initialize INT0 (RESET)
	INT1_Init();            // Initialize INT1 (PAUSE)
	INT2_Init();            // Initialize INT2 (RESUME)

	while (1)  // Main loop
	{
		if (togbit == 1)  // If toggle bit is set
		{
			if (mode == 0)  // If mode is 0 (up counting)
			{
				up_counter();  // Call the function to count up
			}
			else  // If mode is 1 (down counting)
			{
				down_counter();  // Call the function to count down
			}
			togbit = 0;  // Reset toggle bit
		}
		disp_7seg();     // Display the counter on 7-segment display
		mode_control();   // Control mode switching
		control_unit();   // Control the counter
	}
};

void INT0_Init(void) //RESET
{
	MCUCR |= (1 << ISC01);    // Set INT0 to trigger on falling edge
	GICR |= (1 << INT0);     // Enable external interrupt 0

	DDRD &= ~(1 << 2);        // Set PD2 as input (INT0)
	PORTD |= (1 << 2);        // Enable pull-up resistor on PD2
}
ISR(INT0_vect)  // Interrupt service routine for INT0 (RESET)
{
	PORTD &= ~(1 << PD0);  // Turn off LED on PD0
	num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0;  // Reset counters
	GIFR |= (1 << INT1);  // Clear the interrupt flag for INT1
}
void INT1_Init(void) //PAUSE
{
	MCUCR |= (1 << ISC11) | (1 << ISC10);  // Set INT1 to trigger on any edge
	GICR |= (1 << INT1);                 // Enable external interrupt 1

	DDRD &= ~(1 << 3);  // Set PD3 as input (INT1)
}
ISR(INT1_vect)  // Interrupt service routine for INT1 (PAUSE)
{
	TCCR1B = 0;  // Stop Timer1
	GIFR |= (1 << INT1);  // Clear the interrupt flag for INT1
}
void INT2_Init(void) //RESUME
{
	GICR |= (1 << INT2);  // Enable external interrupt 2

	DDRB &= ~(1 << 2);     // Set PB2 as input (INT2)
	PORTB |= (1 << 2);     // Enable pull-up resistor on PB2
}
ISR(INT2_vect)  // Interrupt service routine for INT2 (RESUME)
{
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // Resume Timer1 with prescaler and CTC mode
	GIFR |= (1 << INT2);  // Clear the interrupt flag for INT2
}
void Timer1_compare_Init(void) //TIMER
{
	TCNT1 = 0;         // Initialize Timer1 counter
	OCR1A = 15624;     // Set compare value for 1 second (assuming 16 MHz clock)

	TIMSK |= (1 << OCIE1A);  // Enable Timer1 compare interrupt

	TCCR1A = (1 << FOC1A);   // Configure Timer1 for non-PWM mode
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);  // Configure Timer1 for CTC mode with prescaler 1024
}
ISR(TIMER1_COMPA_vect)  // Timer1 compare interrupt service routine
{
	togbit = 1;  // Set toggle bit to trigger counting
}

void disp_7seg(void)  // Display function for 7-segment display
{
	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X20);  // Set port A for the first digit
	PORTC = (PORTC & (0XF0)) | (num1 & (0X0F));  // Display the first digit

	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X10);  // Set port A for the second digit
	PORTC = (PORTC & (0XF0)) | (num2 & (0X0F));  // Display the second digit

	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X08);  // Set port A for the third digit
	PORTC = (PORTC & (0XF0)) | (num3 & (0X0F));  // Display the third digit

	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X04);  // Set port A for the fourth digit
	PORTC = (PORTC & (0XF0)) | (num4 & (0X0F));  // Display the fourth digit

	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X02);  // Set port A for the fifth digit
	PORTC = (PORTC & (0XF0)) | (num5 & (0X0F));  // Display the fifth digit

	_delay_ms(2);  // Small delay for display refresh
	PORTA = (PORTA & (0XC0)) | (0X01);  // Set port A for the sixth digit
	PORTC = (PORTC & (0XF0)) | (num6 & (0X0F));  // Display the sixth digit
}
void up_counter(void)  // Count up function
{
	if (!(num5 == 4 && num6 == 2))  // If not reached max value
	{
		if (num1 == 9)  // If first digit is 9
		{
			num1 = 0;  // Reset first digit
			if (num2 == 5)  // If second digit is 5
			{
				num2 = 0;  // Reset second digit
				if (num3 == 9)  // If third digit is 9
				{
					num3 = 0;  // Reset third digit
					if (num4 == 5)  // If fourth digit is 5
					{
						num4 = 0;  // Reset fourth digit
						if ((num6 != 2 && num5 != 9) || (num6 == 2 && num5 != 4))  // Check if max value reached
						{
							num5++;  // Increment fifth digit
						}
						else
						{
							num5 = 0;  // Reset fifth digit
							if (num6 != 2)  // If sixth digit is not 2
							{
								num6++;  // Increment sixth digit
							}
							else
							{
								num6 = 0;  // Reset sixth digit
							}
						}
					}
					else
						num4++;  // Increment fourth digit
				}
				else
					num3++;  // Increment third digit
			}
			else
				num2++;  // Increment second digit
		}
		else
			num1++;  // Increment first digit
	}
	else
	{
		num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 4, num6 = 2;  // Reset counter when max value is reached
	}
}
void down_counter(void)  // Count down function
{
	if (!(num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0 && num6 == 0))  // If not at zero
	{
		if (num1 == 0)  // If first digit is 0
		{
			num1 = 9;  // Set first digit to 9
			if (num2 == 0)  // If second digit is 0
			{
				num2 = 5;  // Set second digit to 5
				if (num3 == 0)  // If third digit is 0
				{
					num3 = 9;  // Set third digit to 9
					if (num4 == 0)  // If fourth digit is 0
					{
						num4 = 5;  // Set fourth digit to 5
						if (num5 != 0)  // If fifth digit is not 0
						{
							num5--;  // Decrement fifth digit
						}
						else
						{
							if (num6 != 0)  // If sixth digit is not 0
							{
								num6--;  // Decrement sixth digit
							}
						}
					}
					else
						num4--;  // Decrement fourth digit
				}
				else
					num3--;  // Decrement third digit
			}
			else
				num2--;  // Decrement second digit
		}
		else
			num1--;  // Decrement first digit
	}
	else
	{
		PORTD |= (1 << 0);  // Turn on LED on PD0 when counter reaches zero
	}
}
void control_unit(void)  // Control unit function that handles button presses and counter adjustments
{
	if ((TCCR1B == 0) && (mode == 1))  // Check if the timer is stopped and the mode is set to down counting
	{
		// If the button connected to PINB6 is pressed
		if (!(PINB & (1 << 6)))
		{
			// If the time is not at 4:2 (a special condition), increment the counter
			if (!(num5 == 4 && num6 == 2))
			{
				// Increment first digit and propagate carry if needed
				if (num1 == 9)
				{
					num1 = 0;
					// Increment second digit and propagate carry if needed
					if (num2 == 5)
					{
						num2 = 0;
						// Increment third digit and propagate carry if needed
						if (num3 == 9)
						{
							num3 = 0;
							// Increment fourth digit and propagate carry if needed
							if (num4 == 5)
							{
								num4 = 0;
								// Increment fifth and sixth digits with checks for 4:2 condition
								if ((num6 != 2 && num5 != 9) || (num6 == 2 && num5 != 4))
								{
									num5++;
								}
								else
								{
									num5 = 0;
									if (num6 != 2)
									{
										num6++;
									}
									else
									{
										num6 = 0;
									}
								}
							}
							else
								num4++;
						}
						else
							num3++;
					}
					else
						num2++;
				}
				else
					num1++;
			}
			// Reset counter to 4:2 if it exceeds certain limits
			else
			{
				num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 4, num6 = 2;
			}
			// Display the updated counter value
			while (!(PINB & (1 << 6)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}

		// If the button connected to PINB5 is pressed
		if (!(PINB & (1 << 5)))
		{
			// If the counter is not at zero, decrement the counter
			if (!(num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0 && num6 == 0))
			{
				// Decrement the first digit and propagate carry if needed
				if (num1 == 0)
				{
					num1 = 9;
					// Decrement the second digit and propagate carry if needed
					if (num2 == 0)
					{
						num2 = 5;
						// Decrement the third digit and propagate carry if needed
						if (num3 == 0)
						{
							num3 = 9;
							// Decrement the fourth digit and propagate carry if needed
							if (num4 == 0)
							{
								num4 = 5;
								// Decrement the fifth and sixth digits
								if (num5 != 0)
								{
									num5--;
								}
								else
								{
									if (num6 != 0)
									{
										num6--;
									}
								}
							}
							else
								num4--;
						}
						else
							num3--;
					}
					else
						num2--;
				}
				else
					num1--;
			}
			// Display the updated counter value
			while (!(PINB & (1 << 5)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}

		// If the button connected to PINB4 is pressed
		if (!(PINB & (1 << 4)))
		{
			// If the counter is not at 9:5:3:2 or 4:2, increment the counter
			if (!((num3 == 9 && num4 == 5 && num5 == 3 && num6 == 2) || (num5 == 4 && num6 == 2)))
			{
				// Increment the third digit and propagate carry if needed
				if (num3 == 9)
				{
					num3 = 0;
					// Increment the fourth digit and propagate carry if needed
					if (num4 == 5)
					{
						num4 = 0;
						// Increment the fifth and sixth digits with checks for 4:2 condition
						if ((num6 != 2 && num5 != 9) || (num6 == 2 && num5 != 4))
						{
							num5++;
						}
						else
						{
							num5 = 0;
							if (num6 != 2)
							{
								num6++;
							}
							else
							{
								num6 = 0;
								num1 = 0, num2 = 0;
							}
						}
					}
					else
						num4++;
				}
				else
					num3++;
			}
			// Reset counter to 4:2 if it exceeds certain limits
			else
			{
				num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 4, num6 = 2;
			}

			// Display the updated counter value
			while (!(PINB & (1 << 4)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}

		// Similar logic for buttons connected to PINB3, PINB1, and PINB0
		// Handle decrements and increments based on the pressed buttons

		if (!(PINB & (1 << 3)))
		{
			if (!((num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0 && num6 == 0) || (num3 == 0 && num4 == 0 && num5 == 0 && num6 == 0)))
			{
				if (num3 == 0)
				{
					num3 = 9;
					if (num4 == 0)
					{
						num4 = 5;
						if (num5 != 0)
						{
							num5--;
						}
						else
						{
							if (num6 != 0)
							{
								num6--;
							}
						}
					}
					else
						num4--;
				}
				else
					num3--;
			}
			while (!(PINB & (1 << 3)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}

		// Similarly for other buttons (PINB1 and PINB0), decrement or reset values
		if (!(PINB & (1 << 1)))
		{
			// Check conditions and adjust counter accordingly
			if (!((num5 == 4 && num6 == 2) || (num5 == 3 && num6 == 2)))
			{
				if ((num6 != 2 && num5 != 9) || (num6 == 2 && num5 != 4))
				{
					num5++;
				}
				else
				{
					num5 = 0;
					if (num6 != 2)
					{
						num6++;
					}
					else
					{
						num6 = 0;
					}
				}
			}
			else
			{
				num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 4, num6 = 2;
			}
			while (!(PINB & (1 << 1)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}

		// If button connected to PINB0 is pressed, decrement or reset the counter accordingly
		if (!(PINB & (1 << 0)))
		{
			if (!((num1 == 0 && num2 == 0 && num3 == 0 && num4 == 0 && num5 == 0 && num6 == 0) || (num5 == 0 && num6 == 0)))
			{
				if (num5 != 0)
				{
					num5--;
				}
				else
				{
					if (num6 != 0)
					{
						num6--;
						num5 = 9;
					}
					else
					{
						num6 = 2;
						num5 = 3;
					}
				}
			}
			while (!(PINB & (1 << 0)))  // Keep displaying while the button is pressed
			{
				disp_7seg();  // Call function to update 7-segment display
			}
		}
	}
}
void mode_control(void)  // Function to control the mode (toggle between two states)
{
	if (mode == 0)  // If the mode is currently set to 0
	{
		// Set PORTD pin 4 high, pin 5 low, and pin 0 low
		PORTD |= (1 << 4);
		PORTD &= ~(1 << 5);
		PORTD &= ~(1 << 0);
	}
	else  // If the mode is currently set to 1
	{
		// Set PORTD pin 5 high, pin 4 low
		PORTD |= (1 << 5);
		PORTD &= ~(1 << 4);
	}
	// Check if the button connected to PINB7 is pressed and if TCCR1B is 0 (timer is stopped)
	if (!(PINB & (1 << 7)) && (TCCR1B == 0))
	{
		// Toggle the mode (switch between 0 and 1)
		mode = !mode;
		// Wait until the button is released
		while (!(PINB & (1 << 7)))
		{
			disp_7seg();  // Keep displaying on the 7-segment display while waiting for button release
		}
	}
}
void all_ports(void)  // Function to configure all port directions and set initial states
{
	DDRC |= 0x0F;  // Set the lower 4 pins of PORTC (pins 0-3) as output
	DDRA |= 0x3F;  // Set the lower 6 pins of PORTA (pins 0-5) as output
	
	PORTC &= 0xF0;  // Set the upper 4 pins of PORTC (pins 4-7) to low (input)
	PORTA &= 0xC0;  // Set the upper 2 pins of PORTA (pins 6-7) to low (input)
	
	DDRD |= (1 << 4) | (1 << 5);  // Set pin 4 and pin 5 of PORTD as output
	PORTD &= ~(1 << 4) & (1 << 5);  // Set pin 4 and pin 5 of PORTD to low
	
	DDRB &= ~(1 << 0) & (1 << 1) & (1 << 3) & (1 << 4) & (1 << 5) & (1 << 6) & (1 << 7);  // Set pins 0, 1, 3, 4, 5, 6, 7 of PORTB as input
	PORTB |= (1 << 0) | (1 << 1) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);  // Set pins 0, 1, 3, 4, 5, 6, 7 of PORTB to high
	
	DDRD |= (1 << 0);  // Set pin 0 of PORTD as output
	PORTD &= ~(1 << 0);  // Set pin 0 of PORTD to low
}
