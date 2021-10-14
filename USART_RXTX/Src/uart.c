#include "uart.h"

#define GPIOAEN 	(1U<<0)
#define USARTEN2 	(1U<<17)
#define SYS_FREQ 	16000000UL
#define APB1_CLK	SYS_FREQ
#define BAUD 		115200
#define CR1_TE		(1U<<3)
#define UE 			(1U<<13)
#define TXE			(1U<<7)
#define CR1_RE		(1U<<2)
#define RXNE		(1U<<5)

static void uart_set_baud(USART_TypeDef *USARTx, uint32_t clk,uint32_t baud);
static uint16_t compute_uart_baud(uint32_t clk, uint32_t baud);
void uart2_write(uint8_t ch);

int __io_putchar(uint8_t ch){
	uart2_write(ch);
	return ch;
}

void uart2_init(){
	//COnfigure uart gpio pin
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA2 to alternate function mode
	//Set PA2 alternate function to AF07
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	GPIOA->AFR[0] |= (7U<<8);
	GPIOA->AFR[0] &= ~(1U<<11);

	//Set PA3 to alternate function mode
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	GPIOA->AFR[0] |= (7U<<12);
	GPIOA->AFR[0] &= ~(1U<<15);

	//Enable clock access to RCC_APB1ENR
	RCC->APB1ENR = USARTEN2;
	//Set the Baudrate
	uart_set_baud(USART2, APB1_CLK, BAUD);
	//TX enable, m=8 BIT word
	USART2->CR1 = (CR1_TE | CR1_RE);
	USART2->CR1 |= UE;
	//RX Enable
}

char uart2_read(){
	//COntrol if receive data reg. is no empty
	while(!(USART2->SR & RXNE));
	return USART2->DR;
}

void uart2_write(uint8_t ch){
	//COntrol if transmit data register is empty
	while(!(USART2->SR & TXE));
	//Transmit to data register
	USART2->DR = (ch & 0XFF);
}

static void uart_set_baud(USART_TypeDef *USARTx, uint32_t clk,uint32_t baud){
	USARTx->BRR = compute_uart_baud(clk,baud);
}

static uint16_t compute_uart_baud(uint32_t clk, uint32_t baud){
	return ((clk + (baud/2U))/baud);
}

