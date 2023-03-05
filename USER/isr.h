/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
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

