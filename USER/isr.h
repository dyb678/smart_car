/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		isr
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/


#ifndef _isr_h
#define _isr_h


#define Ksp  4000
#define Ksi  500
#define Ksd   0





#include "headfile.h"

extern float  speed;
extern float encoderspeed;
extern int16 encoder;
extern int32 outputs2;
extern float  error_speed1,error_speed2;
extern float error_speed;
extern uint8 InRingFlag,OutRingFlag;







#endif

