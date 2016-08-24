#include<reg52.h>
#include"frag4.h"
#include"frag6.h"

unsigned char i;
unsigned char LEDMAP[8]	=	//一个暗，其余亮
{
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

unsigned char LEDMAP_1[8] =    //一个亮，其余暗
{
	0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f
};
void delay( unsigned int CNT )
{
	 unsigned char i;

	 while ( CNT-- != 0)
	 	for( i=100; i != 0; --i)
			;
}

void LS()
{	
	int ret=1;
	P2=0x5f;
	while(ret)
	{
		for(i=0; i<8; ++i)
		{
			if(TestKey()){
			ret=0;
			};
			P0 =  LEDMAP_1[i];
			delay(200);
		}
	}
}