#include "stm32f4xx.h"
#include "adc.h"

#define ADC1EN		(1U<<8)
#define GPIOAEN		(1U<<0)
#define ADC_CH1  	(1U<<0)
#define ADC_SEQ_LEN1	0x00
#define ADON 		(1U<<0)
#define SWSTART 	(1U<<30)
#define CONT		(1U<<1)
#define EOC			(1U<<1)
#define EOCIE		(1U<<5)

void adc_init(){
	//Disable Interrupt
	__disable_irq();
	//Enable APB2 clock access
	RCC->APB2ENR |= ADC1EN;
	//Enable gpio for adc channels
	RCC->AHB1ENR |= GPIOAEN;
	//Set the mode of PA1 (ADC channel 1) to analog
	GPIOA->MODER |= (3U<<2);
	//Configure adc parameters such as convertion sequence start and lenght
	ADC1->SQR3 = ADC_CH1; //We are usign the single channel 1
	//Set the sequence lenght
	ADC1->SQR1 = ADC_SEQ_LEN1;
	//Enable ADC module
	ADC1->CR2 |= ADON;
	//Enable ADC interrupt
	ADC1->CR1 |= EOCIE;
	//NVIC enable USART
	NVIC_EnableIRQ(ADC_IRQn);
	//Enable Interrupt
	__enable_irq();
}

void start_conversion(){
	ADC1->CR2 |= CONT;
	//STart the ADC conversion
	ADC1->CR2 |= SWSTART;
}

uint32_t read_conversion(){
	//Wait until  conversion is complete
	while(!(ADC1->SR & EOC));
	//return the value
	return ADC1->DR;
}

