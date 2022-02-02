
/* 
********************************************************************************************************* 


********************************************************************************************************* 
* File : Function.h 
* By : Minglie 
* Date : 
********************************************************************************************************* 
*/ 

/* Function header file, all the function be used in program */ 
#include "stm32f10x.h" 




#ifndef __Function_H 
#define __Function_H 
//-------------------Main and Common Subprogram routine----- 
void mcu_init(); 
void variable_init(); 
void gpio_init(void); 
void systick_init(); 
void systick_counter(); 
void systick_delay_us(unsigned int ticks); 
void fsys_int(); 
void usart_init(void); 
void uart_send_char(USART_TypeDef* USARTx,uint16_t Data); 
void LEDXToggle(uint8_t ledx); 
void Delay_ms( uint16_t time_ms ); 
void adc1_init(void); 
void ad_convert(unsigned char addres); //AD test shoud be on average 
void tm3_init(); 
void tm4_pwm_input_init(u16 arr,u16 psc); 
void usart1_commucate(); 
void usart1_send_dat(); 
void usart1_get_dat(); 
void ad1_vol_measure(void);	//ad test battery voltage 
void ad1_cur_measure(void);	//ad test current current 
void tm4_speed_measure(void);	
void systick_break_time_messure(); 
void systick_1000ms(); 
void key_scan();
void usart2_printf(const u8 *pString);

#endif 



