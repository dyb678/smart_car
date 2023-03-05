/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC212
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-12
 ********************************************************************************************************************/


#include "headfile.h"
#include "math.h"
#include "stdlib.h"


//工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
//工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
//然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
//一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

//对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
//简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。

uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)   //注意计算阈值的一定要是原图像
{
   #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j;
    int pixelSum = width * height/2;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    uint32 gray_sum=0;
    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j++)
        {
            pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
            gray_sum+=(int)data[i * width + j];       //灰度值总和
        }
    }

    //计算每个像素值的点在整幅图像中的比例

    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;

    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;


        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {

                w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
                u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

               w1=1-w0;
               u1tmp=gray_sum/pixelSum-u0tmp;

                u0 = u0tmp / w0;              //背景平均灰度
                u1 = u1tmp / w1;              //前景平均灰度
                u = u0tmp + u1tmp;            //全局平均灰度
                deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
                if (deltaTmp > deltaMax)
                {
                    deltaMax = deltaTmp;
                    threshold = (uint8)j;
                }
                if (deltaTmp < deltaMax)
                {
                break;
                }

         }

    return threshold;

}

void medianBlur(unsigned char* src, unsigned char* dst, unsigned char width, unsigned char height)
{
    unsigned char row,col,i,j,num,index;
    unsigned char hist[256];
    for(row=1;row<height-1;row++)
    {
        memset(hist,0,256);
        num=0;
        for(i=row-1;i<row+2;i++)
            for(j=0;j<3;j++)
                hist[*(src+width*i+j)]+=1;
        i=0;
        while(1)
        {
            num+=hist[i];
            if(num>=5)
            {
                index=i;
                *(dst+width*row+1)=index;
                break;
            }
            i++;
        }
        for(col=2;col<width-1;col++)
        {
            for(i=row-1;i<row+2;i++)
            {
                hist[*(src+width*i+col-2)]-=1;
                hist[*(src+width*i+col+1)]+=1;
                if(*(src+width*i+col-2)<=index)
                    num--;
                if(*(src+width*i+col+1)<=index)
                    num++;
            }
            while(num>5)
            {
                num-=hist[index];
                index--;
            }
            while(num<5)
            {
                index++;
                num+=hist[index];
            }
            *(dst+width*row+col)=index;
        }
    }
    for(i=0;i<height;i++)
    {
        *(dst+width*i)=*(src+width*i);
        *(dst+width*i+width-1)=*(src+width*i+width-1);
    }
    for(j=1;j<width-1;j++)
    {
        *(dst+j)=*(src+j);
        *(dst+width*(height-1)+j)=*(src+width*(height-1)+j);
    }
}

void sobel(uint8 imag[60][94],uint8 imag1[60][94])
{
    int tempx,tempy,temp;
    uint8 i=0,j=0;
    for(i=1;i <59; i++)
        {
          for(j=1;j<92;j++)
            {

                tempx=(-  imag[i-1][j-1])
                         +(-2*imag[i  ][j-1])
                         +(-  imag[i+1][j-1])
                         +(   imag[i-1][j+1])
                     +( 2*imag[i  ][j+1])
                     +(   imag[i+1][j+1]);
                if(tempx<0)
                    tempx=-tempx;

                tempy=(   imag[i+1][j-1])
                         +( 2*imag[i+1][j  ])
                         +(   imag[i+1][j+1])
                         +(-  imag[i-1][j-1])
                     +(-2*imag[i-1][j  ])
                     +(-  imag[i-1][j+1]);
                if(tempy<0)
                    tempy=-tempy;
                temp=tempx+tempy;
                if(temp>255)
                    temp=255;
                imag1[i][j]=(uint8)temp;

            }
        }
}

#define LEFT_LOST_W 0x01u   //0001
#define LEFT_LOST_B 0x02u
#define RIGHT_LOST_W 0x04u  //0100
#define RIGHT_LOST_B 0x08u

int8 Left_Board[60],Right_Board[60];
uint8 road_width[60];
uint8 lost_w_count,lost_b_count,hang_flag[60]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8 middleline[60];
void edge_search1(uint8 imag[60][94])
{
  int8 i,j,k;
   //int16 right_start,right_end,last_right;
   //int16 left_start,left_end,last_left;
 for(i=58;i>=0;i--)
 {
     hang_flag[i]=0;
//  if(i>30)
  {k=middleline[i+1];
      if(imag[i][k]==0)
          k+=10;
      if(k>=93)
          k=93;
  /*    if(imag[i][k]==0)
          {
          Left_Board[i]=Left_Board[i+1];
          Right_Board[i]=Right_Board[i+1];
          continue;
          }*/
      if(imag[i][k]==0)
      {
          for(;i>=0;i--){
          Left_Board[i]=0;
          Right_Board[i]=93;
          middleline[i]=middleline[i+1];
          hang_flag[i]=1;}
          break;

      }
    for(j=k;j>=0;j--)
       {
        if(j>0)  //ÕÒµ½1ÎªºÚ 2Îª°×µÄÊ±ºò
        {
         if( imag[i][j-1]==0x00&&imag[i][j]==0x00&&imag[i][j+1]==0xFF )    //1Îª°×0ÎªºÚ  Ôò¼ÇÂ¼1
         {
           Left_Board[i]=(uint8)j;

           break;
         }
        }
         else if (j==0)  //ÕÒµ½1µÄÊ±ºò²»Âú×ã1ºÚ2°×  Ñ­»·Ã»Ìø³öÔò½øÐÐ´ËÅÐ¶Ï
        {
          Left_Board[i]=0;
 //         hang_flag[i] |= LEFT_LOST_W;
        }
       }

       for(j=k;j<=92;j++)//´ÓÖÐ¼äÍùÓÒ±ßÉ¨
          {
            if(j<92)
            {
              if (imag[i][j-1]==0xFF&& imag[i][j]==0x00&& imag[i][j+1]==0x00)
              {
                  Right_Board[i] = (uint8)j;

                 break;
              }
            }
             if(j==92)
            {
               Right_Board[i] = 92; //ÓÒ±ß¶ªÏßÁË
 //                hang_flag[i] |= RIGHT_LOST_W;
            }
          }

  }                   //½ü´¦Ñ°Ïß½áÊø

/*  else               //Ô¶´¦±ßÑØÑ°Ïß¿ªÊ¼
  {

        if(i==30)
        {
        last_right=Right_Board[30];
        last_left=Left_Board[30];
        }

                       right_start=last_right-15;
                      right_end=last_right+5;
            if(right_start<0)
            right_start=0;
            if(right_end>92)
                right_end=92;
      if( ( imag[i][right_start]==0 )&& ( imag[i][right_start+1]==0 ))
     {
    hang_flag[i] |= RIGHT_LOST_B;
        Right_Board[i]=Right_Board[i+1];
        last_right=Right_Board[i];
     }
      else
      {
          for(j=right_start+1;j<=right_end-1;j++)
          {
              if( (imag[i][j-1]==255) && ( imag[i][j]==255 ) && ( imag[i][j+1]==0 ) )
              {
                    Right_Board[i]=(uint8)j;
                    last_right=j;
                    break;
              }
          }
      }
      if(j==right_end)
    {
        hang_flag[i] |= RIGHT_LOST_W;
        Right_Board[i]=92;
        last_right=Right_Board[i+1];
    }

                       left_start=last_left+15;
                      left_end=last_left-5;
            if(left_end<0)
            left_end=0;
            if(left_start>92)
                left_start=92;
      if( ( imag[i][left_start]==0 )&& ( imag[i][left_start-1]==0 ))
     {
     hang_flag[i] |= LEFT_LOST_B;
        Left_Board[i]=Left_Board[i+1];
        last_left=Left_Board[i];
     }
      else
      {
          for(j=left_start+1;j>=left_end-1;j--)
          {
              if( (imag[i][j+1]==255) && ( imag[i][j]==255 )  && ( imag[i][j-1]==0 ) )
              {
                    Left_Board[i]=(uint8)j;
                    hang_flag[i]=0;
                    last_left=j;
                    break;
              }
          }
      }

      if(j==left_end)
    {
        hang_flag[i] |= LEFT_LOST_W;
        Left_Board[i]=0;
        last_left=Left_Board[i+1];
    }
  }*/

         road_width[i]=Right_Board[i] - Left_Board[i];  //¼ÇÂ¼¿í¶È
         middleline[i]=(Left_Board[i]+Right_Board[i])/2;

 }
}
void edge_search2(uint8 imag[60][94])
{
  int8 i,j,k;
   //int16 right_start,right_end,last_right;
   //int16 left_start,left_end,last_left;
 for(i=58;i>=0;i--)
 {
     hang_flag[i]=0;
//  if(i>30)
  {k=middleline[i+1];
      if(imag[i][k]==0)
          k-=10;
      if(k<0)
          k=0;
  /*    if(imag[i][k]==0)
          {
          Left_Board[i]=Left_Board[i+1];
          Right_Board[i]=Right_Board[i+1];
          continue;
          }*/
      if(imag[i][k]==0)
           {
          for(;i>=0;i--){
               Left_Board[i]=0;
               Right_Board[i]=93;
               middleline[i]=middleline[i+1];
               hang_flag[i] =1;}
               break;
           }
    for(j=k;j>=0;j--)
       {
        if(j>0)  //ÕÒµ½1ÎªºÚ 2Îª°×µÄÊ±ºò
        {
         if( imag[i][j-1]==0x00&&imag[i][j]==0x00&&imag[i][j+1]==0xFF )    //1Îª°×0ÎªºÚ  Ôò¼ÇÂ¼1
         {
           Left_Board[i]=(uint8)j;

           break;
         }
        }
         else if (j==0)  //ÕÒµ½1µÄÊ±ºò²»Âú×ã1ºÚ2°×  Ñ­»·Ã»Ìø³öÔò½øÐÐ´ËÅÐ¶Ï
        {
          Left_Board[i]=0;
//          hang_flag[i] |= LEFT_LOST_W;
        }
       }

       for(j=k;j<=92;j++)//´ÓÖÐ¼äÍùÓÒ±ßÉ¨
          {
            if(j<92)
            {
              if (imag[i][j-1]==0xFF&& imag[i][j]==0x00&& imag[i][j+1]==0x00)
              {
                  Right_Board[i] = (uint8)j;

                 break;
              }
            }
             if(j==92)
            {
               Right_Board[i] = 92; //ÓÒ±ß¶ªÏßÁË
//                 hang_flag[i] |= RIGHT_LOST_W;
            }
          }

  }                   //½ü´¦Ñ°Ïß½áÊø

/*  else               //Ô¶´¦±ßÑØÑ°Ïß¿ªÊ¼
  {

        if(i==30)
        {
        last_right=Right_Board[30];
        last_left=Left_Board[30];
        }

                       right_start=last_right-15;
                      right_end=last_right+5;
            if(right_start<0)
            right_start=0;
            if(right_end>92)
                right_end=92;
      if( ( imag[i][right_start]==0 )&& ( imag[i][right_start+1]==0 ))
     {
    hang_flag[i] |= RIGHT_LOST_B;
        Right_Board[i]=Right_Board[i+1];
        last_right=Right_Board[i];
     }
      else
      {
          for(j=right_start+1;j<=right_end-1;j++)
          {
              if( (imag[i][j-1]==255) && ( imag[i][j]==255 ) && ( imag[i][j+1]==0 ) )
              {
                    Right_Board[i]=(uint8)j;
                    last_right=j;
                    break;
              }
          }
      }
      if(j==right_end)
    {
        hang_flag[i] |= RIGHT_LOST_W;
        Right_Board[i]=92;
        last_right=Right_Board[i+1];
    }

                       left_start=last_left+15;
                      left_end=last_left-5;
            if(left_end<0)
            left_end=0;
            if(left_start>92)
                left_start=92;
      if( ( imag[i][left_start]==0 )&& ( imag[i][left_start-1]==0 ))
     {
     hang_flag[i] |= LEFT_LOST_B;
        Left_Board[i]=Left_Board[i+1];
        last_left=Left_Board[i];
     }
      else
      {
          for(j=left_start+1;j>=left_end-1;j--)
          {
              if( (imag[i][j+1]==255) && ( imag[i][j]==255 )  && ( imag[i][j-1]==0 ) )
              {
                    Left_Board[i]=(uint8)j;
                    hang_flag[i]=0;
                    last_left=j;
                    break;
              }
          }
      }

      if(j==left_end)
    {
        hang_flag[i] |= LEFT_LOST_W;
        Left_Board[i]=0;
        last_left=Left_Board[i+1];
    }
  }*/

         road_width[i]=Right_Board[i] - Left_Board[i];  //¼ÇÂ¼¿í¶È
         middleline[i]=(Left_Board[i]+Right_Board[i])/2;

 }

}
/*uint8 quanzhong[35]={
        5,5,8,8,40,
        40,40,40,30,30,
        20,20,20,10,10,
        10,1,1,1,1,
        1,1,1,1,1
};*/
uint8 quanzhong[35]={
30,30,30,30,30,
45,45,45,45,45,
50,50,50,50,50,
40,40,40,40,40,
20,20,20,20,20,
10,10,10,10,10,
5,5,5,5,5
};
uint8 imagewidth =94;
uint8 imagelength=60;
uint8 image1[60][94],image2[60][94];
uint8 image_threshold;  //图像阈值
uint32 use_time;

#define MOTOR1_PWM1  TOM1_CH4_P11_2
#define MOTOR1_PWM2  TOM1_CH5_P11_3
#define Dir_pwm   TOM1_CH1_P33_9
#define Pmax   3700//最大3700
#define Pmin 2200//最下2200
#define Duty   2950
//#define Ksp   10000
//#define Ksi  30

#define Ksp  1200
#define Ksi  80
#define Ksd   0
#define Kfp   2.8

#define Kfd  0


#define MOTOR1_DIR   P11_2              //定义1电机方向控制引脚
#define MOTOR1_DIR1   TOM1_CH1_P11_2
#define MOTOR1_PWM   TOM0_CH10_P11_3    //定义1电机PWM引脚
#define MOTOR1_PWM3   P11_3

float  speed=2;
int32 error1=0,error2=0;
uint32 output1=Duty;
int32 output2=Duty;
int16 encoder;
float encoderspeed;

uint16  ad_value3=0;
uint16  ad_value2=0;
uint16  ad_value1=0;
uint16  ad_value4=0;
uint16  ad_value5=0;
uint16 ad_value6=0;
uint16  ad_value7=0;
uint8 ad_test3=90;
uint8 ad_test2=4;
uint8 ad_test1=30;
uint8 ad_test4=8;
uint8 ad_test5=30;
uint8 ad_test6=41;
uint8 ad_test7=69;

uint8 flag1=1;
uint8 divFlag=0;
uint8 indivFlag=0;
uint8 outdivFlag=0;
uint8 drawFlag=0;
uint8 ingarage =0;

uint8 outgarFlag=1;
uint8 PoFlag=0;
uint8 ShangFlag=0;
uint8 xiaFlag=0;
uint8 loseflag=0;
uint8 drawFlag1=1;
uint8 drawingFlag=0;//从点划线未丢线
uint8 drawFlag2=0;//丢线从中点以恒定曲率划线
uint8 left=0;
//void lose_check(){
//if(drawFlag1)
//{
//    uint8 i,j=0;
//    drawFlag2=0;
//   for(i=0;i<35;i++)
//       if(Right_Board[i]>90)
//       {
//           j++;
//       }
//    if((j>=30)&&(drawFlag1))
//    {
//        drawFlag1=0;
//        drawFlag2=1;
//    }
//    if((j==0)&&(drawFlag2)){
//
//        outgarFlag=0;
//
//    }
//
//}
//}




void out_garage(){uint8  i;
    if(outgarFlag)

    {
for(i=9;i<50;i++)
    middleline[i]=70;
        if((ad_value3>0.7*ad_test1))
        {
            outgarFlag=0;
        }


    }


}



uint8 InRingFlag=0,RunRingFlag=0,OutRingFlag=0,GoFlag=0,LoseFlag=0,FindFlag=0,CanDiv=0,CanRing=1,CanStraight=0;
//uint8 Ring1=1;//防止反复检测执行进环岛标志，并不能区分第一圈第二圈
uint8 Ring1=1;
void ring_check()//电磁检测要各种补线时刻
{
if((ad_value3>=1.8*ad_test3)&&Ring1)
{

    InRingFlag=1;
    Ring1=0;
    CanStraight=0;
    CanRing=1;
}
/*if((InRingFlag == 1)&&(ad_value4<26*ad_test3))
{RunRingFlag = 1;
InRingFlag = 0;}*/

if((InRingFlag == 1)&&(ad_value3 <ad_test3)&&(ad_value5>1.1*ad_test5))
{InRingFlag = 0;

OutRingFlag = 1;}

if((ad_value3>1.3*ad_test3)&&(OutRingFlag == 1))
{
    LoseFlag=0;
    FindFlag=0;
GoFlag=1;
OutRingFlag=0;
//drawFlag2=0;
}
if((ad_value3 <1.2*ad_test3)&&(ad_value1<1.2*ad_test1)&&(ad_value5<1.2*ad_test5)&&GoFlag)
{

GoFlag=0;
CanDiv=1;
divFlag=1;
left=0;
CanRing=0;
PoFlag=1;

}

}


/** 环岛画线处理 ** 说明： */
void draw_line_for_ring()
{
  if(InRingFlag)
  {     //     printf("InRingFlag=%d,Ringkind=%d\n",InRingFlag,Ringkind);
      uint8 i,j,k,m;
      drawFlag=0;
      for(i=45;i>2;i--)
               {
                  if ((Left_Board[i]-Left_Board[i+1]>20))
                                    {
                                        j=Left_Board[i];
                                        k=j-1;
                                        m=i+2;
                                        drawFlag=1;
                                        break;
                                    }
                  else if ((Right_Board[i+1]-Right_Board[i]>12))
                                    {
                      if(Right_Board[i]<85){
                                        j=Right_Board[i];
                                        k=j-1;
                                        m=i+2;
                                        drawFlag=1;}
                                        break;
                                    }
               }
//      if(!drawFlag){
//          i=0;
//          j=30;
//          while(i<59&&j>0)
//          {
//              Left_Board[i]=j;
//              image2[i][Left_Board[i]]=0;
//              middleline[i]=(Left_Board[i]+Right_Board[i])/2;
//              i++;
//              j--;
//          }
//      }
               while((drawFlag)&&(i<50)&&(j>1))
               {

                   Left_Board[i]=j;
 //                  image2[i][Left_Board[i]]=0;
                   middleline[i]=(Left_Board[i]+Right_Board[i])/2;
                   i++;
                   j-=2;}
      while((drawFlag)&&(m>9)&&(k<93))
                     {

                         Left_Board[m]=k;
  //                       image2[m][Left_Board[m]]=0;
                         middleline[m]=(Left_Board[m]+93)/2;
                         m--;
                         k+=2;}
//      uint8 i=10,j=20;
//      while((i<=50)) {
//                   middleline[i]=20;
//                   i++;
//                   }



  }
  else if(OutRingFlag)//出环岛丢线情况
  {
     uint8 i,j;


               //   lose_check();//是否丢线检查
                 uint8 LRightDrawFlag=0;


                        i=10;
                   while((i<=50)&&(LRightDrawFlag==0)&&!LoseFlag)
                   {
                       i++;
                       if((Left_Board[i]-Left_Board[i-1]>3)&&Left_Board[i-2]<20&&!hang_flag[i-1])
                       { LRightDrawFlag=1; j=Left_Board[i];
                       FindFlag=1;
                       }
                       else if(FindFlag)
                       {
                           LoseFlag=1;
                       }

                   }
                   while((i>0)&&(j>2)&&(LRightDrawFlag==1)&&!LoseFlag) {

                   Left_Board[i]=j;

   //                image2[i][Left_Board[i]]=0;
                   middleline[i]=(Left_Board[i]+Right_Board[i])/2;
                   i--;
                   j+=2;}



                    if(LoseFlag){

                       i=40;
                                j=0;
                            while((i>10)&&(j<94))

                            {
                                Left_Board[i]=j;
         //                       image2[i][Left_Board[i]]=0;

                                middleline[i]=(Left_Board[i]+93)/2;
                                i--;
                                j+=2;
                            }



                   }
}
  else   if(GoFlag)
  {          //printf("InRingFlag=%d,Ringkind=%d\n",InRingFlag,Ringkind);
     uint8 i=0,j;
             uint8 LRightDrawFlag=0;
             while((i<=50)&&(LRightDrawFlag==0))
             {
                 i++;
                 if((Right_Board[i+1]-Right_Board[i]>=10))
                 {LRightDrawFlag=1;
                 j=Right_Board[i];}
                 else if((Left_Board[i]-Right_Board[i+1]>=10))
                                  {LRightDrawFlag=1;
                                  j=Left_Board[i];}

             }

             while((i<=50)&&(j<94)&&(LRightDrawFlag==1)) {

             Right_Board[i]=j;
  //            image2[i][Right_Board[i]]=0;
             middleline[i]=(Left_Board[i]+Right_Board[i])/2;
             i++;
             j++;
             }

//      uint8 i=10;
//      for(i=10;i<50;i++)
//      {
//          middleline[i]=47;
//
//      }


  }
}

void div_check()//三岔路口检测
{

//    if((ad_value6<0.9*ad_test6)&&(ad_value7<0.9*ad_test7)&&(ad_value3<ad_test3)&&(ad_value3>0.3*ad_test3)&&!outdivFlag)
//    {
//    divFlag = 1;
//    }
    if((ad_value1<0.5*ad_test1)&&(ad_value3<0.5*ad_test3)&&(ad_value5<0.6*ad_test5)&&divFlag)
    {
        outdivFlag=1;
        divFlag=0;

    }
//    if((ad_value1<0.2*ad_test1)&&(ad_value2>0.6*ad_test2)&&(ad_value3<0.4*ad_test3)&&(ad_value4>0.5*ad_test4)&&(ad_value5>0.5*ad_test5)&&(ad_value6<0.3*ad_test6)&&(ad_value7<0.3*ad_test7)&&indivFlag)
//    {
//    outdivFlag=1;
//    divFlag=0;
//    indivFlag=0;
//    }

 }
 void div_line()
 {   uint8 i,j,m,n;
 uint8 drawFlag=0;
 if((divFlag||outdivFlag)&&flag1)//第一圈左下角向右上角划线
     {
         for(i=50;i>1;i--)
         {
             if (Left_Board[i]>=15&&(Left_Board[i]-Left_Board[i+1]>5)&&image2[i][Left_Board[i]-15]==0xff&&hang_flag[i-1]==0)
             {
                 j=Left_Board[i];
                 m=i-1;
                  n=j+2;
                 drawFlag=1;
                 break;
             }
             else if ((Right_Board[i+1]-Right_Board[i]>15)&&hang_flag[i-1]==0)
                               {
                                   j=Right_Board[i];
                                   m=i-1;
                                   n=j+2;
                                   drawFlag=1;
                                   break;
                               }
         }
        while((drawFlag)&&(i<50)&&(j>=2))
         {

             Left_Board[i]=j;
 //           image2[i][Left_Board[i]]=0;
             middleline[i]=(Left_Board[i]+Right_Board[i])/2;
             i++;
             j-=2;
         }
        while((drawFlag)&&(m>=10)&&(n<94))
                 {

                     Left_Board[m]=n;
  //                  image2[m][Left_Board[m]]=0;
                     middleline[m]=(Left_Board[m]+93)/2;
                     m--;
                     n+=2;
                 }
    }

 else if((divFlag||outdivFlag)&&!flag1)
 {
     for(i=50;i>1;i--)
              {
                 if (Left_Board[i]>=15&&(Left_Board[i]-Left_Board[i+1]>5)&&image2[i][Left_Board[i]-15]==0xff&&hang_flag[i-1]==0)
                 {
                     j=Left_Board[i];
                     m=i-1;
                     n=j-2;
                     drawFlag=1;
                     break;
                 }
                 else if ((Right_Board[i+1]-Right_Board[i]>15)&&hang_flag[i-1]==0)
                                   {
                                       j=Right_Board[i];
                                       m=i-1;
                                       n=j-2;
                                       drawFlag=1;
                                       break;
                                   }
              }
     while((drawFlag)&&(i<50)&&(j<=91))
                   {

                       Right_Board[i]=j;
 //                      image2[i][Right_Board[i]]=0;
                       middleline[i]=(Left_Board[i]+Right_Board[i])/2;
                       i++;
                       j+=2;}


              while((drawFlag)&&(m>9)&&(n>1))
              {

                  Right_Board[m]=n;
//                  image2[m][Right_Board[m]]=0;
                  middleline[m]=(Right_Board[m])/2;
                  m--;
                  n-=2;}

              }
// else if(outdivFlag&&!flag1)
// { drawFlag2=0;
//     for(i=10;i<35;i++)
//     {
//         if((Left_Board[i]-Left_Board[i-1]>5)&&(Left_Board[i-1]>5))
//         {
//           j=Left_Board[i];
//           drawFlag2=1;
//           break;
//         }
//     }
//     while((drawFlag2)&&(i>10)&&(j<=60))
//                   {
//
//                       Left_Board[i]=j;
//                       image2[i][Left_Board[i]]=0;
//                       middleline[i]=(Left_Board[i]+Right_Board[i])/2;
//                       i--;
//                       j--;}
//     for(i=50;i>1;i--)
//              {
//                 if ((Left_Board[i]-Left_Board[i+1]>10))
//                 {
//                     j=Left_Board[i];
//                     m=i-1;
//                     n=j-2;
//                     drawFlag=1;
//                     break;
//                 }
//                 else if ((Right_Board[i+1]-Right_Board[i]>10))
//                                   {
//                                       j=Right_Board[i];
//                                       m=i-1;
//                                       n=j-2;
//                                       drawFlag=1;
//                                       break;
//                                   }
//              }
//     while((drawFlag)&&(i<50)&&(j<=91))
//                   {
//
//                       Right_Board[i]=j;
//                       image2[i][Right_Board[i]]=0;
//                       middleline[i]=(Left_Board[i]+Right_Board[i])/2;
//                       i++;
//                       j+=2;}
//
//
//              while((drawFlag)&&(m>9)&&(n>1))
//              {
//
//                  Right_Board[m]=n;
//                  image2[m][Right_Board[m]]=0;
//                  middleline[m]=(Right_Board[m])/2;
//                  m--;
//                  n-=2;}
//
//
// }
 }
/** 斑马线检测 ** 说明： */
uint8 FinishFlag=0;//跑完两圈打开
uint8 ZebraLineFlag=0;
void zebra_line_check()
{ uint8 i,j;
uint8 JumpCount=0;
ZebraLineFlag=0;
uint8 ZebraLineCount[60]={0,0,0,0,0,0,0,0,0,0};
for(i=59;i>=5;i--) { JumpCount=0; for(j=20;j<=72;j++)
{ if((image2[i][j]&&!image2[i][j+1]) ||(!image2[i][j]&&(image2[i][j+1])))
{ JumpCount++; } }

    ZebraLineCount[i]=JumpCount;
}

for(i=59;i>5;i--)
{ if(((ZebraLineCount[i]==ZebraLineCount[i+1])) &&(ZebraLineCount[i]>=10))
{ ZebraLineFlag=1; }

} }
//第一圈斑马线应进行补线直行，第二圈应进行补线进环岛。

/** 车库画线处理 ** 说明： */
uint8 RightGarageFlag = 0;
uint8 LeftGarageFlag = 0;
uint8 DrawFlag=0,j_in=0;
//注意求一个prelastline
void draw_line_for_garage()

{
    if(FinishFlag == 1)//FinishFlag
{
        uint8 i=0,j;
                      DrawFlag=0;
                     while((i<=50)&&(DrawFlag==0))
                     {
                         i++;
                         if((Left_Board[i]-Left_Board[i+1]>=10))
                         {DrawFlag=1;
                         j=Left_Board[i];}

                     }

                     while((i<=59)&&(j<92)&&(DrawFlag==1)) {

                     Right_Board[i]=j;

 //                     image2[i][Right_Board[i]]=0;
                     middleline[i]=(Right_Board[i])/2;
                     i++;
                     j+=4;}
       }


}
uint8 ShiziFlag=0;
 void draw_straightline()
 {   ShiziFlag =0;
     if((ad_value2>10*ad_test2)&&(ad_value3<1.2*ad_test3)&&(ad_value4>10*ad_test4))

     {
         ShiziFlag=1;
xiaFlag=0;
flag1=0;
     }
     if(ZebraLineFlag&&!ingarage)
     { uint8 i;
         for(i=10;i<50;i++)
         {
             middleline[i]=47;
         }
         CanRing=1;
     }
     else if(ShiziFlag)
     { uint8 i,j;
      uint8 DrawFlag1=0,DrawFlag2=0;
         for(i=10;i<40;i++)
         {
           if(Left_Board[i]-Left_Board[i+1]>5)
           {
               j=Left_Board[i];
               DrawFlag1=1;
               break;
           }
         }
         while(i<50&&j>0&&DrawFlag1)
         {
             Left_Board[i]=j;
//             image2[i][Left_Board[i]]=0;
             i++;
             j--;
         }
         for(i=10;i<40;i++)
         {
           if(Right_Board[i+1]-Right_Board[i]>5)
           {
               j=Right_Board[i];
               DrawFlag2=1;
               break;
           }
         }
         while(i<50&&j<94&&DrawFlag2)
         {
             Right_Board[i]=j;
//             image2[i][Left_Board[i]]=0;
             i++;
             j++;
         }
     }
 }

 void Right_check()
 {
     if(!ZebraLineFlag&&!InRingFlag&&!OutRingFlag&&!GoFlag)
     {
         uint8 i=37,j=93,k;

         for(k=30;k>15;k--)
         {
             if((Right_Board[k-1]-Right_Board[k]>4)&&(Right_Board[k-1]==92)&&(Right_Board[k-3]==92)&&(Right_Board[k-5]==92)&&(Right_Board[k-7]==92)&&(Right_Board[k-10]==92)&&(Right_Board[5]<90))
             {
                 left=1;

                 break;
             }
         }
         while(i>5&&j>1&&left)
         {

             Right_Board[i]=j;
//              image2[i][Right_Board[i]]=0;
             middleline[i]=(Left_Board[i]+Right_Board[i])/2;
             i--;
             j--;
         }
     }
 }

int32 outputs2=0;
float  error_speed1=0,error_speed2=0;
float error_speed=0;
void core0_main(void)
{
    uint16 i,j;
    uint8 *p = image1[0],*q = image2[0];

	get_clk();//获取时钟频率  务必保留

    //目前的库采集总钻风 图像最后一列为固定的黑色
	//这是由于单片机造成的，不是摄像头的问题
    //显示模式设置为2  横屏模式
    //显示模式在tft的h文件内的TFT_DISPLAY_DIR宏定义设置
    lcd_init();     //初始化TFT屏幕

    //等待所有核心初始化完毕

	pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
	gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDB_P33_5);
    seekfree_wireless_init();
    mt9v03x_init(); //初始化摄像头
    //如果屏幕一直显示初始化信息，请检查摄像头接线

	//用户在此处调用各种初始化函数等

	gtm_pwm_init(56, 10000, 0);
	gtm_pwm_init(61, 10000, 0);
	        //初始化舵机引脚

	gtm_pwm_init(Dir_pwm, 200,output1);
	//初始化PWM引脚
//gtm_pwm_init(MOTOR1_PWM, 10000, 0);

	//初始化方向控制引脚
//	gpio_init(MOTOR1_DIR, GPO, 0, PUSHPULL);
//    icm20602_init_spi();
adc_init(ADC_0, ADC0_CH11_A11);//4
adc_init(ADC_0, ADC0_CH8_A8);//6

adc_init(ADC_0, ADC0_CH5_A5);//7
adc_init(ADC_0, ADC0_CH9_A9);//2
adc_init(ADC_0, ADC0_CH6_A6);//1
adc_init(ADC_0, ADC0_CH7_A7);
adc_init(ADC_0, ADC0_CH10_A10);


    enableInterrupts();

	while (TRUE)
	{

//        systick_start(STM0);

		if(mt9v03x_finish_flag)
        {




		    for(i=0;i<60;i++)
		        for(j=0;j<94;j++)
		        {
		            image1[i][j]=mt9v03x_image[i][2*j];
		        }
		    mt9v03x_finish_flag = 0;//在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
		                //注意：一定要在图像使用完毕后在清除此标志位
//		    seekfree_sendimg_03x(UART_0, p, 94, 60);
            medianBlur(p,q,94,60);
//            seekfree_sendimg_03x(UART_0, q, 94, 60);
            image_threshold = otsuThreshold(q,94,60);  //大津法计算阈值

            sobel(image2,image1);
            for(i=0; i<5639; i++)
            {
                if((q[i]<(image_threshold))||(p[i]>100))
                    q[i] = 0x00;
                else
                    q[i] = 0xff;
            }
//            for(i=0; i<5639; i++)
//            {
//                if(q[i]<image_threshold)
//                    q[i] = 0x00;
//                else
//                    q[i] = 0xff;
//            }

            ad_value1 = adc_convert(ADC_0, ADC0_CH6_A6,   ADC_8BIT);
            ad_value2 = adc_convert(ADC_0, ADC0_CH9_A9,   ADC_8BIT);
            ad_value3= adc_convert(ADC_0, ADC0_CH11_A11,   ADC_8BIT);
            ad_value4 = adc_convert(ADC_0, ADC0_CH8_A8, ADC_8BIT);
            ad_value5  =adc_convert(ADC_0,ADC0_CH5_A5,ADC_8BIT);
//            ad_value6 = adc_convert(ADC_0, ADC0_CH10_A10, ADC_8BIT);
//            ad_value7 = adc_convert(ADC_0, ADC0_CH7_A7, ADC_8BIT);
//                         printf("ad_value1 %d\n", ad_value1);
//                         printf("ad_value2 %d\n", ad_value2);
//                         printf("ad_value3 %d\n", ad_value3);
//                         printf("ad_value4 %d\n", ad_value4);
//                         printf("ad_value5 %d\n", ad_value5);
            if(((ad_value1<=2)&&(ad_value5<=2)&&(ad_value3<=2)&&(ad_value4<=2)&&(ad_value2<=2)&&!outgarFlag)||FinishFlag)
            {
                pwm_duty(56, 0);
                pwm_duty(Dir_pwm,2300);
                while( encoder>0)
                {
                    pwm_duty(61, 1000);
                }
                pwm_duty(61, 0);
                break;
            }
if( image2[58][46]==0xff)
            middleline[59]=46;
else if(image2[58][56]==0xff)
    middleline[59]=56;
else if(image2[58][36]==0xff)
    middleline[59]=36;
else if(image2[58][26]==0xff)
    middleline[59]=26;
else if(image2[58][66]==0xff)
    middleline[59]=66;
            if((flag1&&!InRingFlag)||CanStraight){
                edge_search1(image2);
            }
            else{
                edge_search2(image2);
            }
//
//          draw_line_for_garage();
//          if(CanStraight){
//          zebra_line_check();
//          if(ingarage&&ZebraLineFlag )//如果第一圈检测到斑马线将中线置为最中间
//          {
//               FinishFlag=1;
//          }
//         draw_straightline();
//          }

//          if(CanRing){
////        Right_check();
//        ring_check();
//        draw_line_for_ring();
//         }
//         if(CanDiv){
//        div_check();//考虑将这几个电磁检测的合并成一个，减少重复判断
//         div_line();
//         }
//       out_garage();
////        draw_line_for_garage();
//
//       if(middleline[40]=46&&ad_value3>1.2*ad_test3&&PoFlag&&!ShangFlag&&flag1)
//          {
//
//              ShangFlag=1;
//              outdivFlag=0;
//                 CanDiv=0;
//                 CanStraight=1;
//
//
//                         Ring1=1;
//          }
//       else if(middleline[40]=46&&ad_value3>1.2*ad_test3&&PoFlag&&!ShangFlag&&!flag1)
//          {
//           CanDiv=0;
//              ShangFlag=1;
//              outdivFlag=0;
//                                                             CanStraight=1;
//
//                                                             ingarage=1;
//          }
//          if(ShangFlag)
//          { uint16 i;
//            for(i=10;i<30;i++)
//            {
//                middleline[i]=middleline[i+20];
//                middleline[i+20]=46;
//            }
//
//          }

//            if((ad_value3<1.1*ad_test3)&&(ad_value1<1.25*ad_test1)&&(ad_value5<1.25*ad_test5)&&ShangFlag)
//          {
//
//             xiaFlag=1;
//              PoFlag=0;
//              ShangFlag=0;
//          }
//            if((encoderspeed>2.4)&&ShangFlag)
//          {
//             xiaFlag=1;
//              PoFlag=0;
//              ShangFlag=0;
//
//          }

//            if((ad_value3>ad_test3)&&xiaFlag)
//            {
//                ShangFlag=0;
//                xiaFlag=0;
//            }

// printf("InRingFlag=%d\nRunRingFlag=%d\nOutRingFlag=%d\ndivFlag=%d\n,indivFlag=%d\n,GoFlag=%d\n",InRingFlag,RunRingFlag,OutRingFlag,divFlag,indivFlag,GoFlag);
//         printf("divFlag =%d\n,indivFlag=%d\n,outdivFlag=%d\n,flag1=%d\n",divFlag,indivFlag,outdivFlag ,flag1);
//       printf("ingarage=%d\n,ZebraLineFlag=%d\n,DrawFlag=%d\n",ingarage,ZebraLineFlag,DrawFlag);
//      printf("FindFlag=%d\n,loseFlag=%d\n",FindFlag,LoseFlag);

//          for(i=0;i<60;i++)
//            {   image2[i][middleline[i]]=0;
//               }
//          lcd_displayimage032_zoom(q, imagewidth, imagelength, 160, 120);


  //        seekfree_sendimg_03x(UART_0, q, 94, 60);
draw_straightline();
            error1=error2;
            error2=0;
            for(i=0;i<=34;i++)
            {

                error2+=(quanzhong[i]*(middleline[i+10]-46));

            }
            error2=error2/985;//345;
//            use_time = systick_getval_us(STM0);                        //计算大津法程序消耗时间，单位微秒。
    //     printf("%d\n",InRingFlag);
if(InRingFlag||OutRingFlag||GoFlag)
	           output2=-24.5*error2-90*(error2-error1)+Duty;//舵机pd控制输出,可利用多个error提前预判
else
    output2=-(     (1-      exp(     -0.4*abs(error2)        ))       /   (exp(    -0.4*abs(error2)   )+1)    +1)*13*error2-25*(error2-error1)+Duty;//舵机pd控制输出,可利用多个error提前预判
 //           output2=5.8*error2+Kfd*(error2-error1)+Duty;//舵机pd控制输出,可利用多个error提前预判
	//       printf("%d\n"  ,  output2);
//	           get_icm20602_accdata_spi();
//	           get_icm20602_gyro_spi();

//
//	           printf("icm_acc_x:  %d\n", icm_acc_x);
//	           printf("icm_acc_y:  %d\n", icm_acc_y);
//	           printf("icm_acc_z:  %d\n", icm_acc_z);
//	           printf("icm_gyro_x: %d\n", icm_gyro_x);
//	           printf("icm_gyro_y: %d\n", icm_gyro_y);
//	           printf("icm_gyro_z: %d\n", icm_gyro_z);


//	           printf("poflag=%d\n,ShangFlag=%d\n,output2=%d\n",PoFlag,ShangFlag,output2);
	           if(output2>=Pmax)
	               output2=Pmax;
	           if(output2<=Pmin)
	               output2=Pmin;//限制幅值
	            //控制舵机达到指定位置
	           output1=output2;
	            pwm_duty(Dir_pwm,output1);
	          //电机pid闭环控制
            //  speed=(uint32)(124-2.5*abs(error2))*13;
//速度pid?
              //查看一般error的值看写出理想下error与理想速度的表达式
	            speed=(2.3 -0.04*abs(error2));
//	            if(InRingFlag)
//	            {
//	                speed=1.6;//由1.8到2.2
//	            }
	            if(xiaFlag)
	            {
	                speed=1.7;
	            }

//                if(RunRingFlag||OutRingFlag)
//                {
//                    speed=2.7;//由1.8到2.2
//                }
//   printf("速度%d\n",encoderspeed);
//speed=2;
	        //用户在此处编写任务代码



        }

	//else if((outputs2<1400)&&(outputs2>0))
	//outputs2=1000;
//	if(InRingFlag||OutRingFlag)
//	outputs2=1500;
	// printf("error=%d\n", error2);
	//  printf("outputs2=%d\n", outputs2);
	 //        printf("speed=%f\n,speed2=%f\n",speed,encoderspeed);

//
//		SDS_OutData[0] =speed*100;
//		SDS_OutData[1] = encoderspeed*100;
//		SDS_OutData[2] = outputs2/10;
//		SDS_OutPut_Data(SDS_OutData);
	//outputs2=3000;

        if(0<=outputs2) //电机1   正转 设置占空比为 百分之 (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
                {
            pwm_duty(56, 0);
                    pwm_duty(61, outputs2);

                }
                else                //电机1   反转
                {
                    pwm_duty(61, 0);
                    pwm_duty(56, -outputs2);

                }
//        use_time = systick_getval_us(STM0);                        //计算大津法程序消耗时间，单位微秒。
//          printf("usetime=%d\n",use_time);

	}

}



