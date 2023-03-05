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
 
#ifndef _zf_uart_h
#define _zf_uart_h


#include "common.h"
#include "ifxAsclin_Asc.h"



#define UART0_TX_BUFFER_SIZE 16	//���崮��0���ͻ�������С
#define UART0_RX_BUFFER_SIZE 16	//���崮��0���ջ�������С

#define UART1_TX_BUFFER_SIZE 16
#define UART1_RX_BUFFER_SIZE 16



//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ��ں�
{
    UART_0,
    UART_1,
}UARTN_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ�������
{
	//����0 �������ſ�ѡ��Χ
    UART0_TX_P00_0, UART0_TX_P14_0, UART0_TX_P14_1,  UART0_TX_P15_2,  UART0_TX_P15_3,
	//����0 �������ſ�ѡ��Χ
	UART0_RX_P14_1, UART0_RX_P15_3,

	//����1 �������ſ�ѡ��Χ
	UART1_TX_P02_2, UART1_TX_P11_12, UART1_TX_P15_0, UART1_TX_P15_1,  UART1_TX_P15_4,  UART1_TX_P15_5, UART1_TX_P20_10, UART1_TX_P33_6,
	//����1 �������ſ�ѡ��Χ
	UART1_RX_P02_3, UART1_RX_P11_10, UART1_RX_P14_8,  UART1_RX_P15_1, UART1_RX_P15_5,  UART1_RX_P20_9,  UART1_RX_P33_6,
}UART_PIN_enum;



//��������handle����
extern IfxAsclin_Asc uart0_handle;
extern IfxAsclin_Asc uart1_handle;

void uart_init(UARTN_enum uartn, uint32 baud, UART_PIN_enum tx_pin, UART_PIN_enum rx_pin);
void uart_putchar(UARTN_enum uartn, uint8 dat);
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len);
void uart_putstr(UARTN_enum uartn, const int8 *str);
void uart_getchar(UARTN_enum uartn, uint8 *dat);
uint8 uart_query(UARTN_enum uartn, uint8 *dat);
void SDS_OutPut_Data(float S_Out[]);
extern float SDS_OutData[4];
#endif
