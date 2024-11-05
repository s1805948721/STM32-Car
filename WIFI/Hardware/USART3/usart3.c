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

#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "usart.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "CRC16.h" 
#include "atk_mw8266d.h"
//--------------------- Function Prototype ----------------------//

static int send_string_to_usart3(char * str);
static int initialize_usart3(unsigned long int baudrate);
static int my_printf3(const char * fmt,...);

//--------------------------- Variable --------------------------// 

USART3_T usart3 = {
	.USART_RX_STA = 0,
	.receive_ok_flag = 0,
	.counter = 0,
	.send_string = send_string_to_usart3,
	.initialize = initialize_usart3,
	.printf = my_printf3
};

extern UART_HandleTypeDef huart3;

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
static int initialize_usart3(unsigned long int baudrate)
{
  huart3.Init.BaudRate = baudrate;
	if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    while(1);
  }	
	HAL_UART_Receive_IT(&huart3, (unsigned char *)&usart3.receive_data,1);
	
	return 0;
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
static int send_string_to_usart3(char * str)
{
	while(*str != '\0'){
		while(!(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart3,(unsigned char*)str++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == 1));
	
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
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t Res;
	uint16_t Rcrc;
	if(huart == &huart3){
		HAL_UART_IRQHandler(&huart3);

		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart3,(unsigned char *)&usart3.receive_data,1) != HAL_OK);
		
		Res = usart3.receive_data;//读取接收到的数据
		if((usart3.USART_RX_STA&0x8000)==0)//接收未完成才会进入接收流程，如果接收完成了，需要等待主程序处理完将标志清零后才能继续接收。
		{
			if((usart3.USART_RX_STA&0x4000)==0)//还没接收到了0xAA
			{
				if(Res==0xAA) 
				{
					usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				  usart3.USART_RX_STA++;
					usart3.USART_RX_STA|=0x4000;	//bit14标志位置1
				}
				else return;//没有收到0xAA，并且这个数据也不是0xAA，就退出
			}
			else if((usart3.USART_RX_STA&0x2000)==0)//已经收到0XAA,还没接收到了0xCC
			{
				if(Res==0xCC)//收到0xCC
				{	
					usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				  usart3.USART_RX_STA++;
					usart3.USART_RX_STA|=0x2000;	//bit13标志位置1
				}
				else usart3.USART_RX_STA=0;//接收错误,重新开始
			}
			else//以下是接收包头以外的数据包
			{
				usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				usart3.USART_RX_STA++;
				if((usart3.USART_RX_STA&0x1fff)==24)//包长24字节
				{
					if(1)//1--CRC校验; 0--不需要校验
					{
						Rcrc=crc16_ibm((uint8_t*)usart3.receive_buffer,22);//计算CRC校验值
						if(((Rcrc&0xff)==usart3.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart3.receive_buffer[22]))
						{
							usart3.USART_RX_STA|=0x8000;	//接收完成了 
						}else
						{
							usart3.USART_RX_STA=0;//接收错误,重新开始
						}
					}else{
						usart3.USART_RX_STA|=0x8000;	//接收完成了 
					}
				}
			}
		}
	}else if(huart == &huart1){
		HAL_UART_IRQHandler(&huart1);

		while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart1,(unsigned char *)&usart1.receive_data,1) != HAL_OK);
		
		Res = usart1.receive_data;//读取接收到的数据
		//usart6.printf("%x,",Res);
		if((usart1.USART_RX_STA&0x8000)==0)//接收未完成才会进入接收流程，如果接收完成了，需要等待主程序处理完将标志清零后才能继续接收。
		{
			if((usart1.USART_RX_STA&0x4000)==0)//还没接收到了0xAA
			{
				if(Res==0xAA) 
				{
					//usart2.printf("receive a AA\r\n");
					usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				  usart1.USART_RX_STA++;
					usart1.USART_RX_STA|=0x4000;	//bit14标志位置1
				}
				else return;//没有收到0xAA，并且这个数据也不是0xAA，就退出
			}
			else if((usart1.USART_RX_STA&0x2000)==0)//已经收到0XAA,还没接收到了0xCC
			{
				if(Res==0xCC)//收到0xCC
				{	
					//usart2.printf("receive CC\r\n");
					usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				  usart1.USART_RX_STA++;
					usart1.USART_RX_STA|=0x2000;	//bit13标志位置1
				}
				else usart1.USART_RX_STA=0;//接收错误,重新开始
			}
			else//以下是接收包头以外的数据包
			{
				usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				usart1.USART_RX_STA++;
				if((usart1.USART_RX_STA&0x1fff)==24)//包长24字节
				{
					//usart2.printf("receive a packet\r\n");
					//printf("收到数据包：\r\n");
					//usart6.send_packet((unsigned char*)usart1.receive_buffer, 24);
					Rcrc=crc16_ibm((uint8_t*)usart1.receive_buffer,22);//计算CRC校验值
					if(((Rcrc&0xff)==usart1.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart1.receive_buffer[22]))
					{
						usart1.USART_RX_STA|=0x8000;	//接收完成了 
						//usart2.printf("CRC校验成功%x\r\n", Rcrc);
						//printf("CRC校验成功%x\r\n", Rcrc);
					}else
					{
						usart1.USART_RX_STA=0;//接收错误,重新开始
						//usart2.printf("CRC校验错误%x\r\n", Rcrc);
						//printf("CRC校验错误%x\r\n", Rcrc);
					}
				}
			}
		} 
	}else if(huart == &huart2){
		HAL_UART_IRQHandler(&huart2);
		if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE) != RESET)        /* UART接收过载错误中断 */
    {
        __HAL_UART_CLEAR_OREFLAG(&huart2);                           /* 清除接收过载错误中断标志 */
        (void)huart2.Instance->SR;                                   /* 先读SR寄存器，再读DR寄存器 */
        (void)huart2.Instance->DR;
    }
		while(HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart2,(unsigned char *)&usart2.receive_data,1) != HAL_OK);
		//{
			//huart2.RxState = HAL_UART_STATE_READY;
			//__HAL_UNLOCK(&huart2);
		//}
		//usart2.printf("Recv!\r\n");
		Res = usart2.receive_data;//读取接收到的数据
		if(RECV_FLAG==0)//如果WIFI不是透传模式，则将WIFI数据从调试口打印出来
		{
			usart1.send_packet(&Res,1);
			//usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
			//usart2.USART_RX_STA++;
/*			
			if((usart2.USART_RX_STA&0x8000)==0)//接收未完成
			{
				if(usart2.USART_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
					{
						usart2.USART_RX_STA=0;//接收错误,重新开始
					}else 
					{
						usart2.USART_RX_STA|=0x8000;	//接收完成了 
					}
				}
				else //还没收到0X0D
				{	
					if(Res==0x0d)
					{
						usart2.USART_RX_STA|=0x4000;
					}
					else
					{
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						if(usart2.USART_RX_STA>(UART_BUFFER_SIZE-1))
						{
							usart2.USART_RX_STA=0;//接收数据错误,重新开始接收	
						}							
					}		 
				}
			}*/
		}else
		{
			if((usart2.USART_RX_STA&0x8000)==0)//接收未完成才会进入接收流程，如果接收完成了，需要等待主程序处理完将标志清零后才能继续接收。
			{
				if((usart2.USART_RX_STA&0x4000)==0)//还没接收到了0xAA
				{
					if(Res==0xAA) 
					{
						//usart2.printf("receive a AA\r\n");
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						usart2.USART_RX_STA|=0x4000;	//bit14标志位置1
					}
					else return;//没有收到0xAA，并且这个数据也不是0xAA，就退出
				}
				else if((usart2.USART_RX_STA&0x2000)==0)//已经收到0XAA,还没接收到了0xCC
				{
					if(Res==0xCC)//收到0xCC
					{	
						//usart2.printf("receive CC\r\n");
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						usart2.USART_RX_STA|=0x2000;	//bit13标志位置1
					}
					else usart2.USART_RX_STA=0;//接收错误,重新开始
				}
				else//以下是接收包头以外的数据包
				{
					usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
					usart2.USART_RX_STA++;
					if((usart2.USART_RX_STA&0x1fff)==24)//包长24字节
					{
						//usart6.printf("receive a packet\r\n");
						//usart6.send_packet((unsigned char*)usart1.receive_buffer, 24);
						Rcrc=crc16_ibm((uint8_t*)usart2.receive_buffer,22);//计算CRC校验值
						if(((Rcrc&0xff)==usart2.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart2.receive_buffer[22]))
						{
							usart2.USART_RX_STA|=0x8000;	//接收完成了 
							//usart6.printf("CRC校验成功%x\r\n", Rcrc);
						}else
						{
							usart2.USART_RX_STA=0;//接收错误,重新开始
							//usart2.printf("CRC校验错误%x\r\n", Rcrc);
						}
					}
				}
			}
		}
	}
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
static int my_printf3(const char * fmt,...)
{
	__va_list arg_ptr;
	char buf[UART_BUFFER_SIZE];
	
	memset(buf,'\0',sizeof(buf));
	
	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	send_string_to_usart3(buf);
	
	return 0;
}
