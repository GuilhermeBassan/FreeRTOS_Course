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
 *------------------------------------------------------------------------------*/

#include "TM4C123.h" // Device header

#define RED		(1U<<1)
#define BLUE	(1U<<2)
#define GREEN 	(1U<<3) // Green led is the bit 3
#define DELAY	2000000

void GPIO_Init(void);
void delay(int time);

int main()
{
	GPIO_Init();
	
	while(1)
	{
		GPIOF -> DATA ^= RED; // Toggle operator
		GPIOF -> DATA ^= GREEN; // Toggle operator
		GPIOF -> DATA ^= BLUE; // Toggle operator
		delay(DELAY);
	}
}


void GPIO_Init(void)
{
	SYSCTL -> RCGCGPIO |= (1U<<5); // Enabling the clock gate register
								   // 1U<<5 bit number 5 to the port F
	GPIOF -> DIR |= RED; // Direction register
	GPIOF -> DEN |= RED; // Digital Enable register
	GPIOF -> DIR |= GREEN; // Direction register
	GPIOF -> DEN |= GREEN; // Digital Enable register
	GPIOF -> DIR |= BLUE; // Direction register
	GPIOF -> DEN |= BLUE; // Digital Enable register
}

void delay(int time)
{
	int delay = 0;
	while(delay < time)
	{
		delay++;
	}
}