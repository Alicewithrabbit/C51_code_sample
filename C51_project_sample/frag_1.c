#include<reg52.h>
#include<absacc.h>
#include"frag1.h"
#include"frag3.h"
#include"musicplayer.h"
xdata unsigned char PA _at_ 0x7ffc ; // Port A
xdata unsigned char PB _at_ 0x7ffd ; // Port B
xdata unsigned char PC _at_ 0x7ffe ; // Port C
xdata unsigned char COM _at_ 0x7fff ; // ¿ØÖÆ×ÖµØÖ·
void ini_8255()
{
	COM=mode;
}