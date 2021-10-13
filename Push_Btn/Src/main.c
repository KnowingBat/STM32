#include "stm32f411xe.h"

#define GPIOAEN 	(1U<<0)
#define GPIOPC13	(1U<<2)
#define PIN5 		(1U<<5)
#define LED_PIN		PIN5
#define PIN13 		(1U<<13)
#define PUSH_BTN	PIN13

int main(void){
	//Enable clock access to LED and USER_BTN
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOPC13;

	GPIOA -> MODER |= (1U<<10);

	GPIOA->MODER &= ~(1U<<11);

	//sET pc13 as input pin
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	while(1){
		if(GPIOC->IDR & PUSH_BTN){
		GPIOA->BSRR = LED_PIN;
		} else {
		GPIOA->BSRR = (1U<<21);
		}
	}
}
