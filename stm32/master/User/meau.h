/* 
 ********************************************************************************************************* 
 8414-000000 TKE 
 ********************************************************************************************************* 
 * File : meau.h
 * By : Minglie 
 * Date : 2016.5.5 
 ********************************************************************************************************* 
 */ 
 #ifndef __Meau_H 
#define  __Meau_H 

#include "Main_constant.h" //Port-defined header file 
#include "stm32f10x.h" 

#define MENU_MAX_PER_SCN	8
#define MENU_MAX_LEVEL		8
#define KEY_UP  	  10
#define KEY_DOWN  	11
#define KEY_LEFT  	12
#define KEY_RIGHT  	13
#define KEY_ESC  	  14
#define KEY_ENTER  	15


#define   con_back_manuals_set  0
#define   con_Wcur     1
#define   con_Chg      2
#define   con_Imp      3
#define   con_Ocur     4
#define   con_Dis	     5
#define   con_OCUR_DT  6
#define   con_CHG_DT	 7						
#define   con_DIS_DT   8
#define   con_RS       9
#define   con_RT      10
#define   con_ROM     11
#define   con_CHG_R   12
#define   con_DHG_R   13



/* �����������ݽṹ */
typedef  struct
{  
		u16  x;				// x�������
    u16  y;				// y�������
}poit_TypeDef;

typedef struct _menu_TypeDef
{
		u8 menuCount;			//��ǰ��ڵ���
		u8 size;             //��ǰ����ⳤ��
		const u8 *menuTittle;			//��ǰ�����
		//u8 MenuType;			//�˵����ͣ�0Ϊ��״��1Ϊ��״
		void (*menuFun)();	//��ǰ�ڵ㺯������
	  struct _menu_TypeDef *menuChild;	//�Ӳ˵�
	  struct _menu_TypeDef *menuFather; 	//���˵�
}menu_TypeDef;

typedef struct         //���ڱ��������õĲ���
{
	u8 enable;
	u16 min_set;
	u16 max_set;
}menu_parameter_TypeDef; //


typedef union _uFlag
{
	u8 ucFlag;
	struct
	{
		//u8 is_OnlyMenu 			: 1;
		u8 is_KeyPressed 		: 1;
		u8 is_InConfig			: 1;
		u8 is_ScreenChanged		: 1;
		u8 is_Reseved			: 5;
	}one;
}meau_Flag_TypeDef;


OS_EXT  menu_TypeDef*              pMenuSelect;//������һ���ṹ������ָ��
OS_EXT meau_Flag_TypeDef           menu_flag;//�˵��ṹ�ı�־λ
OS_EXT               u8            menu_index_saved ;//��ǰ��ѡ����
OS_EXT               u8            menu_index_lastlvl[MENU_MAX_LEVEL];//�˵���ջ
OS_EXT               u8            menu_level;//��ǰ�˵�����
OS_EXT  menu_parameter_TypeDef     menu_parameter_new[14];//�˵�����
OS_EXT  menu_parameter_TypeDef     menu_parameter_old[14];

OS_EXT  poit_TypeDef    cursor_new;
OS_EXT  poit_TypeDef    cursor_old;



OS_EXT  u8   set_position_cur;//��ǰ���õ�λ��
OS_EXT  u8   min_qian;//
OS_EXT  u8   min_bai;//
OS_EXT  u8   min_shi;//
OS_EXT  u8   min_ge;//

OS_EXT  u8   max_qian;
OS_EXT  u8   max_bai;
OS_EXT  u8   max_shi;
OS_EXT  u8   max_ge
;



//0����/��
//1��min:ǧλ   
//1��min:ǧλ
//1��min:ǧλ
//1��min:ǧλ











void showhomepage();
void menu_display(u8 x ,u8 y, const u8 *pString ,u8 num);
void menu_clrScreen();
void menu_refresh(const menu_TypeDef *psMenuItem, u8 menuStart, u8 menuSelect);
u8   menu_Index(menu_TypeDef *psMenuItem, u8 menuDefault);
void menu_main();
void menu_init();
void menu_test();

//�����˵��ڵ�Ĺ��Ӻ�����
void MenuFun_set_err();       //�������ô���
void MenuFun_parameter_set();    //��������

////////////////////////////////////////////////////////////





#endif 


