/*
 * uart.h
 *
 *  Created on: 14 ott 2021
 *      Author: davide
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f4xx.h"

void uart2_init(void);
char uart2_read(void);


#endif /* UART_H_ */
