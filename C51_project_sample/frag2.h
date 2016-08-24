/*--------------------------------------------------------------------------
Made by Îâ³ç
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef  __FRAG2_H__
#define  __FRAG2_H__
#define PD1  61     // 122/2 ·Ö³É×óÓÒÁ½°ëÆÁ(122x32)
extern unsigned char Column;
extern unsigned char Page_ ;  // Ò³µØÖ·¼Ä´æÆ÷ D1,DO:Ò³µØÖ·
extern unsigned char Code_ ;  // ×Ö·û´úÂë¼Ä´æÆ÷
extern unsigned char Command; // Ö¸Áî¼Ä´æÆ÷
extern unsigned char LCDData; // Êı¾İ¼Ä´æÆ÷
extern unsigned char code Disp_Tab2[]; //lcd SHUZI ADDRESS
code unsigned char CCTAB[][32];
code unsigned char SZTAB[][16];
code unsigned char EETAB[][16];
extern unsigned char lcd_cache[4];		//LCDÏÔÊ¾»º´æ
extern unsigned int cs;
extern unsigned int bs;//BLACKSTAR
extern unsigned int ws;//WHITESTAR
void Init();
void Clear();
void start();
void LCD_show_2(unsigned int a1);
void select();
void dyna(unsigned int cs);
void WriteCHN16x16();
void WriteEN8x16();	
void WriteSZ8x16();
void op(unsigned int p);
void game(unsigned int a,unsigned int b);
void lcd();
#endif