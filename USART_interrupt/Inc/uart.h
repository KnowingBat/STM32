#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f4xx.h"

#define RXNE		(1U<<5)

void uart2_interrupt(void);
char uart2_read(void);

#endif /* UART_H_ */
