/*--------------------------------------------------------------------------
Made by 吴崇
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __FRAG3_H__
#define __FRAG3_H__
sbit P22=P2^2; //数码管选通
sbit P23=P2^3;
sbit P24=P2^4;
sbit LED_1=P0^0;
sbit LED_2=P0^1;
sbit LED_3=P0^2;
sbit LED_4=P0^3;
sbit LED_5=P0^4;
sbit LED_6=P0^5;
sbit LED_7=P0^6;
sbit LED_8=P0^7;
extern unsigned char code Disp_Tab[];
extern unsigned char count_1s,count,count1,flag_1s;
extern unsigned char flag,flag1;	   //0->red;   1->green;   2->yellow
extern unsigned char led_cache[4];	  //显示数据缓存
void system_ini();
void disp();
void LED_Activity();
#endif