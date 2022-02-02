
/* 
 ********************************************************************************************************* 


 ********************************************************************************************************* 
 * File : Main_constant.h 
 * By : Minglie 
 * Date : 
 ********************************************************************************************************* 
 */ 

/* Main_Constant, all the function be used in program */ 

#ifndef __Main_Constant_H 
#define __Main_Constant_H 
#include "stm32f10x.h" 

#define con_debug_en 2 


#define main_count 100 
#define con_major_cycle 150 //us 
#define con_key_d_delay 6 // 25ms 
#define con_key_u_delay 4 // 16ms 

//--------------------USART deifne--------------------------------------------- 
#define Key1	_pa3	
#define	Key2	_pa1	
#define	Key3	_pb2	
#define	Key4	_pb5	
#define	Key5	_pa5	

#define CPL_C(i) GPIOC->ODR ^=1<<i 
#define CPL_B(i) GPIOB->ODR ^=1<<i 


#define LED1_GPIO_RCC RCC_APB2Periph_GPIOC 
#define LED1_GPIO_PORT GPIOC 
#define LED1_GPIO_PIN GPIO_Pin_13 
#define LED1_ONOFF(x) GPIO_WriteBit(LED1_GPIO_PORT,LED1_GPIO_PIN,x); 

#define LED2_GPIO_RCC RCC_APB2Periph_GPIOG 
#define LED2_GPIO_PORT GPIOG 
#define LED2_GPIO_PIN GPIO_Pin_15 
#define LED2_ONOFF(x) GPIO_WriteBit(LED2_GPIO_PORT,LED2_GPIO_PIN,x); 

#define LED3_GPIO_RCC RCC_APB2Periph_GPIOB 
#define LED3_GPIO_PORT GPIOB 
#define LED3_GPIO_PIN GPIO_Pin_9 
#define LED3_ONOFF(x) GPIO_WriteBit(LED3_GPIO_PORT,LED3_GPIO_PIN,x); 






//#define CPL_C(i) (GPIO_WriteBit(GPIOC, 1<<i, (BitAction)((1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_3))))) 
//----------------------------global variable define--------------------------------------------------- 
#ifdef OS_GLOBALS 
#define OS_EXT 
#else 
#define OS_EXT extern 
#endif 


OS_EXT volatile unsigned int time,system_counter; 
OS_EXT volatile unsigned int counter_1ms; 


OS_EXT unsigned char voltage; 
OS_EXT unsigned char current; 
OS_EXT unsigned char power; 
OS_EXT unsigned char speed; 
OS_EXT unsigned char break_time; 
OS_EXT unsigned char com_step; 
OS_EXT unsigned char tx_buf;
OS_EXT unsigned char tx_buf_temp;
OS_EXT unsigned char rx_buf;
OS_EXT unsigned char rx_buf_temp;

OS_EXT u16 period; 
OS_EXT u16 duty ; 
OS_EXT u16 CollectFlag ;//互斥信号量 
OS_EXT u8  keyval;//按键返回值

OS_EXT char  ming_string[20];//按键返回值


OS_EXT volatile union union2 //announce a union save special bits 
{ struct struct2 
	{ 
		unsigned ms1_s : 1 ; //11ms timer-out flag 
		unsigned ms5_s : 1 ; 
		unsigned ms500_s : 1 ; 
		unsigned mode_f : 1 ; 
		unsigned debug_f : 1 ; 
		unsigned sg_f : 1 ; 
		unsigned usart_rx_f : 1 ; 
		
	}one; 
	unsigned char all; 
}bt; 

OS_EXT unsigned int adres; //announce a int as save the ad result 

OS_EXT union union2_adres //announce a union as save adres as address 
{ 
	unsigned int adre; 
	unsigned char adr[2]; 
}union_ad; 


OS_EXT uint8_t SendBuff[50]; 

#endif 






