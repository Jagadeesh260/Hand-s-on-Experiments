
#include <stdint.h>
#include "stm32f4xx.h"

#define GPIOAEN     (1U<<0)
#define UART2EN     (1U<<17)


#define CR1_TE      (1U<<3)
#define CR1_UE      (1U<<13)
#define SR_TXE       (1U<<7)

#define SYS_FREQ    16000000
#define APB1_CLK    SYS_FREQ

#define UART_BAUDRATE   115200

static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);

void uar2_tx_init(void);
void uart2_write (int ch);

int main(void)
{

	uar2_tx_init();

	while (1)
	{
		uart2_write('Y');
		for(int i=0;i<10000000;i++){}

	}

}
void uart2_write (int ch)
{
	/*Make sure transmit data register is empty  */
	while(!(USART2->SR & SR_TXE)){}
	/*write to transmit data register*/
	USART2->DR =(ch & 0xFF);
}
void uar2_tx_init(void)
{
	/*Configuration UART gpio pin*/
	/*Enable clock access to gpioa*/
	RCC->AHB1ENR |= GPIOAEN;
	/*set PA2 to alternate function mode*/
	GPIOA->MODER |=(1U<<5);
	GPIOA->MODER &=~(1U<<4);
	/*set PA2 to alternate function to UART_Tx  AF7*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);

	/*Enable clock access to UART 2*/
	RCC->APB1ENR |= UART2EN;

	/*configure baudrate*/
	set_uart_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*configure the transfer direction  */
	USART2->CR1 |=CR1_TE;

	/*Enable UART*/
	USART2->CR1 |=CR1_UE;


}

static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div(PeriphClk,BaudRate);
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk +(BaudRate/2U))/BaudRate);
}
