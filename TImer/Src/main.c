#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

#define GPIOAEN 		(1U<<0)
#define PIN5			(1U<<5)

#define LED_PIN 		PIN5

int main(void){

	uart2_init();

	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	tim2_1hz_init();

	while(1){
		while(!(TIM2->SR & SR_UIF)); //Wait until count flag is reached
		//Clear UIF
		TIM2->SR &= ~SR_UIF;
		printf("A second passed with timer !!\n");
		GPIOA->ODR ^= LED_PIN;
	}
}
