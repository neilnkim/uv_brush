/**************************************************
* Project
*
* Copyright
* All Rights Reserved by ~
*
* written by Neil
*
**************************************************/

#define ATMEGA_MAIN
#include "main.h"

//----------------------------------------------------------------------------
/*
	B0: input; 	toggle switch
	B1: output; 	output_power; 	initially L; toggle with B0
	B2: output; 	inv_output_power; 	initially H; toggle with B0
	B3: output; 	sys_power_control; initially H; L if timeout
	B4: input; 	NC
	B5: input; 	RESET
*/

#include <avr/interrupt.h>


volatile int timer_overflow_count = 0;
int g_state;

ISR(TIM0_OVF_vect) {
	timer_overflow_count++;
}

int init_gpio(void)
{
	DDRB = 0b00011001;
	PORTB= 0b00011001;

	return 0;
}

int init_timer(void)
{
	// prescale timer to 1/1024th the clock rate
	TCCR0B |= (1<<CS02) | (1<<CS00);

	// enable timer overflow interrupt
	TIMSK0 |=1<<TOIE0;

	return 0;
}

#if 0
void delay_10us(unsigned short time_ms)
{
	register unsigned short i, j;
	for(j=0;j<10;j++)
	{
		for(i=0; i<time_ms; i++)
		{
			asm volatile(" PUSH  R0 ");
			asm volatile(" POP   R0 ");
		}
	}
}
#endif

void delay_1ms(unsigned short time_ms)
{
	register unsigned short i, j;
	for(j=0;j<50;j++)
	{
		for(i=0; i<time_ms; i++)
		{
			asm volatile(" PUSH  R0 ");
			asm volatile(" POP   R0 ");
		}
	}
}

void set_led_pwr_en(int st)
{
	if(st)
	{
		PORTB |= BIT0;
	}
	else
	{
		PORTB &= ~BIT0;
	}
}

void set_led_en(unsigned char st)
{
	if(st)
	{
		PORTB |= BIT3;
	}
	else
	{
		PORTB &= ~BIT3;
	}
}

void set_fan_en(unsigned char st)
{
	if(st)
	{
		PORTB |= BIT4;
	}
	else
	{
		PORTB &= ~BIT4;
	}
}


int main(void)
{
	init_gpio();
	init_timer();
	sei();

	g_state = STATE_UV;
	set_led_pwr_en(_ON_);
	set_led_en(_ON_);
	set_fan_en(_ON_);

	while(1)
	{
		delay_1ms(10);
		switch(g_state)
		{
			case STATE_UV:
				set_led_pwr_en(_ON_);
				set_led_en(_ON_);
				set_fan_en(_ON_);

				if(timer_overflow_count > TIMEOUT_COUNT_5MIN)
				{
					g_state = STATE_WIND;
					timer_overflow_count = 0;
				}
				break;

			case STATE_WIND:
				set_led_pwr_en(_OFF_);
				set_led_en(_OFF_);
				set_fan_en(_ON_);

				if(timer_overflow_count > TIMEOUT_COUNT_20MIN)
				{
					g_state = STATE_OFF;
					timer_overflow_count = 0;
				}
				break;

			case STATE_OFF:
			default:
				set_led_pwr_en(_OFF_);
				set_led_en(_OFF_);
				set_fan_en(_OFF_);

				sei(); // Enable global interrupts
				set_sleep_mode(SLEEP_MODE_PWR_DOWN);
				sleep_mode();
				sleep_disable();

				break;
		}
	}

	return 0;
}


