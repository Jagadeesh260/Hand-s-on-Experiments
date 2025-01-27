#include "stm32f4xx.h"



#define GPIOAEN     (1U<<0)
#define GPIOCEN     (1U<<2)


#define PIN5        (1U<<5)
#define PIN13       (1U<<13)

#define LED_PIN     PIN5
#define BTN_PIN     PIN13



int main(void)
{
	/*Enable clock for both the ports A and C*/
	RCC->AHB1ENR |=GPIOAEN;
	RCC->AHB1ENR |=GPIOCEN;

	/*Set PA5 as output*/
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*Set PC13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);
	while (1)
	{
		/*Check if BTN is pressed*/
		if (GPIOC->IDR & BTN_PIN)
		{
			/*Turn On led*/
		GPIOA->BSRR =(1U<<21);

		}
		else{
			/*Turn Off led*/

		GPIOA->BSRR =LED_PIN;
		}


	}

}
