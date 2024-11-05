/*
 * FILE               : usart.h
 * DESCRIPTION        : This file is iCore4T usart file header.
 * Author             : zh.
 * Copyright          :
 *
 * History
 * --------------------
 * Rev                : 0.00
 * Date               : 11/12/2019
 *
 * create.
 * --------------------
 */
#ifndef __usart1_h__
#define __usart1_h__

//----------------------- Include files ------------------------//
#include "stm32f1xx_hal.h"

//--------------------------- Define ---------------------------//
#define UART_BUFFER_SIZE 200

//------------------------- Data struct ------------------------//
typedef struct{
	char receive_buffer[UART_BUFFER_SIZE];
	char receive_data;
	int counter;
	
	uint16_t USART_RX_STA;
	int baudrate;
	int error;
	int(* initialize)(unsigned long int);
	int(* send_string)(char *);
	int(* printf)(const char * ,...);
	int(* send_packet)(unsigned char*, unsigned int);
}USART1_T;
//----------------------- Extern function ----------------------//

extern void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
extern void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
extern UART_HandleTypeDef huart1;
extern USART1_T usart1;
void uart1_send_test(void);
//----------------------- Extern variable ----------------------//
#endif // __uart2_h__
