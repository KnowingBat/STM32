#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"

#define GPIOAEN 	(1U<<0)
#define GPIOA_5		(1U<<5)
#define LED_PIN		GPIOA_5

static void usart2_callback();

char key;

int main(void){

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_interrupt();

	while(1){
	}

}

static void usart2_callback(){
	key = USART2->DR;

	if(key == '1'){
			GPIOA->ODR = LED_PIN;
	}else {
			GPIOA->ODR &= ~LED_PIN;
	}
}

void USART2_IRQHandler(){
	//CHekc if DR is empty
	if(USART2->SR & RXNE){
		usart2_callback();
	}
}
