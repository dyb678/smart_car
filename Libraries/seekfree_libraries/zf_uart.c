/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		uart
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/
 
 
#include "IFXPORT.h"
#include "stdio.h"
#include "ifxAsclin_reg.h"
#include "ifxCpu_Irq.h"
#include "IFXASCLIN_CFG.h"
#include "SysSe/Bsp/Bsp.h"
#include "zf_assert.h"
#include "isr_config.h"
#include "TC212_config.h"
#include "zf_uart.h"



//创建串口handle变量
IfxAsclin_Asc uart0_handle;
IfxAsclin_Asc uart1_handle;

//创建一个ascConfig的结构体变量，用于串口初始化时只用
static IfxAsclin_Asc_Config uart_config;


//创建串口缓存数组
static uint8 uart0_tx_buffer[UART0_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 uart0_rx_buffer[UART0_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

static uint8 uart1_tx_buffer[UART1_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];
static uint8 uart1_rx_buffer[UART1_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];




void uart_set_interrupt_priority(UARTN_enum uartn)
{
	switch(uartn)
	{
		case UART_0:
		{
			uart_config.interrupt.txPriority 	= UART0_TX_INT_PRIO;
			uart_config.interrupt.rxPriority 	= UART0_RX_INT_PRIO;
			uart_config.interrupt.erPriority 	= UART0_ER_INT_PRIO;
			uart_config.interrupt.typeOfService = UART0_INT_SERVICE;
		}break;
		case UART_1:
		{
			uart_config.interrupt.txPriority 	= UART1_TX_INT_PRIO;
			uart_config.interrupt.rxPriority 	= UART1_RX_INT_PRIO;
			uart_config.interrupt.erPriority 	= UART1_ER_INT_PRIO;
			uart_config.interrupt.typeOfService = UART1_INT_SERVICE;
		}break;
		default: ZF_ASSERT(FALSE);
	}
}

void uart_set_buffer(UARTN_enum uartn)
{
	switch(uartn)
	{
		case UART_0:
		{
			uart_config.txBuffer 	 = &uart0_tx_buffer;
			uart_config.rxBuffer 	 = &uart0_rx_buffer;
			uart_config.txBufferSize = UART0_TX_BUFFER_SIZE;
			uart_config.rxBufferSize = UART0_RX_BUFFER_SIZE;
		}break;
		case UART_1:
		{
			uart_config.txBuffer 	 = &uart1_tx_buffer;
			uart_config.rxBuffer 	 = &uart1_rx_buffer;
			uart_config.txBufferSize = UART1_TX_BUFFER_SIZE;
			uart_config.rxBufferSize = UART1_RX_BUFFER_SIZE;
		}break;
		default: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);
	}
}


IfxAsclin_Asc* uart_get_handle(UARTN_enum uartn)
{
	switch(uartn)
	{
		case UART_0:	 return &uart0_handle;
		case UART_1:	 return &uart1_handle;
		default: IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);
	}

	return NULL;
}

void uart_mux(UARTN_enum uartn, UART_PIN_enum tx_pin, UART_PIN_enum rx_pin, uint32 *set_tx_pin, uint32 *set_rx_pin)
{
	switch(uartn)
	{
		case UART_0:
		{
		    if     (UART0_TX_P00_0 == tx_pin)   *set_tx_pin = (uint32)&IfxAsclin0_TX_P00_0_OUT;
		    else if(UART0_TX_P14_0 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin0_TX_P14_0_OUT;
			else if(UART0_TX_P14_1 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin0_TX_P14_1_OUT;
			else if(UART0_TX_P15_2 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin0_TX_P15_2_OUT;
			else if(UART0_TX_P15_3 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin0_TX_P15_3_OUT;
			else IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);

			if	   (UART0_RX_P14_1 == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin0_RXA_P14_1_IN;
			else if(UART0_RX_P15_3 == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin0_RXB_P15_3_IN;
			else IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);

		}break;
		case UART_1:
		{
			if	   (UART1_TX_P02_2  == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P02_2_OUT;
			else if(UART1_TX_P11_12 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P11_12_OUT;
			else if(UART1_TX_P15_0  == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P15_0_OUT;
			else if(UART1_TX_P15_1  == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P15_1_OUT;
			else if(UART1_TX_P15_4  == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P15_4_OUT;
			else if(UART1_TX_P15_5  == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P15_5_OUT;
			else if(UART1_TX_P20_10 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P20_10_OUT;
			else if(UART1_TX_P33_6 == tx_pin)	*set_tx_pin = (uint32)&IfxAsclin1_TX_P33_6_OUT;
			else IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);

			if	   (UART1_RX_P15_1  == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXA_P15_1_IN;
			else if(UART1_RX_P15_5  == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXB_P15_5_IN;
			else if(UART1_RX_P20_9  == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXC_P20_9_IN;
			else if(UART1_RX_P14_8  == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXD_P14_8_IN;
			else if(UART1_RX_P11_10 == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXE_P11_10_IN;
			else if(UART1_RX_P33_6 == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXF_P33_6_IN;
			else if(UART1_RX_P02_3  == rx_pin)	*set_rx_pin = (uint32)&IfxAsclin1_RXG_P02_3_IN;
			else IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, FALSE);

		}break;
	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口初始化
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      baud            串口波特率
//  @param      tx_pin          串口发送引脚
//  @param      rx_pin          串口接收引脚
//  @return     uint32          实际波特率
//  Sample usage:               uart_init(UART_0,115200,UART0_TX_P14_0,UART0_RX_P14_1);       // 初始化串口0 波特率115200 发送引脚使用P14_0 接收引脚使用P14_1
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uartn, uint32 baud, UART_PIN_enum tx_pin, UART_PIN_enum rx_pin)
{
	boolean interrupt_state = disableInterrupts();

	volatile Ifx_ASCLIN *moudle = IfxAsclin_getAddress((IfxAsclin_Index)uartn);

	IfxAsclin_Asc_initModuleConfig(&uart_config, moudle); 		//初始化化配置结构体

	uart_set_buffer(uartn);//设置缓冲区
	uart_set_interrupt_priority(uartn);//设置中断优先级

    uart_config.baudrate.prescaler    = 4;
    uart_config.baudrate.baudrate     = (float32)baud;
    uart_config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;

    IfxAsclin_Asc_Pins pins;//设置引脚
    pins.cts = NULL;
    pins.rts = NULL;
    uart_mux(uartn, tx_pin, rx_pin, (uint32 *)&pins.tx, (uint32 *)&pins.rx);
    pins.rxMode = IfxPort_InputMode_pullUp;
    pins.txMode = IfxPort_OutputMode_pushPull;
    pins.pinDriver = IfxPort_PadDriver_cmosAutomotiveSpeed1;
    uart_config.pins = &pins;

    IfxAsclin_Asc_initModule(uart_get_handle(uartn), &uart_config);

    restoreInterrupts(interrupt_state);
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口字节输出
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      dat             需要发送的字节
//  @return     void        
//  Sample usage:               uart_putchar(UART_0, 0xA5);       // 串口0发送0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uartn, uint8 dat)
{
//	IfxAsclin_Asc_blockingWrite(uart_get_handle(uartn),dat);
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(uart_get_handle(uartn), &dat, &count, TIME_INFINITE);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送数组
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      *buff           要发送的数组地址
//  @param      len             发送长度
//  @return     void
//  Sample usage:               uart_putbuff(UART_0,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len)
{
	while(len)
	{
		uart_putchar(uartn, *buff);
		len--;
		buff++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送字符串
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      *str            要发送的字符串地址
//  @return     void
//  Sample usage:               uart_putstr(UART_0,"i lvoe you");
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uartn, const int8 *str)
{
    while(*str)
    {
        uart_putchar(uartn, *str++);
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取串口接收的数据（whlie等待）
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      *dat            接收数据的地址
//  @return     void        
//  Sample usage:               uint8 dat; uart_getchar(UART_0,&dat);       // 接收串口0数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
void uart_getchar(UARTN_enum uartn, uint8 *dat)
{
	while(!IfxAsclin_Asc_getReadCount(uart_get_handle(uartn)));
	*dat = IfxAsclin_Asc_blockingRead(uart_get_handle(uartn));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取串口接收的数据（查询接收）
//  @param      uartn           串口模块号(UART_0,UART_1,UART_2,UART_3)
//  @param      *dat            接收数据的地址
//  @return     uint8           1：接收成功   0：未接收到数据
//  Sample usage:               uint8 dat; uart_query(UART_0,&dat);       // 接收串口0数据  存在在dat变量里
//-------------------------------------------------------------------------------------------------------------------
uint8 uart_query(UARTN_enum uartn, uint8 *dat)
{
	if(IfxAsclin_Asc_getReadCount(uart_get_handle(uartn)) >0)
	{
		*dat = IfxAsclin_Asc_blockingRead(uart_get_handle(uartn));
		return 1;
	}
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      重定义printf 到串口
//  @param      ch      需要打印的字节
//  @param      stream  数据流
//  @note       此函数由编译器自带库里的printf所调用
//-------------------------------------------------------------------------------------------------------------------
int fputc(int ch, FILE *stream)
{
    uart_putchar(DEBUG_UART, (char)ch);
    return(ch);
}

float SDS_OutData[4]= {0};
unsigned short CRC_CHEC(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void SDS_OutPut_Data(float S_Out[])
{
  int temp[4] = {0};
  unsigned int temp1[4] = {0};
  unsigned char databuf[10] = {0};
  unsigned char i;
  unsigned short CRC16 = 0;
  float SDS_OutData[4];
  for(i=0;i<4;i++) {
  SDS_OutData[i]=S_Out[i];
  }
  for(i=0;i<4;i++)
   {

    temp[i]  = (int)SDS_OutData[i];
    temp1[i] = (unsigned int)temp[i];

   }

  for(i=0;i<4;i++)
  {
    databuf[i*2]   = (unsigned char)(temp1[i]%256);
    databuf[i*2+1] = (unsigned char)(temp1[i]/256);
  }

  CRC16 = CRC_CHEC(databuf,8);
  databuf[8] = CRC16%256;
  databuf[9] = CRC16/256;

  for(i=0;i<10;i++)
{
    uart_putchar(UART_0, databuf[i] );
}
}
