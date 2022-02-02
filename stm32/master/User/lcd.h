/* 
 ********************************************************************************************************* 
 8414-000000 TKE 
 ********************************************************************************************************* 
 * File : lcd.h 
 * By : Minglie 
 * Date : 2016.5.5 
 ********************************************************************************************************* 
 */ 

 #ifndef __Lcd_H 
#define  __Lcd_H 

#include "Main_constant.h" //Port-defined header file 
#include "stm32f10x.h" 

void lcd_clrScreen();
void lcd_printf(const u8 *pString ,u8 num);
void lcd_display(u8 x ,u8 y, const u8 *pString ,u8 num);
void lcd_goto(u8 x ,u8 y);
void lcd_cursor_underline();//�»���
void lcd_vt100_reset();//��ԭ�ն�
void lcd_cursor_control(u8 a);//����Ƿ���ʾ
void lcd_send_char(u8 a);

#endif 