#include "state_reg.h" 
#include "stdio.h"
#include "usart2.h"
#include "main.h"
uint8_t STAT_BUF[64];//保存所有寄存器
//uint32_t PACKET_CNT;
///////////////////////////////////////////////////////
//获取所有GPIO状态输入


void clear_state_reg(void)
{
	
}

void do_open_led0()
{
	if(usart2.receive_buffer[4]&0x1){
		HAL_GPIO_WritePin (LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin (LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
	}
}
void UART2_COMMAND_PROCESSING(void)//连接电机
{
	if(usart2.USART_RX_STA&0x8000)//串口接收到数据
	{  
		switch(usart2.receive_buffer[3]) //0xAA,CC,01,01
		{
			case CMD_OPEN_LED0: 
			{
				do_open_led0();
				break;
			}
			default:
			{
				break;
			}
		}
		usart2.USART_RX_STA=0;//清除接收标志
	}
}
