/*
 * FILE                : usart.c
 * DESCRIPTION         : This file is iCore3 usart driver demo.
 * Author              : zh.
 * Copyright           :
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 07/11/2019
 *
 * create.
 * --------------------
 */

//------------------------ Include files ------------------------//

#include "usart2.h"
#include "usart1.h"
#include "usart.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "CRC16.h" 
//--------------------- Function Prototype ----------------------//

static int send_string_to_usart2(char * str);
static int initialize_usart2(unsigned long int baudrate);
static int my_printf2(const char * fmt,...);
static int uart2_sendpacket(unsigned char*, unsigned int);
//--------------------------- Variable --------------------------// 

USART2_T usart2 = {
	.USART_RX_STA = 0,
	.counter = 0,
	.send_string = send_string_to_usart2,
	.initialize = initialize_usart2,
	.printf = my_printf2,
	.send_packet = uart2_sendpacket
};

extern UART_HandleTypeDef huart2;

//--------------------------- Function --------------------------//
/*
 * Name               : initialize_usart2
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *
 * create.
 * -------------------
 */
static int initialize_usart2(unsigned long int baudrate)
{
  huart2.Init.BaudRate = baudrate;
	if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    while(1);
  }	
	HAL_UART_Receive_IT(&huart2, (unsigned char *)&usart2.receive_data,1);
	
	return 0;
}
///////////////////by wuyajun////////////////
static int uart2_sendpacket(unsigned char* sbuf, unsigned int len)
{
	int t;
	for(t=0;t<len;t++)
	{
		while(!(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart2,(unsigned char*)sbuf++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC) == 1));
	return 0;
}

void uart2_send_test(void)
{
	unsigned char a[6]={0x61,0x62,0x63,0x64,0x0D,0x0A};
	uart2_sendpacket(a,6);
}
/*
 * Name               : send_string_to_usart2
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *
 * create.
 * -------------------
 */
static int send_string_to_usart2(char * str)
{
	while(*str != '\0'){
		while(!(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart2,(unsigned char*)str++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC) == 1));
	
	return 0;
}
/*
 * Name               : my_printf4
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *t
 * create.
 * -------------------
 */
static int my_printf2(const char * fmt,...)
{
	__va_list arg_ptr;
	char buf[UART_BUFFER_SIZE];
	
	memset(buf,'\0',sizeof(buf));
	
	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	send_string_to_usart2(buf);
	
	return 0;
}
