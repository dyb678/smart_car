/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		uart
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
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



//��������handle����
IfxAsclin_Asc uart0_handle;
IfxAsclin_Asc uart1_handle;

//����һ��ascConfig�Ľṹ����������ڴ��ڳ�ʼ��ʱֻ��
static IfxAsclin_Asc_Config uart_config;


//�������ڻ�������
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
//  @brief      ���ڳ�ʼ��
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      baud            ���ڲ�����
//  @param      tx_pin          ���ڷ�������
//  @param      rx_pin          ���ڽ�������
//  @return     uint32          ʵ�ʲ�����
//  Sample usage:               uart_init(UART_0,115200,UART0_TX_P14_0,UART0_RX_P14_1);       // ��ʼ������0 ������115200 ��������ʹ��P14_0 ��������ʹ��P14_1
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uartn, uint32 baud, UART_PIN_enum tx_pin, UART_PIN_enum rx_pin)
{
	boolean interrupt_state = disableInterrupts();

	volatile Ifx_ASCLIN *moudle = IfxAsclin_getAddress((IfxAsclin_Index)uartn);

	IfxAsclin_Asc_initModuleConfig(&uart_config, moudle); 		//��ʼ�������ýṹ��

	uart_set_buffer(uartn);//���û�����
	uart_set_interrupt_priority(uartn);//�����ж����ȼ�

    uart_config.baudrate.prescaler    = 4;
    uart_config.baudrate.baudrate     = (float32)baud;
    uart_config.baudrate.oversampling = IfxAsclin_OversamplingFactor_8;

    IfxAsclin_Asc_Pins pins;//��������
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
//  @brief      �����ֽ����
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      dat             ��Ҫ���͵��ֽ�
//  @return     void        
//  Sample usage:               uart_putchar(UART_0, 0xA5);       // ����0����0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uartn, uint8 dat)
{
//	IfxAsclin_Asc_blockingWrite(uart_get_handle(uartn),dat);
	Ifx_SizeT count = 1;
	(void)IfxAsclin_Asc_write(uart_get_handle(uartn), &dat, &count, TIME_INFINITE);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ�������
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      *buff           Ҫ���͵������ַ
//  @param      len             ���ͳ���
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
//  @brief      ���ڷ����ַ���
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      *str            Ҫ���͵��ַ�����ַ
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
//  @brief      ��ȡ���ڽ��յ����ݣ�whlie�ȴ���
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      *dat            �������ݵĵ�ַ
//  @return     void        
//  Sample usage:               uint8 dat; uart_getchar(UART_0,&dat);       // ���մ���0����  ������dat������
//-------------------------------------------------------------------------------------------------------------------
void uart_getchar(UARTN_enum uartn, uint8 *dat)
{
	while(!IfxAsclin_Asc_getReadCount(uart_get_handle(uartn)));
	*dat = IfxAsclin_Asc_blockingRead(uart_get_handle(uartn));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ���ڽ��յ����ݣ���ѯ���գ�
//  @param      uartn           ����ģ���(UART_0,UART_1,UART_2,UART_3)
//  @param      *dat            �������ݵĵ�ַ
//  @return     uint8           1�����ճɹ�   0��δ���յ�����
//  Sample usage:               uint8 dat; uart_query(UART_0,&dat);       // ���մ���0����  ������dat������
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
//  @brief      �ض���printf ������
//  @param      ch      ��Ҫ��ӡ���ֽ�
//  @param      stream  ������
//  @note       �˺����ɱ������Դ������printf������
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
