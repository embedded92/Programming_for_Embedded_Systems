/*
 * @brief Blinky example using sysTick
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define TICKRATE_HZ1 (10)	/* 10 ticks per second */
//unsigned short int which_LED=0;
//static int which_LED;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	/*bool st_R, st_G, st_B; //states of RED GREEN n BLUE LEDs
	st_R= Board_LED_Test(0);
	st_G= Board_LED_Test(1);
	st_B= Board_LED_Test(2);

	if ((st_R== true) | (st_R==1))
	{
		Board_LED_Toggle(0);
	}
	else if ((st_G== true) | (st_G==1))
	{
		Board_LED_Toggle(1);
		}
	else if ((st_B== true) | (st_B==1))
		{
			Board_LED_Toggle(2);
			}
	else{
	*/
	//RED on--wait--off--GREEN on--wait--off--BLUE 0n--wait--off REPEAT
	int c=1;
	Board_LED_Set(0, 0);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);
	Board_LED_Set(0,  1);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);

	Board_LED_Set(1, 0);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);
	Board_LED_Set(1,  1);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);

	Board_LED_Set(2, 0);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);
	Board_LED_Set(2,  1);
		for(c=1;c<1000;c++)
			for(int i=0;i<7000; i++);
	}


/**
 * @brief	main routine for systick example
 * @return	Function should not exit.
 */
int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

	/* LEDs toggle in interrupt handlers */
	while (1) {
		__WFI();
	}

	return 0;
};


