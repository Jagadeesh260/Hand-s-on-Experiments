//This is the structure method using the register name
//

#include <stdint.h>

#define PERIPH_BASE              (0X40000000UL)//peripheral address start form this.
#define AHB1PHERIPH_OFFSET       (0x00020000UL) // AHB1-Advanced High-performance Bus 1 ,
#define AHB1PHERIPH_BASE         (PERIPH_BASE +AHB1PHERIPH_OFFSET)//address of AHB1 start
#define GPIOA_OFFSET             (0x0000UL)

#define GPIOA_BASE                (AHB1PHERIPH_BASE +GPIOA_OFFSET ) //Start address of GPIO port A

#define RCC_OFFSET               (0x3800UL) //RCC-Reset and Clock Control
#define RCC_BASE                (AHB1PHERIPH_BASE + RCC_OFFSET) //Start address of RCC


#define GPIOAEN                  (1U<<0)//Shift 1 at position 0 i.e. 0b 0000 0000 0000 0000 0000 0000 0001


#define PIN                      (1U<<5)
#define LED_PIN                   PIN
#define __TO  volatile



typedef struct
{
	volatile uint32_t DUMMY[12]; /*!<to align other registers properly within the memory space.*/
	volatile uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
}RCC_Typedef;


typedef struct
{
	__TO uint32_t MODER;  /*!< GPIO port mode register,               Address offset: 0x00      */
	volatile uint32_t DUMMY[4]; /*!<to align other registers properly within the memory space.*/
	volatile uint32_t ODR;     /*!< GPIO port output data register,        Address offset: 0x14      */

}GPIO_Typedef;


#define RCC        ((RCC_Typedef*)RCC_BASE)
#define GPIOA      ((GPIO_Typedef*)GPIOA_BASE)

/*
 * (1U<<10)  // set only bit 10 to 1
 * &=~(1U<<11)// set only bit 11 to 0*/

int main(void){
	/*1. Enable clock to GPIOA*/


	RCC->AHB1ENR |= GPIOAEN;


	/*2. Set PA5 as output pin*/


	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		/*3. set PA5 high*/



		/*Experiment 4: Toggle LED*/

		GPIOA->ODR ^= LED_PIN;
		for(int i=0;i<1000000;i++){}

	}
}





