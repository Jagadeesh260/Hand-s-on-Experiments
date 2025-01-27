// LED Blink for STM32F446RE MCU
// Requirements : MCU's Data sheet, Reference manual and user manual Nucleo 64 boards



#define PERIPH_BASE              (0X40000000UL)//peripheral address start form this.
#define AHB1PHERIPH_OFFSET       (0x00020000UL) // AHB1-Advanced High-performance Bus 1 ,
#define AHB1PHERIPH_BASE         (PERIPH_BASE +AHB1PHERIPH_OFFSET)//address of AHB1 start
#define GPIOA_OFFSET             (0x0000UL)

#define GPIOA_BASE                (AHB1PHERIPH_BASE +GPIOA_OFFSET ) //Start address of GPIO port A

#define RCC_OFFSET               (0x3800UL) //RCC-Reset and Clock Control
#define RCC_BASE                (AHB1PHERIPH_BASE + RCC_OFFSET) //Start address of RCC

#define AHB1EN_R_OFFSET          (0x30) //RCC AHB1 peripheral clock enable register
#define RCC_AHB1EN_R             (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET            (0x00UL) //GPIOA Mode register
#define GPIOA_MODE_R             (*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET              (0x14UL) //GPIO port output data register
#define GPIOA_OD_R               (*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN                  (1U<<0)//Shift 1 at position 0 i.e. 0b 0000 0000 0000 0000 0000 0000 0001


#define PIN                      (1U<<5)
#define LED_PIN                   PIN


/*
 * (1U<<10)  // set only bit 10 to 1
 * &=~(1U<<11)// set only bit 11 to 0*/

int main(void){
	/*1. Enable clock to GPIOA*/
	RCC_AHB1EN_R |= GPIOAEN;


	/*2. Set PA5 as output pin*/
	GPIOA_MODE_R |= (1U<<10);  // set only bit 10 to 1
	GPIOA_MODE_R &=~(1U<<11);//set only bit 11 to 0

	while(1)
	{
		/*3. set PA5 high*/

		//GPIOA_OD_R |= LED_PIN;

		/*Experiment 4: Toggle LED*/
		GPIOA_OD_R ^= LED_PIN;
		for(int i=0;i<100000;i++){}

	}
}





