/*--------------------------------------------------------------------------
Made by ���
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef  __FRAG2_H__
#define  __FRAG2_H__
#define PD1  61     // 122/2 �ֳ�����������(122x32)
extern unsigned char Column;
extern unsigned char Page_ ;  // ҳ��ַ�Ĵ��� D1,DO:ҳ��ַ
extern unsigned char Code_ ;  // �ַ�����Ĵ���
extern unsigned char Command; // ָ��Ĵ���
extern unsigned char LCDData; // ���ݼĴ���
extern unsigned char code Disp_Tab2[]; //lcd SHUZI ADDRESS
code unsigned char CCTAB[][32];
code unsigned char SZTAB[][16];
code unsigned char EETAB[][16];
extern unsigned char lcd_cache[4];		//LCD��ʾ����
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