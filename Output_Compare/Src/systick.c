#include "stm32f4xx.h"
#include "systick.h"
#define LOAD_VALUE		16000 //Load for 1ms
#define CTRL_ENABLE 	(1U<<0)
#define CTRL_CLK		(1U<<2)
#define CTRL_COUNTFLAG	(1U<<16)

void sysTickDelayMs(int delay){
	//COnfigure Systick
	SysTick->LOAD = LOAD_VALUE;
	//Clear SysTick value
	SysTick->VAL = 0;

	SysTick->CTRL |= CTRL_ENABLE | CTRL_CLK;

	for(int i=0;i<delay;i++){
		//Wait until contuflag is set
		while(!(SysTick->CTRL & CTRL_COUNTFLAG));
	}
	//Reset SysTick
	SysTick->CTRL = 0;

}

