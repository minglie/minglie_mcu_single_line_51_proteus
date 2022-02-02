/* 
 ********************************************************************************************************* 
 8414-000000 TKE 
 ********************************************************************************************************* 
 * File : meau.c 
 * By : Minglie 
 * Date : 2016.5.5 
 ********************************************************************************************************* 
 */ 
#include "include.h" 
#include "stdio.h"

const u8  str_set_err[]="\033[7mhello,world\n";//�������ô���ĶԻ���
const u8  str_arrow[]="->";
const u8  str_back_root_meau[]="0.���ظ��˵�";
const u8  str_item_select[]="1.Ʒ��ѡ��";
const u8  str_back_item_select[]="0.����Ʒ��ѡ��";
const u8  str_item1[]="1.8414-801501";
const u8  str_item2[]="2.8414-801502";			
const u8  str_item3[]="3.8414-801503";	

const u8  str_manuals_set[]="2.�ֶ�����";
                const u8  str_back_manuals_set[]="0.�����ֶ�����";
								const u8         str_Wcur[]="1.�Ժĵ�ֵ(uA)��:";	
								const u8          str_Chg[]="2.���䱣����ѹֵ(mV):"; 
								const u8          str_Imp[]="3.����ֵ(mR)";	
								const u8         str_Ocur[]="4.����������ֵ(A)��";     
								const u8 				  str_Dis[]="5.���ű�����ѹֵ(mV)��";	
							  const u8      str_OCUR_DT[]="6.��������ʱֵ(mS)��";
							  const u8       str_CHG_DT[]="7.�������ʱֵ(mS)��";	 							
							  const u8  		 str_DIS_DT[]="8.���ŵ���ʱֵ(mS):"; 
								const u8  	   str_RS[]="9.��������ֵ(KR)"; 
				        const u8 		 	 str_RT[]="10.ʶ�����ֵ(KR)��";	
								const u8      str_ROM[]="11.���룺";	 
								const u8  	str_CHG_R[]="12.���䱣���ָ���ѹֵ(V):"; 
								const u8    str_DHG_R[]="13.���ű����ָ���ѹֵ(V)"; 								
								
const u8  str_mode_select[]="3.ģʽѡ��";								
							  const u8  str_back_mode_select[]="0.����ģʽѡ��";
								const u8         str_auto_mode[]="1.�Զ�ģʽ��:";	
								const u8          str_detail[]="2.��ϸģʽ(mV):"; 	
const u8  str_star[]="4.��ʼ����";
                  const u8    str_back_Star[]="0.���ؿ�ʼ����";
//								const u8         str_Wcur[]="1.�Ժĵ�ֵ(uA)��:";	
//								const u8          str_Chg[]="2.���䱣����ѹֵ(mV):"; 
//								const u8          str_Imp[]="3.����ֵ(mR)";	
//								const u8         str_Ocur[]="4.����������ֵ(A)��";     
//								const u8 				  str_Dis[]="5.���ű�����ѹֵ(mV)��";	
//							  const u8      str_OCUR_DT[]="6.��������ʱֵ(mS)��";
//							  const u8       str_CHG_DT[]="7.�������ʱֵ(mS)��";	 							
//							  const u8  		 str_DIS_DT[]="8.���ŵ���ʱֵ(mS):"; 
//								const u8  	   str_RS[]="9.��������ֵ(KR)"; 
//				        const u8 		 	 str_RT[]="10.ʶ�����ֵ(KR)��";	
//								const u8  str_ROM[]="11.���룺";	 
//								const u8  	str_CHG_R[]="12.���䱣���ָ���ѹֵ(V):"; 
//								const u8  str_DHG_R[]="13.���ű����ָ���ѹֵ(V)"; 	




//5��1�����˵�
const menu_TypeDef menu_root_L0[5];
//4+14+3+14�������˵�
const menu_TypeDef menu_item_select_L0_1[4];//Ʒ��ѡ��
const menu_TypeDef menu_manuals_set_L0_2[14];//�ֶ�����
const menu_TypeDef menu_mode_select_L0_3[3];//ģʽѡ��
const menu_TypeDef menu_star_L0_4[14];      //��ʼ����



/***************************************�ṹ����***********************************************/
/**************************************һ�����˵�**********************************************/
//����//���ⳤ�� // ����//����Enter�Ĳ˵��¼����� //�Ӳ˵� // ���˵�

 const menu_TypeDef menu_root_L0[5]=
{  
   {5,sizeof(str_back_root_meau), str_back_root_meau, NULL,   NULL  ,                                 (menu_TypeDef *)menu_root_L0}, 	//0.���ظ��˵�   
   {5,sizeof(str_item_select),    str_item_select,    NULL,  (menu_TypeDef *)menu_item_select_L0_1,    NULL},	  //1.Ʒ��ѡ��
   {5,sizeof(str_manuals_set),    str_manuals_set,    NULL,  (menu_TypeDef *)menu_manuals_set_L0_2,    NULL},	  //2.�ֶ�����
   {5,sizeof(str_mode_select),    str_mode_select,    NULL,  (menu_TypeDef *)menu_mode_select_L0_3,    NULL},	  //2.ģʽѡ��
   {5,sizeof(str_star),           str_star,       	  NULL,  (menu_TypeDef *) menu_star_L0_4,          NULL}	  //3.��ʼ����
};

//�����˵�
const menu_TypeDef menu_item_select_L0_1[4]=
{  
   {4,sizeof(str_back_item_select),   str_back_item_select,    NULL,                  NULL,               (menu_TypeDef *)menu_root_L0}, 	//����Ʒ��ѡ��
   {4,sizeof(str_item1),              str_item1,               NULL,                  NULL,                NULL},	  //8414_801501
   {4,sizeof(str_item2),              str_item2,               NULL,                  NULL,         	     NULL},	  //8414_801502
   {4,sizeof(str_item3),              str_item3,               NULL,                  NULL,                NULL}	  //8414_801503
};

const menu_TypeDef menu_manuals_set_L0_2[14]=
{  
   {14,sizeof(str_back_manuals_set),   str_back_manuals_set,        NULL,                      NULL,      (menu_TypeDef *)menu_root_L0}, //0.�����ֶ�����
   {14,sizeof(str_Wcur),                           str_Wcur,        MenuFun_parameter_set,     NULL,       NULL},	//1.�Ժĵ�ֵ
   {14,sizeof(str_Chg),                             str_Chg,        MenuFun_parameter_set,     NULL,       NULL},	//2.���䱣����ѹֵ 
   {14,sizeof(str_Imp),                             str_Imp,        MenuFun_parameter_set,     NULL,       NULL},	//3.����ֵ(mR) 
   {14,sizeof(str_Ocur),                           str_Ocur,        MenuFun_parameter_set,     NULL,       NULL},	//4.����������ֵ
   {14,sizeof(str_Dis),                             str_Dis,        MenuFun_parameter_set,     NULL,       NULL},	//5.���ű�����ѹֵ 
   {14,sizeof(str_OCUR_DT),                     str_OCUR_DT,        MenuFun_parameter_set,     NULL,       NULL},	//6.��������ʱֵ 
   {14,sizeof(str_CHG_DT),                       str_CHG_DT,        MenuFun_parameter_set,     NULL,       NULL},	//7.�������ʱֵ
   {14,sizeof(str_DIS_DT),                       str_DIS_DT,        MenuFun_parameter_set,     NULL,       NULL}, //8.���ŵ���ʱֵ	 
   {14,sizeof(str_RS),                               str_RS,        MenuFun_parameter_set,     NULL,       NULL},	//9.��������ֵ 
   {14,sizeof(str_RT),                               str_RT,        MenuFun_parameter_set,     NULL,       NULL},	//10.ʶ�����ֵ 
   {14,sizeof(str_ROM),                             str_ROM,        MenuFun_parameter_set,     NULL,       NULL},	//11.����   
   {14,sizeof(str_CHG_R),                         str_CHG_R,        MenuFun_parameter_set,     NULL,       NULL},	//12.���䱣���ָ���ѹֵ
   {14,sizeof(str_DHG_R),                         str_DHG_R,        MenuFun_parameter_set,     NULL,       NULL}	//13.���ű����ָ���ѹֵ 
};

const menu_TypeDef menu_mode_select_L0_3[3]=
{  
   {3,sizeof (str_back_mode_select),  str_back_mode_select,    NULL,             NULL,                      (menu_TypeDef *)menu_root_L0},
   {3,sizeof (str_auto_mode),         str_auto_mode,           NULL,             NULL,         	             NULL},	 
   {3,sizeof (str_detail),            str_detail,              NULL,             NULL,                       NULL}	  
};



const menu_TypeDef menu_star_L0_4[14]=
{  
   {14,sizeof(str_back_Star),  str_back_Star,    NULL,         NULL,           (menu_TypeDef *)menu_root_L0}, //0.���ؿ�ʼ����
   {14,sizeof(str_Wcur),       str_Wcur,         NULL,         NULL,           NULL},	//1.�Ժĵ�ֵ
   {14,sizeof(str_Chg),        str_Chg,          NULL,         NULL,         	 NULL},	//2.���䱣����ѹֵ 
   {14,sizeof(str_Imp),        str_Imp,          NULL,         NULL,           NULL},	//3.����ֵ(mR) 
   {14,sizeof(str_Ocur),       str_Ocur,         NULL,         NULL,           NULL},	//4.����������ֵ
   {14,sizeof(str_Dis),        str_Dis,          NULL,         NULL,           NULL},	//5.���ű�����ѹֵ 
   {14,sizeof(str_OCUR_DT),    str_OCUR_DT,      NULL,         NULL,           NULL},	//6.��������ʱֵ 
   {14,sizeof(str_CHG_DT),     str_CHG_DT,       NULL,         NULL,           NULL},	//7.�������ʱֵ
   {14,sizeof(str_DIS_DT),     str_DIS_DT,       NULL,         NULL,           NULL}, //8.���ŵ���ʱֵ	 
   {14,sizeof(str_RS),         str_RS,           NULL,         NULL,           NULL},	//9.��������ֵ 
   {14,sizeof(str_RT),         str_RT,           NULL,         NULL,           NULL},	//10.ʶ�����ֵ 
   {14,sizeof(str_ROM),        str_ROM,          NULL,         NULL,           NULL},	//11.����   
   {14,sizeof(str_CHG_R),      str_CHG_R,        NULL,         NULL,           NULL},	//12.���䱣���ָ���ѹֵ
   {14,sizeof(str_DHG_R),      str_DHG_R,        NULL,         NULL,          NULL}	//13.���ű����ָ���ѹֵ 
};



/***********************desiccant***************��ҳ**********************************************/
void  showhomepage()
{
  
	
	
	
	
}

/*******************************************************************************
�������ƣ�Menu_Display()
�������ܣ���ʾ�˵�
��ڲ���: ��ʾλ�ã�����ʾ����
���ڲ���: void
�������ڲ�
��ע: �ú�����Ӳ���ӿں�����ʵ�ֲ˵�����ʾ������Ӳ��ֻ��ı���������
*******************************************************************************/
//#define _UART_DIS
void menu_display(u8 x ,u8 y, const u8 *pString ,u8 num)
{
   lcd_display(x ,y,pString,num);

}


/*******************************************************************************
�������ƣ�ClrScreen()
�������ܣ������Ļ
��ڲ���: void
���ڲ���: void
�������ڲ�
��ע: �ú�����Ӳ���ӿں�����ʵ���������ܣ�����Ӳ��ֻ��ı���������
*******************************************************************************/
void menu_clrScreen()
{
   lcd_clrScreen();//����
}

/*******************************************************************************
�������ƣ�Menu_Refresh()
�������ܣ�ˢ�²˵�
��ڲ���: psMenuItem(ѡ�еĲ˵���)��MenuStart���ò˵�����ʾ��ʼ�˵��
			MenuSelect(��ѡ�еĲ˵������������ʾʱ���⴦��)
���ڲ���: ����а��������±�־(Menu_SysFlag.Bits.is_KeyPressed)
�������ڲ�
��ע:
*******************************************************************************/
void menu_refresh(const menu_TypeDef *psMenuItem, u8 menuStart, u8 menuSelect)
{
  u8 n, disPoint,disPoint1, maxItems; 
	maxItems = (*psMenuItem).menuCount;//�������ͬ���˵� 
	disPoint = menuStart;
	//
	menu_flag.one.is_KeyPressed = 0;//���һ�ΰ�����־���˵����仯

	//�ȵ�����������
	menu_clrScreen();
	//����Һ����ʾ����
	for (n=0;disPoint<maxItems && n<MENU_MAX_PER_SCN; n++)  
  {
		 if (disPoint==menuSelect) menu_display(0, n, str_arrow,2);
		 else menu_display(0, n, "  ",2);
		 menu_display( 3, n, (psMenuItem+disPoint)->menuTittle,(psMenuItem+disPoint)->size);
		 if(psMenuItem==menu_manuals_set_L0_2 && n>0)//��������ò˵�����ô�ں�������õĲ���
		 {
         if(menu_parameter_new[n].enable)	 
			   {
					   menu_display(25 ,n,"��[��]---",20); 
				 }
				 else 
			   {
					   menu_display(25 ,n,"��[��]---",20); 
				 }
				 
				// sprintf(ming_string, "[%4d]---[%4d]", menu_parameter_new[n].min_set, menu_parameter_new[n].max_set);	
	      // menu_display(35,n,ming_string,sizeof(ming_string)); 		      			         
			
				 min_qian= (menu_parameter_new[n].min_set/1000)%10;
				 min_bai= (menu_parameter_new[n].min_set/100)%10;
				 min_shi= (menu_parameter_new[n].min_set/10)%10;
				 min_ge= (menu_parameter_new[n].min_set/1)%10;				 
				 lcd_goto(34,n);			  
				 lcd_send_char('[');	
         lcd_send_char(min_qian+0x30);
         lcd_send_char(min_bai+0x30);
         lcd_send_char(min_shi+0x30);
				 lcd_send_char(min_ge+0x30);
				 lcd_send_char(']');	
				 
				 lcd_send_char('-');	
				 lcd_send_char('-');	
				 lcd_send_char('-');					 
         max_qian= (menu_parameter_new[n].max_set/1000)%10;
				 max_bai= (menu_parameter_new[n].max_set/100)%10;
				 max_shi= (menu_parameter_new[n].max_set/10)%10;
				 max_ge= (menu_parameter_new[n].max_set/1)%10;				 
				 lcd_goto(43,n);			  
				 lcd_send_char('[');	
         lcd_send_char(max_qian+0x30);
         lcd_send_char(max_bai+0x30);
         lcd_send_char(max_shi+0x30);
				 lcd_send_char(max_ge+0x30);
         lcd_send_char(']');	

//				 if( menu_flag.one.is_InConfig)
//				 {
//		//			   lcd_goto(36,menuSelect);				 				 
//         }		 
		
//��/��   [25]				 
//min_set:[35,36,37,38]
//max_set:[43,44,45,46]				 
				 
     }
		 disPoint++;
		
	}
	
	//ˢ��������Ƶ����ô�
	 if(menu_flag.one.is_InConfig)
	 {

        switch(set_position_cur)
        {
					  case 0:{ 	lcd_goto(28,menu_index_saved);       break;}          
            case 1:{ 	lcd_goto(35,menu_index_saved);		   break;}
						case 2:{  lcd_goto(36,menu_index_saved);;      break;}
						case 3:{	lcd_goto(37,menu_index_saved);       break;}
						case 4:{	lcd_goto(38,menu_index_saved);       break;}
					
          	case 5:{	lcd_goto(44,menu_index_saved);       break;}
						case 6:{	lcd_goto(45,menu_index_saved);       break;}
						case 7:{	lcd_goto(46,menu_index_saved);       break;}
						case 8:{	lcd_goto(47,menu_index_saved);       break;}
					
       } 
    }	
	return;
	    
}
/******************************************************************************
��������:Menu_Index()
��������:�˵���������
��ڲ�����psMenuItem(ָ�������Ĳ˵���),MenuDefault(Ĭ�ϵ���ʼ������)
���ڲ�����psMenuSlect���������Ĳ˵��㣬MenuIndex���������Ĳ˵���
�������ڲ�
��ע����Menu_Main()�������ã�ʵ�ֲ˵�������		 
	�ú������㣺������������ջ������ʹ��ָ�붨�壬��
			ʵ����һ���˵��������õı��棬ʹ�÷��ز���ʱ����ֱ�ӷ��ص�
			�ϼ�ѡ�в˵���	
******************************************************************************/
u8 menu_Index(menu_TypeDef *psMenuItem, u8 menuDefault)
{
	   unsigned char menuIndex, keyTemp, counter;
		//�жϰ������ҵ����˵�ָ�� 
	  counter=(*psMenuItem).menuCount;
	  menuIndex=menuDefault;
		keyTemp = keyval; 
	  
	 
	
	  switch (keyTemp) 
	  {
				case 0:{ 
					
				          usart2_printf("0");  break;
									if(menu_flag.one.is_InConfig)//���������ģʽ
									{
										    if(keyval==1)             ;	

									}  

               }
				case 1:{ usart2_printf("1");   break;}
				case 2:{ usart2_printf("2");   break;}
				case 3:{usart2_printf("3"); break;}
				case 4:{usart2_printf("4"); break;}
				case 5:{usart2_printf("5"); break;}
				case 6:{usart2_printf("6"); break;}
				case 7:{usart2_printf("7"); break;}
				case 8:{usart2_printf("8"); break;}
				case 9:{usart2_printf("9"); break;}
				case KEY_UP:  
				{     
					 usart2_printf("up");  
					//�ϼ�ѡ��˵�		
              if(menu_flag.one.is_InConfig==0)//���ڲ�������ģʽ
					    {
									if (menuIndex == 0) menuIndex =0;
									else menuIndex --; 
							}
				      break; 
				}
				case KEY_DOWN: 
		  	{
					 //�¼�ѡ��˵�
					
					 if(menu_flag.one.is_InConfig==0)//���ڲ�������ģʽ
					 {	
						   if (menuIndex == (counter-1)) menuIndex = counter-1;
						   else menuIndex ++; 
           }						 
					// sprintf(ming_string, "An approximation of Pi is %d\n",3);	

          // sprintf(ming_string, "%d", 123); 					
				//	 ming_string="qwertyuiop";
				//	 usart2_printf(ming_string);  
					 usart2_printf("down");  
					
				   break; 
				}
				case KEY_LEFT: 
				{

           usart2_printf("left"); 
           if(menu_flag.one.is_InConfig)
					 {   
						   if(set_position_cur>0)  set_position_cur--;	
						   else   set_position_cur=0;
					 }
					
							break;
		    }
				case KEY_RIGHT:
				{
             usart2_printf("right");  
					  
					 if(menu_flag.one.is_InConfig)
					 {   
						  if(set_position_cur<8)  set_position_cur++;	
						  else   set_position_cur=8;
					 }

              break;
        }
				case KEY_ESC:	
			  {

              usart2_printf("esc");  

							break;
				 }
				case KEY_ENTER:							
				{
            
             usart2_printf("enter");  
					//�ж�psMenuItem[MenuIndex]���ܣ�һ���˵�ֻ������һ�ֹ���
				//�ò˵������Ӳ˵��������Ӳ˵�
				if (psMenuItem[menuIndex].menuChild != NULL) 
				{
						pMenuSelect = psMenuItem[menuIndex].menuChild;
						//pMenuSelect = (*(psMenuItem+MenuIndex)).MenuChild;
						menu_index_lastlvl[menu_level++] = menuIndex;
						//Console_SendByte(MenuIndex_LastLvl[MenuLevel-1]);
						menuIndex = 0;//
						break;
				}
				//�ò˵����ڹ��ܣ����ú�������
				if (psMenuItem[menuIndex].menuFun != NULL)
				{
						(*((psMenuItem+menuIndex)->menuFun))();
					//	(*(psMenuItem[MenuIndex].MenuFun))();
						break;	
				}
				//�ò˵����ڸ��˵����ص����˵�
				if (psMenuItem[menuIndex].menuFather != NULL) 
				{
						pMenuSelect =  psMenuItem[menuIndex].menuFather;
						menuIndex = menu_index_lastlvl[--menu_level];
						break;
				}
					  break;
			 }								
    }	
		
		 sprintf(ming_string, "menuIndex=%d;", menuIndex); 					
		 usart2_printf(ming_string);  		
	   return menuIndex; 	
		
}
/******************************************************************************
��������:Menu_Main()
��������:�˵�������
��ڲ�����void
���ڲ�����void
�������ⲿ
��ע���������������øú���ʵ�ֲ˵���ˢ��������
	indexһ��Ҫ����Ϊ��̬������ÿ�ε���ʹ����һ�ε�ֵ������ʵ�ַ�����ʽ����
******************************************************************************/
void menu_main()
{
	
		u8 startIndex;
	  u8 index; ;//MenuIndexSaved��һ�����ͷŵ��ڴ浥Ԫ	
	  index=menu_index_saved;	
    if(menu_flag.one.is_KeyPressed)
    {
         menu_flag.one.is_KeyPressed=0;
         index = menu_Index(pMenuSelect,index);
//ʵ�ֹ����Ĺؼ� 
				if (index < MENU_MAX_PER_SCN) startIndex = 0;
				else startIndex = index - MENU_MAX_PER_SCN + 1;
				//ֻ��is_InConfigΪ1ʱ��ˢ�²˵��� ��ֹ���������Ļ����Ļ��ˢ��
				if (menu_flag.one.is_InConfig||1) menu_refresh(pMenuSelect, startIndex, index);		     			
    }
    menu_index_saved = index;	
}


void menu_init()
{
	
	 printf("\033[0m");//��ԭ�ն�
	 pMenuSelect = (menu_TypeDef *)menu_root_L0;
	 menu_flag.ucFlag =0x00;
	 
	 menu_parameter_new[con_Wcur].enable=1;//1
	 menu_parameter_new[con_Chg].enable=1;//2
	 menu_parameter_new[con_Imp].enable=1;//
	 menu_parameter_new[con_Ocur].enable=1;//
	 menu_parameter_new[con_Dis].enable=1;//
	 menu_parameter_new[con_OCUR_DT].enable=1;//
	 menu_parameter_new[con_CHG_DT].enable=1;//
	 menu_parameter_new[con_DIS_DT].enable=1;//
	 menu_parameter_new[con_RS].enable=1;//
	 menu_parameter_new[con_RT].enable=1;//
	 menu_parameter_new[con_ROM].enable=1;//
	 menu_parameter_new[con_CHG_R].enable=1;//
	 menu_parameter_new[con_DHG_R].enable=1;//
	
	 menu_parameter_new[con_Wcur].min_set=1000;//1
	 menu_parameter_new[con_Chg].min_set=1000;//2	 
	 menu_parameter_new[con_Imp].min_set=1000;//
	 menu_parameter_new[con_Ocur].min_set=1000;//
	 menu_parameter_new[con_Dis].min_set=1000;//
	 menu_parameter_new[con_OCUR_DT].min_set=1000;//
	 menu_parameter_new[con_CHG_DT].min_set=1000;//
	 menu_parameter_new[con_DIS_DT].min_set=1000;//
	 menu_parameter_new[con_RS].min_set=1000;//
	 menu_parameter_new[con_RT].min_set=1000;//
	 menu_parameter_new[con_ROM].min_set=1000;//
	 menu_parameter_new[con_CHG_R].min_set=1000;//
	 menu_parameter_new[con_DHG_R].min_set=1000;//
	
	 menu_parameter_new[con_Wcur].max_set=5000;//1
	 menu_parameter_new[con_Chg].max_set=5000;//2	 
	 menu_parameter_new[con_Imp].max_set=5000;//
	 menu_parameter_new[con_Ocur].max_set=5000;//
	 menu_parameter_new[con_Dis].max_set=5000;//
	 menu_parameter_new[con_OCUR_DT].max_set=5000;//
	 menu_parameter_new[con_CHG_DT].max_set=5000;//
	 menu_parameter_new[con_DIS_DT].max_set=5000;//
	 menu_parameter_new[con_RS].max_set=5000;//
	 menu_parameter_new[con_RT].max_set=5000;//
	 menu_parameter_new[con_ROM].max_set=5000;//
	 menu_parameter_new[con_CHG_R].max_set=5000;//
	 menu_parameter_new[con_DHG_R].max_set=5000;//
	 
  pMenuSelect = (menu_TypeDef*)menu_root_L0;//�ѽṹ��������׵�ַ�����ָ��	
	menu_refresh(pMenuSelect, 0, 0);
		
}


void menu_test()
{

  	 pMenuSelect = (menu_TypeDef*)menu_star_L0_4;//�ѽṹ��������׵�ַ�����ָ��	
	   menu_refresh(pMenuSelect, 0, 5);
}


void MenuFun_parameter_set()
{ 
	  menu_flag.one.is_InConfig=!menu_flag.one.is_InConfig;  
	  set_position_cur=0;//�����ÿ���
}


void MenuFun_set_err() 
{
    u8 i=1;
   //�ȵ�����������
	  menu_clrScreen();
    menu_display(5, 10, str_set_err,sizeof(str_set_err));//��ʾ����˵�� 
    while(1) 
		{ 
			systick_counter(); 
			if(bt.one.ms5_s)	//routine of 5ms base time 
			{		 
				  key_scan();
				  if(menu_flag.one.is_KeyPressed)
					{
							 if(keyval==15)             //����ȷ�����˳�
							 {
								  menu_main();
									break;
							 }							 
          }			
				 	bt.one.ms5_s=0;	
			} 
		} 
}








