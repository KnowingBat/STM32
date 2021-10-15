#ifndef TIMER_H_
#define TIMER_H_

#define SR_UIF 	(1U<<0)

void tim2_1hz_init(void);
void tim2_output_compare(void);
void tim3_input_capture(void);

#define CC1IF		(1U<<1)

#endif /* TIMER_H_ */
