#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//LED端口定义
#define LED0 PFout(9)
#define LED1 PFout(10)
#define LED2 PFout(6)
#define LED3 PAout(8)

#define FAN0 PFout(7)
#define FAN1 PAout(11)

#define AIR_C2 PBout(6)
#define AIR_C0 PBout(7)
#define AIR_C1 PAout(4)

#define COOKER PAout(5)
#define TV PAout(6)
#define RANG_HOOD PAout(7)




void LED_Init(void);  //初始化
#endif
