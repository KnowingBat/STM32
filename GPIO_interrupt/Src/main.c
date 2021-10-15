#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"
#include "exti.h"

#define GPIOAEN 		(1U<<0)
#define PIN5			(1U<<5)

#define LED_PIN 		PIN5

static void exti_callback(void);

int main(void){

	pc13_exti_init();
	uart2_init();

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	while(1){}
}

static void exti_callback(){
	printf("BTN Pressed...!\n");
	GPIOA->ODR ^= LED_PIN;
}

void EXTI15_10_IRQHandler(){
	if(EXTI->PR & LINE13){
		//Continue with IRQ
		//CLear PR Flag
		EXTI->PR |= LINE13;
		//Do something...
		exti_callback();
	}
}

