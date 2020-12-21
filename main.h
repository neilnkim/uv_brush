/**************************************************
* Project
*
* Copyright
* All Rights Reserved by
*
* written by Neil
*
**************************************************/

#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <string.h>
#include <ctype.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include "version.h"

#ifndef ATMEGA_MAIN
	#define EXTERN extern
#else
	#define EXTERN
#endif

#define SYS_CLOCK        		4000000	//8000000 //14745600
#define TIMEOUT_COUNT_1M30SEC 	180 //90sec
#define TIMEOUT_COUNT_5MIN 		600 //300sec
#define TIMEOUT_COUNT_20MIN 	2400 //1200sec

#define STATE_UV 		0
#define STATE_WIND 		1
#define STATE_OFF 		2

#define sbi(port, bit) 	(port) |=  (1<<(bit))
#define cbi(port, bit) 	(port) &= ~(1<<(bit))

#define BIT(x) 	(1<<(x))
#define BIT0 		0x01
#define BIT1 		0x02
#define BIT2 		0x04
#define BIT3 		0x08
#define BIT4 		0x10
#define BIT5 		0x20
#define BIT6 		0x40
#define BIT7 		0x80
#define ZERO(x) 	0

#define _ON_  		1
#define _OFF_ 		0
#define _TRUE_  	1
#define _FALSE_ 	0
#define _OUT_ 		1
#define _IN_  		0
#define _HIGH_ 		1
#define _LOW_  		0



/*******************************************************************
	function prototypes
*******************************************************************/

#endif


