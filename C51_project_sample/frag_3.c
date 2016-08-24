#include<reg52.h>
#include<absacc.h>
#include"frag1.h"
#include"frag2.h"
#include"frag3.h"
#include"frag4.h"
#define PA XBYTE [0x7ffc]
#define PB XBYTE [0x7ffd]
#define PC XBYTE [0x7ffe]
#define COM XBYTE [0x7fff]
// 此表为 LED 的字模    
// 0   1   2   3   4   5   6   7   8   9   clear
unsigned char code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
unsigned char count_1s,count,count1,flag_1s;
unsigned char flag,flag1=1;	   //0->red;   1->green;   2->yellow
unsigned char led_cache[4];	  //显示数据缓存
void zd_ini()         //中断初始化程序接口 
{
	TMOD=0x11;					//定时器0,1选择工作方式1，0001 0001b
	TH0=0X3C;						//定时50ms初值	
	TL0=0XB0;
	ET0=1;							//开定时器中断
	EA=1;								//开总中断
	TR0=1;
	ET1=1;							//开启定时器0
}

void system_ini()			//系统初始化接口
{
	flag=0;
	count_1s=20;       	//20*50ms=1s;	  
	count=63;
  count1=60;
	zd_ini();	       		//调用中断初始化程序
	LED_1=0;
	LED_2=0;
	LED_3=0;
	LED_4=0;
	LED_5=0;
	LED_6=0;
	LED_7=0;
	LED_8=0;	
}

void timer_0() interrupt 1    //定时器中断0接口
{
	TH0=0X3C;				  					//继续赋初值	
	TL0=0XB0;
	if(--count_1s)  		  			//如果没到1s，则返回
	{ return;}
	//到1s
	flag_1s=1;				  				//置位标志位
	count_1s=20;
}

void show()					  				//用于计算和查表转换相应的待显示数接口
{
	 //东西向
	 led_cache[0]=count/10;					//高位
	 led_cache[1]=count%10;				 	//低位

	 led_cache[0]=Disp_Tab[led_cache[0]];
	 led_cache[1]=Disp_Tab[led_cache[1]];

	 //南北向
	 led_cache[2]=count1/10;			 	 //高位
	 led_cache[3]=count1%10;				 //低位

	 led_cache[2]=Disp_Tab[led_cache[2]];
	 led_cache[3]=Disp_Tab[led_cache[3]];
}

void update()				    //更新count和count1的值，切换LED灯接口
{

			
			if(flag==0)
				{
					
					if(count==0)
						{////////////////////////////////
							flag=1;				 //绿灯亮
							flag1=0;			 //红灯1亮
							count=60;			 
							count1=63;
						}
						
            else if(count1==0)
            {	///////////////////////////
								
								flag1=2;	//黄灯1亮
								count1=3;
            }
						
						else
						{							
								count--;
								count1--;
						}
						
				}
				
			else if(flag==1)
			{
				
				if(count==0)
				{/////////////////////////////////////
					flag=2;			   //黄灯亮
					count=3;
				}
				else
					{
						count--;
            			count1--;
					}
			}
			else
			{
				if(count==0)
				{////////////////////////////////////////
					flag=0;				 //红灯亮
  					flag1=1;			 //绿灯1亮
          			count1=60;
					count=63;
				}
				else
					{	
						count--;
						count1--;
					}
			}

		if(flag==0&&flag1==1) {
		Page_ = 0x02;
		Column = 0x60;
		Code_ = 0x1C;
		WriteCHN16x16();
		}
		if(flag==1&&flag1==0) {
		Page_ = 0x02;
		Column = 0x00;
		Code_ = 0x1D;
		WriteCHN16x16();		
		}
		if(flag==2||flag1==2) {
		Clear();
	
		}


}
void disp()		   	//总的显示接口
{
	int i;
	show();	//调用用于计算和查表转换相应的待显示数的模块
	P22=0;	//输出低位选通信号
	P23=0;
	P24=0;	
	PB=led_cache[0];
	for(i=0;i<30;i++);		//延时
	P22=1;	
	P23=0;
	P24=0;	
	PB=led_cache[1];
	for(i=0;i<30;i++);	  	//延时
	P22=0;	//输出低位选通信号
	P23=1;
	P24=0;	
	PB=led_cache[2];
	for(i=0;i<30;i++);		//延时
	P22=1;	
	P23=1;
	P24=0;	
	PB=led_cache[3];
	for(i=0;i<30;i++);		//延时
}
////////////////////////////////////////////
void LED_Activity(){
	int ret=1;
	while(ret)											//这里根据自己需要改
	{	
		
		if(TestKey()){
			ret=0;
			Clear();
		}
		if(flag_1s)
		{
			update();		   	//更新显示		
			flag_1s=0;			//清除1秒时间到的标志
			dyna(cs);
			cs=~cs;		 	
		}

		disp();					//持续显示
	}		
}