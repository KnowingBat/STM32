#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"

uint32_t value;

static void ADC_Callback(void);

int main(void){

	uart2_init();
	adc_init();
	start_conversion();
	while(1){}
}

static void ADC_Callback(){
	value = ADC1->DR;
	printf("Sensor value: %d\n", (int)value);
}

void ADC_IRQHandler(){
	if(ADC1->SR & EOC){
		ADC1->SR &= ~EOC;
		ADC_Callback();
	}
}
