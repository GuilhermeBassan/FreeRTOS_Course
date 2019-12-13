/*--------------------------------------------------------------------------------
 *
 *	Guilherme Bassan
 *
 *	Turning a usual program into RTOS
 *	Lesson 01 - blinky
 *
 *	TM4C123GH6PM Port Bits:
 *	PORTA - 1U<<0
 *	PORTB - 1U<<1
 *	PORTC - 1U<<2
 *	PORTD - 1U<<3
 *	PORTE - 1U<<4
 *	PORTF - 1U<<5
 *
 *	1U - Input 0U - Output
 * 
 *  The code did not work as expected - it only runs with one of the tasks active
 *  Awaiting on support from the teacher or the community. 
 * 
 *------------------------------------------------------------------------------*/

#include "TM4C123.h" // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#define RED		(1U<<1)
#define BLUE	(1U<<2)
#define GREEN 	(1U<<3) // Green led is the bit 3
#define DELAY	2000000

void blueLedControllerTask(void *pvParameters);
//void redLedControllerTask(void *pvParameters);
//void greenLedControllerTask(void *pvParameters);

void GPIO_Init(void);
void delay(int time);

int main()
{
	GPIO_Init();
	
	xTaskCreate(blueLedControllerTask, // The function to be called 
				"Blue Led Controller", // Name of the function
				100,	// Stack size (100 * 32 bits | 100 * 4 bytes | 100 * word)
				NULL,	// Parameter assigned to task
				1,		// Task priority
				NULL);	// Task handle
	//xTaskCreate(redLedControllerTask, // The function to be called 
	//			"RED Led Controller", // Name of the function
	//			100,	// Stack size (100 * 32 bits | 100 * 4 bytes | 100 * word)
	//			NULL,	// Parameter assigned to task
	//			1,		// Task priority
	//			NULL);	// Task handle
	//xTaskCreate(greenLedControllerTask, // The function to be called 
	//			"Green Led Controller", // Name of the function
	//			100,	// Stack size (100 * 32 bits | 100 * 4 bytes | 100 * word)
	//			NULL,	// Parameter assigned to task
	//			1,		// Task priority
	//			NULL);	// Task handle
	
	vTaskStartScheduler();
	
	while(1)
	{ }
}

void blueLedControllerTask(void *pvParameters)
{
	while(1)
	{
		GPIOF -> DATA ^= BLUE; // Toggle operator
		delay(DELAY);
	}
}

//void redLedControllerTask(void *pvParameters)
//{
//	while(1)
//	{
//		GPIOF -> DATA ^= RED; // Toggle operator
//		delay(DELAY);
//	}
//}

//void greenLedControllerTask(void *pvParameters)
//{
//	while(1)
//	{
//		GPIOF -> DATA ^= GREEN; // Toggle operator
//		delay(DELAY);
//	}
//}

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
