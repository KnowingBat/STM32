#include "stm32f4xx.h"
#include "timer.h"

#define TIM2_EN			(1U<<0)
#define PRESCALER 		1600-1
#define CR1_TIM2EN		(1U<<0)
#define TOGGLE_MODE 	(3U<<4)
#define CC1E			(1U<<0)
#define GPIOAEN			(1U<<0)
#define CC3E			(1U<<0)

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

void tim2_output_compare(){
	//Enable clk access to timer2
	RCC->APB1ENR |= TIM2_EN;
	//Set the prescale value
	TIM2->PSC = PRESCALER; //16 000 000/1 600 = 10 000Hz
	//Set the auto-reload value
	TIM2->ARR = 10000 - 1; // 10 000/10 000 = 1Hz
	//Set the OutputCOmpare Toggle Mode
	TIM2->CCMR1 |= TOGGLE_MODE;
	//Enable channel1 (PA1) in COmpare Mode
	TIM2->CCER |= CC1E;
	//Enable clock access to PA5
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA5 as alternate funcion mode
	GPIOA->MODER |= (2U<<10);
	//COnfigure PA5 as alternate function mode AF1
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] &= ~(1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);
	//Clear the timer-counter
	TIM2->CNT = 0;
	//enable the timer
	TIM2->CR1 = CR1_TIM2EN;
}

void tim3_input_capture(){
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set PA6 mode to alternate function
	GPIOA->MODER |= (2U<<12);
	//Set PA6 to AF02
	GPIOA->AFR[0] |= (2U<<24);
	//Enable clock access to tim3
	RCC->APB1ENR |= (1U<<1);
	//Set the prescaler
	TIM3->PSC = 16000 - 1;
	//Set the ch1 to input capture mode
	TIM3->CCMR1 |= (1U<<0);
	//Set ch1 to input capture on rising edge
	TIM3->CCER |= CC3E;
	//ENable tim3
	TIM3->CR1 |= CC3E;
}
