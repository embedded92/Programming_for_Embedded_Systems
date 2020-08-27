/*
 * #SAVAGE LOVE......
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
#include "queue.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
xQueueHandle xQueue1;

typedef struct {
	char ucMessageID;
	int ledNo;
	int ledState;
} messageTask1;

messageTask1 arr[20];

int delay[20] = { 150, 250, 150, 250, 500, 400, 250, 500, 250, 700, 150, 250,
		150, 250, 500, 400, 250, 500, 250, 700 };

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
#define LED0 0
#define LED1 1
#define LED2 2
#define DELAYCOUNT 20
/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, 1);
	Board_LED_Set(1, 1);
	Board_LED_Set(2, 1);
}

static void vTask1(void *pvParameters) {
	messageTask1 msg1;
	while (1) {
		if (xQueueReceive(xQueue1, &msg1, 100) == pdTRUE) {
			Board_LED_Set(msg1.ledNo, msg1.ledState);
		}
	}
}

static void vTask2(void *pvParameters) {
	while (1) {
		for (int i = 0; i < DELAYCOUNT; i++) {
			arr[i].ledNo = LED0;

			if (i % 2 == 0) {
				arr[i].ledState = 0;
			} else
				arr[i].ledState = 1;
			xQueueSendToBack(xQueue1, &arr[i], 10);

			vTaskDelay(delay[i]);
		}
	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief main routine for FreeRTOS blinky example
 * @return Nothing, function should not exit
 */
int main(void) {
	prvSetupHardware();

	xTaskCreate(vTask1, (signed char* ) "task1", configMINIMAL_STACK_SIZE, NULL,
			(tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);

	xTaskCreate(vTask2, (signed char* ) "task2", configMINIMAL_STACK_SIZE, NULL,
			(tskIDLE_PRIORITY + 1UL), (xTaskHandle *) NULL);
	/* Create a queue capable of containing 10 unsigned long values. */
	xQueue1 = xQueueCreate(10, sizeof(messageTask1));

	if (xQueue1 == 0) {
		return 1;
	}
	/* Start the scheduler */
	vTaskStartScheduler();
	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
