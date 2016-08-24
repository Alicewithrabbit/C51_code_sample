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
// �˱�Ϊ LED ����ģ    
// 0   1   2   3   4   5   6   7   8   9   clear
unsigned char code Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
unsigned char count_1s,count,count1,flag_1s;
unsigned char flag,flag1=1;	   //0->red;   1->green;   2->yellow
unsigned char led_cache[4];	  //��ʾ���ݻ���
void zd_ini()         //�жϳ�ʼ������ӿ� 
{
	TMOD=0x11;					//��ʱ��0,1ѡ������ʽ1��0001 0001b
	TH0=0X3C;						//��ʱ50ms��ֵ	
	TL0=0XB0;
	ET0=1;							//����ʱ���ж�
	EA=1;								//�����ж�
	TR0=1;
	ET1=1;							//������ʱ��0
}

void system_ini()			//ϵͳ��ʼ���ӿ�
{
	flag=0;
	count_1s=20;       	//20*50ms=1s;	  
	count=63;
  count1=60;
	zd_ini();	       		//�����жϳ�ʼ������
	LED_1=0;
	LED_2=0;
	LED_3=0;
	LED_4=0;
	LED_5=0;
	LED_6=0;
	LED_7=0;
	LED_8=0;	
}

void timer_0() interrupt 1    //��ʱ���ж�0�ӿ�
{
	TH0=0X3C;				  					//��������ֵ	
	TL0=0XB0;
	if(--count_1s)  		  			//���û��1s���򷵻�
	{ return;}
	//��1s
	flag_1s=1;				  				//��λ��־λ
	count_1s=20;
}

void show()					  				//���ڼ���Ͳ��ת����Ӧ�Ĵ���ʾ���ӿ�
{
	 //������
	 led_cache[0]=count/10;					//��λ
	 led_cache[1]=count%10;				 	//��λ

	 led_cache[0]=Disp_Tab[led_cache[0]];
	 led_cache[1]=Disp_Tab[led_cache[1]];

	 //�ϱ���
	 led_cache[2]=count1/10;			 	 //��λ
	 led_cache[3]=count1%10;				 //��λ

	 led_cache[2]=Disp_Tab[led_cache[2]];
	 led_cache[3]=Disp_Tab[led_cache[3]];
}

void update()				    //����count��count1��ֵ���л�LED�ƽӿ�
{

			
			if(flag==0)
				{
					
					if(count==0)
						{////////////////////////////////
							flag=1;				 //�̵���
							flag1=0;			 //���1��
							count=60;			 
							count1=63;
						}
						
            else if(count1==0)
            {	///////////////////////////
								
								flag1=2;	//�Ƶ�1��
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
					flag=2;			   //�Ƶ���
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
					flag=0;				 //�����
  					flag1=1;			 //�̵�1��
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
void disp()		   	//�ܵ���ʾ�ӿ�
{
	int i;
	show();	//�������ڼ���Ͳ��ת����Ӧ�Ĵ���ʾ����ģ��
	P22=0;	//�����λѡͨ�ź�
	P23=0;
	P24=0;	
	PB=led_cache[0];
	for(i=0;i<30;i++);		//��ʱ
	P22=1;	
	P23=0;
	P24=0;	
	PB=led_cache[1];
	for(i=0;i<30;i++);	  	//��ʱ
	P22=0;	//�����λѡͨ�ź�
	P23=1;
	P24=0;	
	PB=led_cache[2];
	for(i=0;i<30;i++);		//��ʱ
	P22=1;	
	P23=1;
	P24=0;	
	PB=led_cache[3];
	for(i=0;i<30;i++);		//��ʱ
}
////////////////////////////////////////////
void LED_Activity(){
	int ret=1;
	while(ret)											//��������Լ���Ҫ��
	{	
		
		if(TestKey()){
			ret=0;
			Clear();
		}
		if(flag_1s)
		{
			update();		   	//������ʾ		
			flag_1s=0;			//���1��ʱ�䵽�ı�־
			dyna(cs);
			cs=~cs;		 	
		}

		disp();					//������ʾ
	}		
}