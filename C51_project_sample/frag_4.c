#include<reg52.h>
#include<absacc.h>
#include"frag1.h"
#include"frag4.h"
#include"frag6.h"
#include"musicplayer.h"
#define PC XBYTE [0x7ffe]
code unsigned char KeyTable[]={   // ¼üÂë¶¨Òå
  0x03,0x07,0x0b,0x0f,
  0x02,0x06, 0x0a,0x0e,   
  0x01,0x05,0x09,0x0d,   
  0x00,0x04, 0x08, 0x0c	,
};
unsigned char key;
void Delay_Key(unsigned char k){
	unsigned char i,j;
	for(j=k;j>0;j--)  
	for (i=300;i>0;i--); 
}
unsigned char TestKey(){
	unsigned char IN;
	IN=PC&0x0f;
	return(~IN&0x0f);
}
unsigned char GetKey(){
	unsigned char Pos;
	unsigned char i;
	unsigned char k;
	i=4;
	Pos=0x80;    
	do{
		PC = ~Pos;
		Pos >>= 1;
		Delay_Key(50);
		k=~PC & 0x0f;
	} 
	while((--i != 0)&&(k == 0));
	if(k!=0){
	i*=4;
	if(k&2)i+=1;
	else if(k&4)i+=2;
	else if(k&8)i+=3;
	
	PC=0;
	do Delay_Key(10); 
	while (TestKey()); 

	return(KeyTable[i]);  
	} 
	else return(0xff);
}
