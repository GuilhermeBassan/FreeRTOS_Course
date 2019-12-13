/*--------------------------------------------------------------------------------
 *
 *	Guilherme Bassan
 *
 *	Turning a usual program into RTOS
 *	Lesson 02 - Task creation
 *
 *------------------------------------------------------------------------------*/
 
#include "TM4C123.h"                    // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#define RED		(1U<<1)
#define BLUE	(1U<<2)
#define GREEN 	(1U<<3) // Green led is the bit 3

#define DELAY 200000

void vBlueLedControllerTask(void *pvParameters);
//void vRedLedControllerTask(void *pvParameters);
//void vGreenLedControllerTask(void *pvParameters);

void GPIO_Init(void);
void delay(int time);

int main()
{
	GPIO_Init();
	
	xTaskCreate(vBlueLedControllerTask, // function to be called (the 'v' denotes it's a void)
				"Blue LED Controller",	// Descriptive title for debug
				100,	// Heap size
				NULL,	// No parameters will be passed on to the function
				1,		// Priority
				NULL);	// No handle will be necessary
/*	
	xTaskCreate(vRedLedControllerTask, 	// function to be called (the 'v' denotes it's a void)
				"red LED Controller",	// Descriptive title for debug
				100,	// Heap size
				NULL,	// No parameters will be passed on to the function
				1,		// Priority
				NULL);	// No handle will be necessary
	
	xTaskCreate(vGreenLedControllerTask, // function to be called (the 'v' denotes it's a void)
				"Green LED Controller",	 // Descriptive title for debug
				100,	// Heap size
				NULL,	// No parameters will be passed on to the function
				1,		// Priority
				NULL);	// No handle will be necessary
	*/			
	vTaskStartScheduler();
	
	while(1) {}
}

void vBlueLedControllerTask(void *pvParameters)
{
	//int i;
	while(1)
	{
		GPIOF -> DATA ^= BLUE; // Toggle operator
		//for(i = 0; i < DELAY; i++) {}
		delay(DELAY);
	}
}
/*
void vRedLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		GPIOF -> DATA ^= RED; // Toggle operator
		for(i = 0; i < DELAY; i++) {}
	}
}

void vGreenLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		GPIOF -> DATA ^= GREEN; // Toggle operator
		for(i = 0; i < DELAY; i++) {}
	}
}
*/
void GPIO_Init(void)
{
	SYSCTL -> RCGCGPIO |= (1U<<5); // Enabling the clock gate register
								   // 1U<<5 bit number 5 to the port F
	GPIOF -> DIR |= RED;	// Direction register
	GPIOF -> DEN |= RED;	// Digital Enable register
	
	GPIOF -> DIR |= GREEN;	// Direction register
	GPIOF -> DEN |= GREEN;	// Digital Enable register
	
	GPIOF -> DIR |= BLUE;	// Direction register
	GPIOF -> DEN |= BLUE;	// Digital Enable register
}

void delay(int time)
{
	int delay = 0;
	while(delay < time)
	{
		delay++;
	}
}

