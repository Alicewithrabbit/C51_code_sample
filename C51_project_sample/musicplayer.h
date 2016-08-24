/*--------------------------------------------------------------------------
Made by Œ‚≥Á
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __MUSICPLAYER_H__
#define __MUSICPLAYER_H__
sbit MusicPlayer=P3^5;
extern code unsigned char FREQH[];
extern code unsigned char FREQL[];
extern code unsigned char music[][500];
void music_player();
#endif