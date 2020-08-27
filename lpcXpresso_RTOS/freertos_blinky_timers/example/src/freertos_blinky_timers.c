/*
 * @brief FreeRTOS Blinky example
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
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
xTimerHandle timerHndl1Sec;
int red_led_state = 0;  //ON
int green_led_state = 1; //OFF
int blue_led_state = 1; //OFF
bool req_update = true; //when update is required

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	//Board_LED_Set(0, false);
	//Board_LED_Set(1, false);
	//Board_LED_Set(2, false);
}
static void vTimerCallback1SecExpired(xTimerHandle pxTimer) {
	//GPIO_PortToggle(BOARD_INITPINS_LED_RED_GPIO, 1<<BOARD_INITPINS_LED_RED_PIN); /* toggle red LED */
	if (red_led_state == 0) {
		red_led_state = 1;  //off
		green_led_state = 0;  //on

	} else if (green_led_state == 0) {
		green_led_state = 1;
		blue_led_state = 0;
	} else {
		blue_led_state = 1;
		red_led_state = 0;
	}
	req_update = true;
}
/* LED1 toggle thread */
static void vLEDTask1(void *pvParameters) {

	while (1) {
		if (req_update == true) {
			Board_LED_Set(0, red_led_state);
			Board_LED_Set(1, green_led_state);
			Board_LED_Set(2, blue_led_state);
			req_update = false;
		}
		vTaskDelay(10);
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void) {
	prvSetupHardware();

	xTaskCreate(vLEDTask1, (signed char* ) "vTaskLed1",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	timerHndl1Sec = xTimerCreate("timer1Sec", /* name */
	(1000), /* period/time */
	pdTRUE, /* auto reload */
	(void*) 0, /* timer ID */
	vTimerCallback1SecExpired); /* callback */

	if (timerHndl1Sec == NULL) {
		for (;;)
			; /* failure! */
	}

	if (xTimerStart(timerHndl1Sec, 0) != pdPASS) {
		for (;;)
			; /* failure!?! */
	}
	/* Start the scheduler */
	vTaskStartScheduler();
	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
