/* 
 ********************************************************************************************************* 


 ********************************************************************************************************* 
 * File : subprogram.c 
 * By : Minglie 
 * Date : 
 ********************************************************************************************************* 
 */ 
#define OS_GLOBALS 
#include "include.h" //Port-defined header file 
#include "meau.h"

void mcu_init() 
{ 
	fsys_int(); 
	systick_init(); 
	usart_init(); 
	gpio_init() ;
	NVIC_Configuration(); 
	variable_init();	
} 
void variable_init() 
{ 
	com_step=0; 
	period = 0; 
	duty = 0; 
	CollectFlag = 1; 
	bt.one.usart_rx_f=0;
} 

/********************************************************** 
 ** ������: gpio_init 
 ** ��������: ����IO 
 ** �������: �� 
 ** �������: �� 
 ***********************************************************/ 
void gpio_init(void) 
{	
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
} 
/*********************************************END OF FILE**********************/ 



void systick_init() 
{ 
	SysTick->LOAD = (SystemCoreClock/1000 & SysTick_LOAD_RELOAD_Msk) - 1; /* set reload register */ 
	SysTick->VAL = 0; /* Load the SysTick Counter Value */ 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
} 


void systick_counter() //provide a 1ms and 5ms clock signal for the system 
{ 
	static u8 i=0; 
	if(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) 
	{ 
		bt.one.ms1_s=1; //1ms flag set 1 
		system_counter++; 
		if(system_counter>=5) 
		{ 
			bt.one.ms5_s=1; //5ms flag set 1 
			system_counter=0; //clear the system_counter when it overflow 
			i++; 
			if(i>main_count){bt.one.ms500_s=1;i=0;} 
		} 
		SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk; 
	} 
} 



void systick_delay_us(unsigned int ticks) 
{ 
	//while(SysTick->VAL); 
	SysTick->LOAD = (SystemCoreClock/1000000*ticks & SysTick_LOAD_RELOAD_Msk) - 1; /* set reload register */ 
	SysTick->VAL = 0; /* Load the SysTick Counter Value */	
	SysTick->CTRL &= ~SysTick_CTRL_COUNTFLAG_Msk; 
	while(1) 
	{ 
		if( SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) 
		{ 
			break; 
		}	
	}	
} 


void fsys_int() 
{ 
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;	
	RCC_DeInit(); 
	RCC_HSEConfig(RCC_HSE_ON); 
	if(RCC_WaitForHSEStartUp() == SUCCESS) 
	{ 
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
		RCC_PCLK2Config(RCC_HCLK_Div1); 
		RCC_PCLK1Config(RCC_HCLK_Div2); 
		if ((RCC->CR & RCC_CR_HSERDY) != RESET) 
		{ 
			HSEStatus = (uint32_t)0x01; 
		} 
		else 
		{ 
			HSEStatus = (uint32_t)0x00; 
		} 

		if (HSEStatus == (uint32_t)0x01) 
		{ 
			/* Enable Prefetch Buffer */ 
			FLASH->ACR |= FLASH_ACR_PRFTBE; 

			/* Flash 2 wait state */ 
			FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY); 
			FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2; 
		} 
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); 
		RCC_PLLCmd(ENABLE);// 
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); 
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
		while(RCC_GetSYSCLKSource() != 0x08); 
	} 

} 





/** 
 * @brief USART GPIO ����,����ģʽ����115200 8-N-1 
 * @param �� 
 * @retval �� 
 */ 
void usart_init(void) 
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	USART_InitTypeDef USART_InitStructure; 

	/* config USART clock */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4 , ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 , ENABLE); 

	/* USART1 GPIO config to USATR1 */ 
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	/* Configure USART1 Rx (PA.10) as input floating */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 


	/* USART2 GPIO config to USATR2 */ 
	/* Configure USART2 Tx (PA.02) as alternate function push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	/* Configure USART1 Rx (PA.03) as input floating */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 



	/* USART2 GPIO config to USATR3 */ 
	/* Configure USART3 Tx (PD.8) as alternate function push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	/* Configure USART1 Rx (PD.9) as input floating */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOD, &GPIO_InitStructure); 


	/* USART1 mode config */ 
	USART_InitStructure.USART_BaudRate = 115200; 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1; 
	USART_InitStructure.USART_Parity = USART_Parity_No ; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_Init(USART1, &USART_InitStructure); 
	USART_Init(USART2, &USART_InitStructure); 
	USART_Init(USART3, &USART_InitStructure); 

	/* ʹ�ܴ���1�����ж� */ 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 

	USART_Cmd(USART1, ENABLE); 
	USART_Cmd(USART2, ENABLE); 
	USART_Cmd(USART3, ENABLE); 
} 


void uart_send_char(USART_TypeDef* USARTx,uint16_t Data) 
{ 
	USART_SendData(USARTx, Data); 
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); 
} 


void LEDXToggle(uint8_t ledx) 
{ 
	if(ledx==1) 
	{ 
		LED1_GPIO_PORT->ODR^=LED1_GPIO_PIN; 
	} 
	else if(ledx==2) 
	{ 
		LED2_GPIO_PORT->ODR^=LED2_GPIO_PIN; 
	} 
	else 
	{ 
		LED3_GPIO_PORT->ODR^=LED3_GPIO_PIN; 
	} 
} 

void adc1_init(void) 
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	ADC_InitTypeDef ADC_InitStructure; 
	/* Enable DMA clock */ 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
	/* Enable ADC1 and GPIOC clock */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE); 
	/* Configure PC.01 as analog input */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	// PC1,����ʱ������������ 

	/* ADC1 configuration */	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ADCģʽ 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//��ֹ������ת��ģʽ 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��ʹ���ⲿ����ת�� 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�ɼ������Ҷ��� 
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//Ҫת����ͨ����Ŀ1 
	ADC_Init(ADC1, &ADC_InitStructure); 

	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9MHz*/ 
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	/*����ADC1��ͨ��11Ϊ55.	5���������ڣ�����Ϊ1 */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5); 

	/* Enable ADC1 DMA */ 
	ADC_DMACmd(ADC1, DISABLE); 

	/* Enable ADC1 */ 
	ADC_Cmd(ADC1, ENABLE); 

	/*��λУ׼�Ĵ��� */ 
	ADC_ResetCalibration(ADC1); 
	/*�ȴ�У׼�Ĵ�����λ��� */ 
	while(ADC_GetResetCalibrationStatus(ADC1)); 

	/* ADCУ׼ */ 
	ADC_StartCalibration(ADC1); 
	/* �ȴ�У׼���*/ 
	while(ADC_GetCalibrationStatus(ADC1)); 

	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
} 



//------------------AD test----------------------------------------------------- 
void ad_convert(unsigned char addres) //AD test shoud be on average 
{ 
	adres=0; 
	//ADC1->DR=0; 
	ADC_Cmd(ADC1, DISABLE); 
	if(addres==0) 
	{ 
		ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5); 
	} 
	else if(addres==1) 
	{ 
		ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);	
	}	
	/* Enable ADC1 */ 
	ADC_Cmd(ADC1, ENABLE);	
	/*��λУ׼�Ĵ��� */ 
	ADC_ResetCalibration(ADC1); 
	/*�ȴ�У׼�Ĵ�����λ��� */ 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	/* ADCУ׼ */ 
	ADC_StartCalibration(ADC1); 
	/* �ȴ�У׼���*/ 
	while(ADC_GetCalibrationStatus(ADC1)); 

	/* ����û�в����ⲿ����������ʹ���������ADCת�� */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 
	ADC1->SR &=~ADC_FLAG_EOC; 
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==0);	
	adres=ADC_GetConversionValue(ADC1);	
}  


void tm3_init() // tim3�����·pwm//period=10ms--6000r/min 
{ 
	//TM3_GPIO_INIT 
	GPIO_InitTypeDef GPIO_InitStructure; 

	//TIM3_Mode_INIT 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_OCInitTypeDef TIM_OCInitStructure; 


	/* PWM�źŵ�ƽ����ֵ */ 
	u16 CCR1_Val = 2000; 
	u16 CCR2_Val = 375; 
	u16 CCR3_Val = 2000; 
	u16 CCR4_Val = 125; 
	/* ����TIM3CLK Ϊ 72MHZ */ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	/* GPIOA and GPIOB clock enable */ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); 
	/*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	// ����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	/*GPIOB Configuration: TIM3 channel 3 and 4 as alternate function push-pull */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* ----------------------------------------------------------------------- 
	   TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR+1)* 100% = 50% 
	   TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR+1)* 100% = 37.5% 
	   TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR+1)* 100% = 25% 
	   TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR+1)* 100% = 12.5% 
	   ----------------------------------------------------------------------- */ 

	/* Time base configuration */	
	TIM_TimeBaseStructure.TIM_Period =10000; //period=1ms--6000r/min 
	TIM_TimeBaseStructure.TIM_Prescaler = 72;	//fT=1MHZ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���) 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 

	/* PWM1 Mode configuration: Channel1 */ 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//����ΪPWMģʽ1 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	//��������ֵ�������������������ֵʱ����ƽ�������� 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ 

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��1 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 

	/* PWM1 Mode configuration: Channel2 */ 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��2 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 

	/* PWM1 Mode configuration: Channel3 */ 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��3 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 

	/* PWM1 Mode configuration: Channel4 */ 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��4 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM3, ENABLE);	// ʹ��TIM3���ؼĴ���ARR 
	/* TIM3 enable counter */ 
	TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��3	
} 


/*�������ƣTIM4_PWMINPUT_INIT(u16 arr,u16 psc) 
  ���� PWM�����ʼ��*/ 

void tm4_pwm_input_init(u16 arr,u16 psc) 
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	NVIC_InitTypeDef NVIC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //open gpioB clock 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure); 


	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 


 
} 



void	ad1_vol_measure(void)	//ad test battery voltage 
{ 
	ad_convert(0); 
	voltage=adres%256; 
} 

void	ad1_cur_measure(void)	//ad test current current 
{ 
	ad_convert(1); 
	current=adres%256;	
} 
void tm4_speed_measure(void) 
{ 

	speed=25; 
}	
void systick_break_time_messure() 
{ 
	break_time=48; 
} 

void systick_1000ms() 
{ 
	counter_1ms++; 
	if(counter_1ms>1000) 
	{ 
		counter_1ms=0; 
		//CPL_B(9); 
	} 
}










//#define UART_KEY
//��ȡ����ֵ����Ӳ���������
void key_scan()
{
		if(bt.one.usart_rx_f)
		{
			   bt.one.usart_rx_f=0;
         switch(rx_buf)
         {
              case '0':{  keyval=0;break;}
              case '1':{  keyval=1;break;}
					    case '2':{  keyval=2;break;}
              case '3':{  keyval=3;break;}
					    case '4':{  keyval=4;break;}
              case '5':{  keyval=5;break;}
					    case '6':{  keyval=6;break;}
              case '7':{  keyval=7;break;}				    
              case '8':{  keyval=8;break;}
              case '9':{  keyval=9;break;}
              case 'A':{  keyval=10;break;}
              case 'B':{  keyval=11;break;}
              case 'C':{  keyval=12;break;}				    
              case 'D':{  keyval=13;break;}
              case 'E':{  keyval=14;break;}
              case 'F':{  keyval=15;break;}
         }
			   menu_flag.one.is_KeyPressed=1;
    }
		else  keyval=16;			
}


void usart2_printf(const u8 *pString)
{

	USART_ClearFlag(USART2,USART_FLAG_TC);
	 while(*pString!='\0')
	{
			USART_SendData(USART2,*pString);
		  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
			pString++;
	}
	
}












