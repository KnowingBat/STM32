#include <stdint.h>
#include "stm32f411xe.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

int main(void){
	tim2_output_compare();
	while(1){}
}
