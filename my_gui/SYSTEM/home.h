#ifndef _home_H
#define _home_H
#include "sys.h"

//家居管理控制器
struct _my_home_dev
{
	void (*init)(u8);  		//初始化
//	u8 (*perused)(u8); 		//内存使用率
//	u8 *membase[SRAMBANK]; //内存池,管理SRAMBANK个区域的内存
//	u16 *memmap[SRAMBANK];  //内存状态表
//	u8 memrdy[SRAMBANK];   //内存管理是否就绪
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