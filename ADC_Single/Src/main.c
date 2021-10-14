#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"

#define VOLTAGE 	3.3

uint32_t value;
float result;

int main(void){

	uart2_init();
	adc_init();
	//to add continuous conversion put start_conversion() out of the while
	start_conversion();
	while(1){
		value = read_conversion();
		result = ((float)value/4096) * 3.3;
		printf("Sensor value: %.2f\n", result);
	}
}
