/*
 * FILE               : usart.h
 * DESCRIPTION        : This file is iCore3T usart file header.
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
#ifndef __usart3_h__
#define __usart3_h__

//----------------------- Include files ------------------------//

#include "stm32f1xx_hal.h"

//--------------------------- Define ---------------------------//

#define UART_BUFFER_SIZE 200

//------------------------- Data struct ------------------------//
typedef struct{
	char receive_buffer[UART_BUFFER_SIZE];
	char receive_data;
	int counter;
	
	int receive_ok_flag;
	uint16_t USART_RX_STA;
	int baudrate;
	int error;
	int(* initialize)(unsigned long int);
	int(* send_string)(char *);
	int(* printf)(const char * ,...);
}USART3_T;
//----------------------- Extern function ----------------------//

extern void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle);
extern void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle);
extern UART_HandleTypeDef huart3;
extern USART3_T usart3;

//----------------------- Extern variable ----------------------//
#endif // __uart3_h__
