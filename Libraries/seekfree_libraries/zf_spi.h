/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		spi
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/
 
#ifndef _zf_spi_h
#define _zf_spi_h

#include "common.h"



typedef enum    // SPIģ���
{
	SPI_0,
    SPI_1,
    SPI_2,
    SPI_3,
}SPIN_enum;

typedef enum    // ö��SPI����
{

	SPI0_SCLK_P20_11 = 0*102+0*6 , SPI0_SCLK_P20_13,//SPI0 CLK ���ſ�ѡ��Χ
	SPI0_MOSI_P20_12 = 0*102+1*6 , SPI0_MOSI_P20_14,//SPI0 MOSI���ſ�ѡ��Χ
	SPI0_MISO_P20_12 = 0*102+2*6 ,					//SPI0 MISO���ſ�ѡ��Χ

	SPI0_CS0_P20_8   = 0*102+3*6 ,					//SPI0 CS0 ���ſ�ѡ��Χ
	SPI0_CS1_P20_9   = 0*102+4*6 ,
	SPI0_CS2_P20_13  = 0*102+5*6 ,
	SPI0_CS3_P11_10  = 0*102+6*6 ,
	SPI0_CS4_P11_11  = 0*102+7*6 ,
	SPI0_CS5_P11_2   = 0*102+8*6 ,
	SPI0_CS6_P20_10  = 0*102+9*6 ,
	SPI0_CS7_P33_5   = 0*102+10*6,
	SPI0_CS13_P15_0  = 0*102+16*6,
	//----------------------------------------------------------------------------------

	SPI1_SCLK_P11_6  = 1*102+0*6 ,
	SPI1_MOSI_P10_3  = 1*102+1*6 , SPI1_MOSI_P11_9,
	SPI1_MISO_P11_3  = 1*102+2*6 ,

	SPI1_CS0_P20_8   = 1*102+3*6 ,
	SPI1_CS1_P20_9   = 1*102+4*6 ,
	SPI1_CS2_P20_13  = 1*102+5*6 ,
	SPI1_CS3_P11_10  = 1*102+6*6 ,
	SPI1_CS4_P11_11  = 1*102+7*6 ,
	SPI1_CS5_P11_2   = 1*102+8*6 ,
	SPI1_CS6_P33_10  = 1*102+9*6 ,
	SPI1_CS7_P33_5   = 1*102+10*6,
	SPI1_CS9_P10_5   = 1*102+12*6,
	//----------------------------------------------------------------------------------

	//��TQFP80��װ��û��P15_4
	SPI2_SCLK_P15_3  = 2*102+0*6 ,
	SPI2_MOSI_P15_5  = 2*102+1*6 ,
	SPI2_MISO_P15_2  = 2*102+2*6 , SPI2_MISO_P15_4,

	SPI2_CS0_P15_2   = 2*102+3*6 ,
	SPI2_CS3_P14_3   = 2*102+6*6 ,
	SPI2_CS5_P15_1   = 2*102+8*6 ,
	//----------------------------------------------------------------------------------

	SPI3_SCLK_P02_7  = 3*102+0*6 ,
	SPI3_MOSI_P02_6  = 3*102+1*6 , SPI3_MOSI_P10_6,
	SPI3_MISO_P02_5  = 3*102+2*6 ,

	SPI3_CS0_P02_4   = 3*102+3*6 ,
	SPI3_CS1_P02_0   = 3*102+4*6 , SPI3_CS1_P33_9,
	SPI3_CS2_P02_1   = 3*102+5*6 , SPI3_CS2_P33_8,
	SPI3_CS3_P02_2   = 3*102+6*6 ,
	SPI3_CS4_P02_3   = 3*102+7*6 ,
	SPI3_CS5_P02_8   = 3*102+8*6 ,
	SPI3_CS6_P00_8   = 3*102+9*6 ,
	SPI3_CS7_P33_7   = 3*102+10*6,
	SPI3_CS8_P10_5   = 3*102+11*6,
	SPI3_CS11_P33_10 = 3*102+14*6,
	SPI3_CS13_P23_1  = 3*102+16*6,

	SPI_CS_NOT_USE,
}SPI_PIN_enum;



void spi_init(SPIN_enum spi_n, SPI_PIN_enum sck_pin, SPI_PIN_enum mosi_pin, SPI_PIN_enum miso_pin, SPI_PIN_enum cs_pin, uint8 mode, uint32 baud);
void spi_mosi(SPIN_enum spi_n, SPI_PIN_enum cs_pin, uint8 *modata, uint8 *midata, uint32 len, uint8 continuous);




#endif
