/* 
 ********************************************************************************************************* 
 8414-000000 TKE 
 ********************************************************************************************************* 
 * File : lcd.c 
 * By : Minglie 
 * Date : 2016.5.5 
 ********************************************************************************************************* 
 */ 
#include "include.h" 
#include "stdio.h"


void lcd_clrScreen()
{
   printf("\033[2J");//清屏 
}

void lcd_printf(const u8 *pString ,u8 num)
{
   u8 num_temp;
	 num_temp=0;
	 num=num;
	USART_ClearFlag(USART1,USART_FLAG_TC);
	 while(*pString!='\0'&& num_temp<num)
	{
			USART_SendData(USART1,*pString);
		  while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			pString++;
		  num_temp++;
	}
}
void lcd_goto(u8 x ,u8 y)
{
		  y*=2;
	  printf( "\033[%d;%dH",y,x );  //光标跳转到/*x行y列*/  
}
void lcd_send_char(u8 a)
{
	 USART_SendData(USART1,a);
	 while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
}



void lcd_cursor_underline()//下划线
{
    printf( "\033[4m" );
}


void lcd_vt100_reset()//还原终端
{
    printf( "\033[0m" );
}

void lcd_cursor_control(u8 a)//光标是否显示
{
	 if(a==0)  printf( "\33[?25l" );//隐藏光标
   else      printf( "\33[?25h" );//显示光标
} 



void lcd_display(u8 x ,u8 y, const u8 *pString ,u8 num)
{
    if(num%2==1)num--;//输出汉字时不可以为奇数
	  y*=2;
	  printf( "\033[%d;%dH",y,x );  //光标跳转到/*x行y列*/  
	  lcd_printf(pString,num);
}


