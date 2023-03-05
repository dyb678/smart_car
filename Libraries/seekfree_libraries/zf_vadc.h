/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		zf_vadc
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/
 
#ifndef _zf_vadc_h
#define _zf_vadc_h

#include "common.h"



//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADC���
{
	ADC_0,
	ADC_1,
}VADCN_enum;

typedef enum  // ö��ADCͨ��
{
    //ADC0��ѡ����
    ADC0_CH5_A5 = 0*16 + 5,
    ADC0_CH6_A6,
    ADC0_CH7_A7,
    ADC0_CH8_A8,
    ADC0_CH9_A9,
    ADC0_CH10_A10,
    ADC0_CH11_A11,

    //ADC1��ѡ����
    ADC1_CH0_A12  = 1*16 + 0,
    ADC1_CH1_A13,
    ADC1_CH2_A14,
    ADC1_CH3_A15,
    ADC1_CH4_A16,
    ADC1_CH5_A17,
    ADC1_CH6_A18,
}VADC_CHN_enum;

//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    ADC_8BIT,     //8λ�ֱ���
    ADC_10BIT,    //10λ�ֱ���
    ADC_12BIT,    //12λ�ֱ���
}VADC_RES_enum;

void adc_init(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn);
uint16 adc_convert(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res);
uint16 adc_mean_filter(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res, uint8 count);
#endif
