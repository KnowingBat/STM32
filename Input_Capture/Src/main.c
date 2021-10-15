#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

int time_stamp = 0;

int main(void){
	tim2_output_compare();
	tim3_input_capture();

	while(1){
		while(!(TIM3->SR & CC1IF));
		time_stamp = TIM3->CCR1;
	}
}
