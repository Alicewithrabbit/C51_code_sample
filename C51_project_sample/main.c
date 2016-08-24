/*--------------------------------------------------------------------------
Made by Œ‚≥Á
All rights reserved.
--------------------------------------------------------------------------*/
#include<reg52.h>
#include<absacc.h>
#include"frag1.h"
#include"frag2.h"
#include"frag3.h"
#include"frag4.h"
#include"frag5.h"
#include"frag6.h"
#include"musicplayer.h"
void main(){
	ini_8255();
	system_ini();
	Init();
	Clear();
	start();
	while(1)
	{
		select();
		if(TestKey()){
			key=GetKey();
			switch(key){
				case 0x00:Clear();juzhenled();break;
				case 0x01:op(0);LCD_show_2(0);LED_Activity();break;
				case 0x02:op(0);music_player();break;
				case 0x03:op(0);game(0,0);break;
				case 0x04:op(0);LS();break;				
				default:break;
		}
		}
	
	}
}