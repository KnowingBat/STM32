#include "exti.h"

#define GPIOCEN 		(1U<<2)
#define SYSCFGEN		(1U<<14)

void pc13_exti_init(){
	//Disable global interrupt
	__disable_irq();
	//Enable clock access to GPIOC
	RCC->AHB1ENR |= GPIOCEN;
	RCC->APB2ENR |= SYSCFGEN;
	//sET PC13 as input
	GPIOC->MODER &= ~((1U<<26)|(1U<<27));
	//Enable clocka ccess to SYSCFG
	//Select PORTC for EXTI13
	SYSCFG->EXTICR[3] |= (1U<<5);
	//Unmask EXTI13
	EXTI->IMR |= (1U<<13);
	//Select falling edge trigger
	EXTI->FTSR |= (1U<<13);
	//Enable exti line NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	//enable global interrupt
	__enable_irq();
}



