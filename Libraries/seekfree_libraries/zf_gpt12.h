/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		gpt12
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/
 
#ifndef _zf_gpt12_h
#define _zf_gpt12_h

#include "common.h"



typedef enum  // 枚举GPT12 定时器编号
{
    GPT12_T2,
	GPT12_T3,
	GPT12_T4,
	GPT12_T5,
}GPTN_enum;


//此枚举定义不允许用户修改
typedef enum //枚举GPT12引脚
{
	GPT12_T2INB_P33_7,	//T2定时器 计数引脚可选范围
	GPT12_T2EUDB_P33_6,	//T2定时器 计数方向引脚可选范围

	GPT12_T3INA_P02_6,  //T3定时器 计数引脚可选范围
	GPT12_T3EUDA_P02_7, //T3定时器 计数方向引脚可选范围

	GPT12_T4INA_P02_8,  //T4定时器 计数引脚可选范围
	GPT12_T4EUDB_P33_5, //T4定时器 计数方向引脚可选范围

	GPT12_T5INA_P21_7,  //T5定时器 计数引脚可选范围
	GPT12_T5EUDA_P21_6, //T5定时器 计数方向引脚可选范围
}GPT_PIN_enum;


void gpt12_init(GPTN_enum gptn, GPT_PIN_enum count_pin, GPT_PIN_enum dir_pin);
int16 gpt12_get(GPTN_enum gptn);
void gpt12_clear(GPTN_enum gptn);

#endif
