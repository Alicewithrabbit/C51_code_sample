#include<reg52.h>
#include"frag1.h"
#include"frag2.h"
#include"frag4.h"
#include"musicplayer.h"
unsigned char timer0h,timer0l,time,zt=1;
//单片机晶振采用11.0592MHz
// 频率-半周期数据表 高八位     本软件共保存了四个八度的28个频率数据
code unsigned char FREQH[] = {
             0xF2, 0xF3, 0xF5, 0xF5, 0xF6, 0xF7, 0xF8,    //低音1234567
             0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0xFC,//1,2,3,4,5,6,7,i
             0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE,            //高音 234567
             0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF};   //超高音 1234567
          
// 频率-半周期数据表 低八位
code unsigned char FREQL[] = {
              0x42, 0xC1, 0x17, 0xB6, 0xD0, 0xD1, 0xB6,    //低音1234567
              0x21, 0xE1, 0x8C, 0xD8, 0x68, 0xE9, 0x5B, 0x8F, //1,2,3,4,5,6,7,i
              0xEE, 0x44, 0x6B, 0xB4, 0xF4, 0x2D,             //高音 234567
              0x47, 0x77, 0xA2, 0xB6, 0xDA, 0xFA, 0x16};   //超高音 1234567
//----------------------------------------------------------------------------------------------
// 要想演奏不同的乐曲, 只需要修改这个数据表
code unsigned char music[][500] ={ 
// 送别数据表
           {5,1,2, 3,1,3, 5,1,1, 1,2,3, 6,1,2, 1,2,2, 5,1,4, 5,1,2, 1,1,1, 2,1,1, 3,1,2, 2,1,1, 1,1,1, 2,1,4,
            5,1,2, 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 5,1,4, 5,1,2, 2,1,1, 3,1,1, 4,1,2, 7,0,1, 1,1,4, 
						6,1,2, 1,2,2, 1,2,4, 7,1,2, 6,1,1, 7,1,1, 1,2,4, 6,1,1, 7,1,1, 1,2,1, 6,1,1, 6,1,1, 5,1,1, 3,1,1, 
						1,1,1, 2,1,8, 5,1,2, 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 5,1,4, 5,1,2, 2,1,1, 3,1,1, 4,1,2,
						7,0,2, 1,1,4, 0,0,0}};
///////////////////////////////////////////////////////////////////////////////////////////////
//音乐播放接口            
void t1int() interrupt 3       //T1中断程序，控制发音的音调
    {
       TR1 = 0;                      //先关闭T1
       MusicPlayer = !MusicPlayer;           //输出方波, 发音          
       TH1 = timer0h;               //下次的中断时间, 这个时间, 控制音调高低
  	   TL1 = timer0l;
       TR1 = 1;                     //启动T1
    }
/////////////////////////////////////////////////////////////////////////////////////////////////
void delay_music(unsigned char t)    //延时子函数，控制发音的时间长度
     {
      	unsigned char t1;
        unsigned long t2;
       	for(t1 = 0; t1 < t; t1++)          //嵌套循环, 共延时t个半拍
        for(t2 = 0; t2 < 8000; t2++); //延时期间, 可进入T1中断去发音
       	TR1 = 0;                        //关闭T1, 停止发音
     }
////////////////////////////////////////////////////////////////////////////////////////////////

void song()                    //演奏一个音符
     {
       	TH1 = timer0h;               //控制音调
       	TL1 = timer0l;
       	TR1 = 1;                     //启动T1, 由T1输出方波去发音
       	delay_music(time);                 //控制时间长度
      }
///////////////////////////////////////////////////////////////////////
void Song(unsigned char j)  
       { 
					 unsigned char k, i;
					 i = 0;
           time = 1; 
            while(time) {
								k = music[j][i] + 7 * music[j][i + 1] - 1;
								timer0h = FREQH[k];      
								timer0l = FREQL[k];     
								time = music[j][i + 2];   
								i += 3;
								song(); 

							}
			 }
//////////////////////////////////////////////////////////////////////////////////
//以下接口根据自己需要扩展			 				 
void music_player(){

		Clear();
		Song(0);
		return;	
		

}