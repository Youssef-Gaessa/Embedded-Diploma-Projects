/*
 * main.c
 *
 *  Created on: Fep 12, 2025
 *      Author: Youssef Gaessa
 *
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char num1=0,num2=0,num3=0,num4=0,num5=0,num6=0,togbit=0,mode=0;

void INT0_Init(void); //RESET
void INT1_Init(void); //PAUSE
void INT2_Init(void); //RESUME
void Timer1_compare_Init(void);
void disp_7seg(void);
void up_counter(void);
void down_counter(void);
void control_unit(void);
void mode_control(void);
void all_ports(void);

int main()
{
	SREG |= (1<<7);

	all_ports();
	Timer1_compare_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();

	while(1)
	{
		if(togbit==1)
		{
			if(mode == 0)
			{
				up_counter();
			}
			else
			{
				down_counter();
			}
			togbit=0;
		}
		disp_7seg();
		mode_control();
		control_unit();
	}
};

void INT0_Init(void) //RESET
{
	MCUCR |=  (1<<ISC01);
	GICR  |=  (1<<INT0);

	DDRD  &=~ (1<<2);
	PORTD |=  (1<<2);
}
ISR(INT0_vect)
{
	PORTD &=~ (1<<PD0);
	num1=0,num2=0,num3=0,num4=0,num5=0,num6=0;
	GIFR |= (1<<INT1);
}
void INT1_Init(void) //PAUSE
{
	MCUCR |=  (1<<ISC11) | (1<<ISC10);
	GICR  |=  (1<<INT1);

	DDRD  &=~ (1<<3);
}
ISR(INT1_vect)
{
	TCCR1B = 0;
	GIFR |= (1<<INT1);
}
void INT2_Init(void) //RESUME
{
	GICR  |=   (1<<INT2);

	DDRB  &=~  (1<<2);
	PORTB |=   (1<<2);
}
ISR(INT2_vect)
{
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
	GIFR |= (1<<INT2);
}
void Timer1_compare_Init(void) //TIMER
{
	TCNT1=0;
	OCR1A=15624;

	TIMSK |= (1<<OCIE1A);

	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12)|(1<<CS12)|(1<<CS10);
}
ISR(TIMER1_COMPA_vect)
{
	togbit=1;
}

void disp_7seg(void)
{
	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X20);
	PORTC = (PORTC&(0XF0)) | (num1&(0X0F));

	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X10);
	PORTC = (PORTC&(0XF0)) | (num2&(0X0F));

	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X08);
	PORTC = (PORTC&(0XF0)) | (num3&(0X0F));

	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X04);
	PORTC = (PORTC&(0XF0)) | (num4&(0X0F));

	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X02);
	PORTC = (PORTC&(0XF0)) | (num5&(0X0F));

	_delay_ms(2);
	PORTA = (PORTA&(0XC0)) | (0X01);
	PORTC = (PORTC&(0XF0)) | (num6&(0X0F));
}
void up_counter(void)
{
	if(!( num5==4 && num6==2))
	{
		if(num1==9)
		{
			num1=0;
			if(num2==5)
			{
				num2=0;
				if(num3==9)
				{
					num3=0;
					if(num4==5)
					{
						num4=0;
						if(( num6 !=2 && num5!=9) || ( num6 ==2 && num5!=4))
						{
							num5++;
						}
						else
						{
							num5=0;
							if(num6!=2)
							{
								num6++;
							}
							else
							{
								num6=0;
							}
						}
					}else
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
	else
	{
		num1=0 , num2=0 , num3=0 , num4=0 , num5=4 , num6=2;
	}
}
void down_counter(void)
{
	if(!(num1==0 && num2==0 && num3==0 && num4==0 && num5==0 && num6==0))
	{
		if(num1==0)
		{
			num1=9;
			if(num2==0)
			{
				num2=5;
				if(num3==0)
				{
					num3=9;
					if(num4==0)
					{
						num4=5;
						if(num5!=0)
						{
							num5--;
						}
						else
						{
							if(num6!=0)
							{
								num6--;
							}
						}
					}else
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
	else
	{
		PORTD|= (1<<0);
	}
}
void control_unit(void)
{
	if((TCCR1B == 0) && (mode==1))
	{
		if(!(PINB&(1<<6)))
		{
			if(!( num5==4 && num6==2))
			{
				if(num1==9)
				{
					num1=0;
					if(num2==5)
					{
						num2=0;
						if(num3==9)
						{
							num3=0;
							if(num4==5)
							{
								num4=0;
								if(( num6 !=2 && num5!=9) || ( num6 ==2 && num5!=4))
								{
									num5++;
								}
								else
								{
									num5=0;
									if(num6!=2)
									{
										num6++;
									}
									else
									{
										num6=0;
									}
								}
							}else
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
			else
			{
				num1=0 , num2=0 , num3=0 , num4=0 , num5=4 , num6=2;
			}
			while(!(PINB&(1<<6)))
			{
				disp_7seg();
			}
		}
		if(!(PINB&(1<<5)))
		{
			if(!(num1==0 && num2==0 && num3==0 && num4==0 && num5==0 && num6==0))
			{
				if(num1==0)
				{
					num1=9;
					if(num2==0)
					{
						num2=5;
						if(num3==0)
						{
							num3=9;
							if(num4==0)
							{
								num4=5;
								if(num5!=0)
								{
									num5--;
								}
								else
								{
									if(num6!=0)
									{
										num6--;
									}
								}
							}else
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
			while(!(PINB&(1<<5)))
			{
				disp_7seg();
			}
		}
		if(!(PINB&(1<<4)))
		{
			if(!((num3==9 && num4==5 && num5==3 && num6==2)||(num5==4 && num6==2)))
			{
				if(num3==9)
				{
					num3=0;
					if(num4==5)
					{
						num4=0;
						if(( num6 !=2 && num5!=9) || ( num6 ==2 && num5!=4))
						{
							num5++;
						}
						else
						{
							num5=0;
							if(num6!=2)
							{
								num6++;
							}
							else
							{
								num6=0;
								num1=0 , num2=0;
							}
						}
					}else
						num4++;
				}
				else
					num3++;
			}
			else
			{
				num1=0 , num2=0 , num3=0 , num4=0 , num5=4 , num6=2;
			}

			while(!(PINB&(1<<4)))
			{
				disp_7seg();
			}

		}
		if(!(PINB&(1<<3)))
		{
			if(!((num1==0 && num2==0 && num3==0 && num4==0 && num5==0 && num6==0)||(num3==0 && num4==0 && num5==0 && num6==0)))
			{
				if(num3==0)
				{
					num3=9;
					if(num4==0)
					{
						num4=5;
						if(num5!=0)
						{
							num5--;
						}
						else
						{
							if(num6!=0)
							{
								num6--;
							}
						}
					}else
						num4--;
				}
				else
					num3--;
			}
			while(!(PINB&(1<<3)))
			{
				disp_7seg();
			}
		}
		if(!(PINB&(1<<1)))
		{
			if(!((num5==4 && num6==2) || (num5==3 && num6==2)))
			{
				if(( num6 !=2 && num5!=9) || ( num6 ==2 && num5!=4))
				{
					num5++;
				}
				else
				{
					num5=0;
					if(num6!=2)
					{
						num6++;
					}
					else
					{
						num6=0;
					}
				}
			}
			else
			{
				num1=0 , num2=0 , num3=0 , num4=0 , num5=4 , num6=2;
			}
			while(!(PINB&(1<<1)))
			{
				disp_7seg();
			}
		}
		if(!(PINB&(1<<0)))
		{
			if(!((num1==0 && num2==0 && num3==0 && num4==0 && num5==0 && num6==0)||(num5==0 && num6==0)))
			{
				if(num5!=0)
				{
					num5--;
				}
				else
				{
					if(num6!=0)
					{
						num6--;
						num5=9;
					}
					else
					{
						num6=2;
						num5=3;
					}
				}

			}
			while(!(PINB&(1<<0)))
			{
				disp_7seg();
			}
		}
	}
}
void mode_control(void)
{
	if(mode == 0)
	{
		PORTD |=  (1<<4);
		PORTD &=~ (1<<5);
		PORTD&=~ (1<<0);
	}
	else
	{
		PORTD |=  (1<<5);
		PORTD &=~ (1<<4);
	}
	if(!(PINB&(1<<7)) && (TCCR1B ==0))
	{
		mode  =! mode;
		while(!(PINB&(1<<7)))
		{
			disp_7seg();
		}
	}
}
void all_ports(void)
{
	DDRC |= 0X0F;
	DDRA |= 0X3F;

	PORTC &= 0XF0;
	PORTA &= 0XC0;

	DDRD |=(1<<4)|(1<<5);
	PORTD &=~(1<<4)&(1<<5);

	DDRB &=~ (1<<0) & (1<<1) & (1<<3) & (1<<4) & (1<<5) & (1<<6) & (1<<7);
	PORTB |= (1<<0) | (1<<1) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7);;

	DDRD |= (1<<0);
	PORTD &=~ (1<<0);
}
