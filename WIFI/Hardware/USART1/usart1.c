/*
 * FILE                : usart.c
 * DESCRIPTION         : This file is iCore4t usart driver demo.
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

#include "usart1.h"
#include "usart.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

//--------------------- Function Prototype ----------------------//

static int send_string_to_usart1(char * str);
static int initialize_usart1(unsigned long int baudrate);
static int my_printf1(const char * fmt,...);
static int uart1_sendpacket(unsigned char*, unsigned int);
//--------------------------- Variable --------------------------// 

USART1_T usart1 = {
	.USART_RX_STA = 0,
	.counter = 0,
	.send_string = send_string_to_usart1,
	.initialize = initialize_usart1,
	.printf = my_printf1,
	.send_packet = uart1_sendpacket
};

extern UART_HandleTypeDef huart1;

//--------------------------- Function --------------------------//
/*
 * Name               : initialize_usart1
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
static int initialize_usart1(unsigned long int baudrate)
{
  huart1.Init.BaudRate = baudrate;
	if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    while(1);
  }	
	HAL_UART_Receive_IT(&huart1, (unsigned char *)&usart1.receive_data,1);
	
	return 0;
}
///////////////////by wuyajun////////////////
static int uart1_sendpacket(unsigned char* sbuf, unsigned int len)
{
	int t;
	for(t=0;t<len;t++)
	{
		while(!(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart1,(unsigned char*)sbuf++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC) == 1));
	return 0;
}

void uart1_send_test(void)
{
	unsigned char a[4]={0x01,0x02,0x03,0x04};
	uart1_sendpacket(a,4);
}
/*
 * Name               : send_string_to_usart1
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
static int send_string_to_usart1(char * str)
{

	while(*str != '\0'){
		while(!(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart1,(unsigned char*)str++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC) == 1));

	return 0;
}
/*
 * Name               : HAL_UART_RxCpltCallback
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
/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1){
		HAL_UART_IRQHandler(&huart1);

		while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart1,(unsigned char *)&usart1.receive_data,1) != HAL_OK);
		usart1.receive_buffer[usart1.counter ++] = usart1.receive_data;
		if(usart1.counter == UART_BUFFER_SIZE)usart1.counter = 0;
		
		if(usart1.receive_buffer[usart1.counter - 1] =='\n' && usart1.receive_buffer[usart1.counter - 2] == '\r'){
			usart1.receive_buffer[usart1.counter - 1] = 0;
			usart1.counter = 0;
			usart1.receive_ok_flag = 1;
		}		
	}
}*/
/*
 * Name               : my_printf1
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
static int my_printf1(const char * fmt,...)
{
	__va_list arg_ptr;
	char buf[UART_BUFFER_SIZE];
	
	memset(buf,'\0',sizeof(buf));
	
	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	send_string_to_usart1(buf);
	
	return 0;
}
