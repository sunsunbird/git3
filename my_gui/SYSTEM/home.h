#ifndef _home_H
#define _home_H
#include "sys.h"

//�Ҿӹ��������
struct _my_home_dev
{
	void (*init)(u8);  		//��ʼ��
//	u8 (*perused)(u8); 		//�ڴ�ʹ����
//	u8 *membase[SRAMBANK]; //�ڴ��,����SRAMBANK��������ڴ�
//	u16 *memmap[SRAMBANK];  //�ڴ�״̬��
//	u8 memrdy[SRAMBANK];   //�ڴ�����Ƿ����
};

//typedef struct
//{
//	
//	
//}family_struct;

typedef struct
{
	u8 led_state;
	u8 fan_state;
	u8 air_conditioner_state;
	u8 others;
	
}book_room_struct;

typedef struct
{
	u8 led_state;
	u8 fan_state;
	u8 air_conditioner_state;
	u8 others;
	
}living_room_struct;

typedef struct
{
	u8 led_state;
	u8 fan_state;
	u8 cooker_state;
	u8 others;
	
}kitchen_struct;





#endif