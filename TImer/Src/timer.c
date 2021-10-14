#include "stm32f4xx.h"
#include "timer.h"

#define TIM2_EN			(1U<<0)
#define PRESCALER 		1600-1
#define CR1_TIM2EN		(1U<<0)

//Driver to generate a timeout every second

void tim2_1hz_init(){
	//Enable clk access to timer2
	RCC->APB1ENR |= TIM2_EN;
	//Set the prescale value
	TIM2->PSC = PRESCALER; //16 000 000/1 600 = 10 000Hz
	//Set the auto-reload value
	TIM2->ARR = 10000 - 1; // 10 000/10 000 = 1Hz
	//Clear the timer-counter
	TIM2->CNT = 0;
	//enable the timer
	TIM2->CR1 = CR1_TIM2EN;
}
