/**
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 MiniSTM32 V4开发板
 *
 ****************************************************************************************************
 */

#include "atk_mw8266d.h"
#include <string.h>
#include <stdio.h>
#include "gpio.h"
#include "usart2.h"
#include "usart1.h"
#include "state_reg.h" 
#include "CRC16.h" 
/**
 * @brief       ATK-MW8266D硬件初始化
 * @param       无
 * @retval      无
 */

/**
 * @brief       ATK-MW8266D硬件复位
 * @param       无
 * @retval      无
 */
uint8_t RECV_FLAG;

/**
 * @brief 执行查询状态操作
 *
 * 该函数负责构建一个查询状态的数据包，并通过UART发送出去。
 * 数据包包含包头、设备ID、包计数器和校验码。
 */
void do_query_state(void)
{
	uint8_t len=STAT_PACKET_LENGTH;//数据包长度，不包括包头，但是包括校验码
	uint16_t Scrc;
	//添加包头
	STAT_BUF[0]=0xAA;
	STAT_BUF[1]=0xCC;
	STAT_BUF[2]=DEVICE_ID;
	STAT_BUF[3]=PKG_CNT;
	//其余数据包就是UART1_TX_BUF中的内容
	
	//添加校验码
	Scrc=crc16_ibm(STAT_BUF,len);
	STAT_BUF[len]=(Scrc>>8)&0xff;
	STAT_BUF[len+1]=Scrc&0xff;
	//发送数据包，数据包长度为包头+版本+校验=3+len+2
	usart2.send_packet(STAT_BUF, len+2);
	PKG_CNT = PKG_CNT+1;//包计数器+1
}

/**
 * @brief 对MW8266D硬件进行复位
 *
 * 该函数通过操作GPIO引脚对MW8266D模块进行硬件复位。
 *
 * @note 复位操作分为两步：
 *       1. 将WIFI_RST引脚拉低持续100毫秒。
 *       2. 将WIFI_RST引脚拉高持续2000毫秒。
 */
void atk_mw8266d_hw_reset(void)
{
    // 将WIFI模块的重置引脚设置为低电平，以进行硬件重置
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_RESET);
    // 延时100毫秒，确保重置信号生效
    HAL_Delay(100);
    // 将WIFI模块的重置引脚设置为高电平，结束重置
    HAL_GPIO_WritePin(WIFI_RST_GPIO_Port, WIFI_RST_Pin, GPIO_PIN_SET);
    // 延时2000毫秒，等待WIFI模块启动
    HAL_Delay(2000);
}
/**
 * @brief 接收应答信号
 *
 * 在指定超时时间内，不断检查USART2接收缓冲区是否有数据。
 * 如果接收到数据，则通过USART1发送该数据，并检查是否包含"OK"字符串。
 * 如果在超时时间内收到包含"OK"的应答，则返回成功状态码；否则返回超时状态码。
 *
 * @param timeout 超时时间（单位：毫秒）
 * @return 如果成功接收到包含"OK"的应答，返回ATK_MW8266D_EOK；如果超时则返回ATK_MW8266D_ETIMEOUT。
 */
uint8_t recv_ack(uint32_t timeout)
{
	// 循环直到超时
	while (timeout > 0)
  {
		// 检查USART2接收缓冲区是否接收到数据
		if(usart2.USART_RX_STA&0x8000)
		{
			// 将接收到的数据通过USART1发送出去
			usart1.send_packet((unsigned char *)usart2.receive_buffer, usart2.USART_RX_STA&0x3fff);
			// 清除接收标志
			usart2.USART_RX_STA=0;//清除接收标志
			// 检查接收到的数据是否包含"OK"
			if (strstr((const char *)usart2.receive_buffer, "OK") != NULL)
			{
				// 如果包含"OK"，则返回成功状态
				return ATK_MW8266D_EOK;
			}
		}
		// 超时时间减1
		timeout--;
		// 延时1毫秒
    HAL_Delay(1);
  }
	// 如果超时，则返回超时状态
	return ATK_MW8266D_ETIMEOUT;
}

/**
 * @brief       ATK-MW8266D初始化
 * @param       baudrate: ATK-MW8266D UART通讯波特率
 * @retval      ATK_MW8266D_EOK  : ATK-MW8266D初始化成功，函数执行成功
 *              ATK_MW8266D_ERROR: ATK-MW8266D初始化失败，函数执行失败
 * @return      返回0表示初始化成功，否则返回非零值表示初始化失败。
 */
uint8_t atk_mw8266d_init(void)
{
  // ATK-MW8266D硬件复位
  atk_mw8266d_hw_reset();                         /* ATK-MW8266D硬件复位 */

  // 等待10秒，确保复位完成
  HAL_Delay(10000);

  // 发送ATE0指令，关闭回显
  usart2.printf("ATE0\r\n");
  HAL_Delay(1000);

  // 设置WiFi模块为STA模式
  usart2.printf("AT+CWMODE=1\r\n");
  HAL_Delay(2000);

  // 连接到指定的WiFi网络
  usart2.printf("AT+CWJAP=\"Yuzusoft\",\"20041030\"\r\n");
  HAL_Delay(15000);

  // 获取WiFi模块的IP地址
  usart2.printf("AT+CIFSR\r\n");
  HAL_Delay(5000);

  // 建立TCP连接
  usart2.printf("AT+CIPSTART=\"TCP\",\"192.168.31.51\",5555\r\n");
  HAL_Delay(10000);

  // 设置CIP模式为透传模式
  usart2.printf("AT+CIPMODE=1\r\n");
  HAL_Delay(1000);

  // 开始发送数据
  usart2.printf("AT+CIPSEND\r\n");
  HAL_Delay(1000);

  // 注释掉发送数据的代码
  //usart2.printf("HELLO!\r\n");

  // 设置接收标志
  RECV_FLAG = 1;

  // 返回0表示初始化成功
  return 0;
}

/**
 * @brief       ATK-MW8266D发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      ATK_MW8266D_EOK     : 函数执行成功
 *              ATK_MW8266D_ETIMEOUT: 等待期望应答超时，函数执行失败
 */
uint8_t atk_mw8266d_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
//    atk_mw8266d_uart_rx_restart();
//    atk_mw8266d_uart_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0))
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        while (timeout > 0)
        {
//            ret = atk_mw8266d_uart_rx_get_frame();
            if (ret != NULL)
            {
                if (strstr((const char *)ret, ack) != NULL)
                {
                    return ATK_MW8266D_EOK;
                }
                else
                {
//                    atk_mw8266d_uart_rx_restart();
                }
            }
            timeout--;
            HAL_Delay(1);
        }
        
        return ATK_MW8266D_ETIMEOUT;
    }
}



/**
 * @brief       ATK-MW8266D恢复出厂设置
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 恢复出场设置成功
 *              ATK_MW8266D_ERROR: 恢复出场设置失败
 */
uint8_t atk_mw8266d_restore(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RESTORE", "ready", 3000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D AT指令测试
 * @param       无
 * @retval      ATK_MW8266D_EOK  : AT指令测试成功
 *              ATK_MW8266D_ERROR: AT指令测试失败
 */
uint8_t atk_mw8266d_at_test(void)
{
    uint8_t ret;
    uint8_t i;
    
    for (i=0; i<10; i++)
    {
        ret = atk_mw8266d_send_at_cmd("AT", "OK", 500);
        if (ret == ATK_MW8266D_EOK)
        {
            return ATK_MW8266D_EOK;
        }
    }
    
    return ATK_MW8266D_ERROR;
}

/**
 * @brief       设置ATK-MW8266D工作模式
 * @param       mode: 1，Station模式
 *                    2，AP模式
 *                    3，AP+Station模式
 * @retval      ATK_MW8266D_EOK   : 工作模式设置成功
 *              ATK_MW8266D_ERROR : 工作模式设置失败
 *              ATK_MW8266D_EINVAL: mode参数错误，工作模式设置失败
 */
uint8_t atk_mw8266d_set_mode(uint8_t mode)
{
    uint8_t ret;
    
    switch (mode)
    {
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=1", "OK", 500);    /* Station模式 */
            break;
        }
        case 2:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=2", "OK", 500);    /* AP模式 */
            break;
        }
        case 3:
        {
            ret = atk_mw8266d_send_at_cmd("AT+CWMODE=3", "OK", 500);    /* AP+Station模式 */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D软件复位
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 软件复位成功
 *              ATK_MW8266D_ERROR: 软件复位失败
 */
uint8_t atk_mw8266d_sw_reset(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+RST", "OK", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        HAL_Delay(1000);
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      ATK_MW8266D_EOK  : 设置回显模式成功
 *              ATK_MW8266D_ERROR: 设置回显模式失败
 */
uint8_t atk_mw8266d_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = atk_mw8266d_send_at_cmd("ATE0", "OK", 500);   /* 关闭回显 */
            break;
        }
        case 1:
        {
            ret = atk_mw8266d_send_at_cmd("ATE1", "OK", 500);   /* 打开回显 */
            break;
        }
        default:
        {
            return ATK_MW8266D_EINVAL;
        }
    }
    
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D连接WIFI
 * @param       ssid: WIFI名称
 *              pwd : WIFI密码
 * @retval      ATK_MW8266D_EOK  : WIFI连接成功
 *              ATK_MW8266D_ERROR: WIFI连接失败
 */
uint8_t atk_mw8266d_join_ap(char *ssid, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "WIFI GOT IP", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D获取IP地址
 * @param       buf: IP地址，需要16字节内存空间
 * @retval      ATK_MW8266D_EOK  : 获取IP地址成功
 *              ATK_MW8266D_ERROR: 获取IP地址失败
 */
uint8_t atk_mw8266d_get_ip(char *buf)
{
    uint8_t ret;
    char *p_start;
    char *p_end;
    
    ret = atk_mw8266d_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret != ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_ERROR;
    }
    
//    p_start = strstr((const char *)atk_mw8266d_uart_rx_get_frame(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return ATK_MW8266D_EOK;
}

/**
 * @brief       ATK-MW8266D连接TCP服务器
 * @param       server_ip  : TCP服务器IP地址
 *              server_port: TCP服务器端口号
 * @retval      ATK_MW8266D_EOK  : 连接TCP服务器成功
 *              ATK_MW8266D_ERROR: 连接TCP服务器失败
 */
uint8_t atk_mw8266d_connect_tcp_server(char *server_ip, char *server_port)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s", server_ip, server_port);
    ret = atk_mw8266d_send_at_cmd(cmd, "CONNECT", 5000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D进入透传
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 进入透传成功
 *              ATK_MW8266D_ERROR: 进入透传失败
 */
uint8_t atk_mw8266d_enter_unvarnished(void)
{
    uint8_t ret;
    
    ret  = atk_mw8266d_send_at_cmd("AT+CIPMODE=1", "OK", 500);
    ret += atk_mw8266d_send_at_cmd("AT+CIPSEND", ">", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D退出透传
 * @param       无
 * @retval      无
 */
void atk_mw8266d_exit_unvarnished(void)
{
//    atk_mw8266d_uart_printf("+++");
}

/**
 * @brief       ATK-MW8266D连接原子云服务器
 * @param       id : 原子云设备编号
 *              pwd: 原子云设备密码
 * @retval      ATK_MW8266D_EOK  : 连接原子云服务器成功
 *              ATK_MW8266D_ERROR: 连接原子云服务器失败
 */
uint8_t atk_mw8266d_connect_atkcld(char *id, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+ATKCLDSTA=\"%s\",\"%s\"", id, pwd);
    ret = atk_mw8266d_send_at_cmd(cmd, "CLOUD CONNECTED", 10000);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}

/**
 * @brief       ATK-MW8266D断开原子云服务器连接
 * @param       无
 * @retval      ATK_MW8266D_EOK  : 断开原子云服务器连接成功
 *              ATK_MW8266D_ERROR: 断开原子云服务器连接失败
 */
uint8_t atk_mw8266d_disconnect_atkcld(void)
{
    uint8_t ret;
    
    ret = atk_mw8266d_send_at_cmd("AT+ATKCLDCLS", "CLOUD DISCONNECT", 500);
    if (ret == ATK_MW8266D_EOK)
    {
        return ATK_MW8266D_EOK;
    }
    else
    {
        return ATK_MW8266D_ERROR;
    }
}
