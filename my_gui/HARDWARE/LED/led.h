#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//LED�˿ڶ���
#define LED0 PFout(9)
#define LED1 PFout(10)
#define LED2 PFout(6)

#define FAN0 PFout(7)
#define FAN1 PAout(11)
#define FAN2 PBout(6)

#define AIR_C0 PBout(7)
#define AIR_C1 PAout(4)
#define COOKER PAout(5)

#define TV PAout(6)
#define OTHER1 PAout(7)
#define OTHER2 PAout(8)



void LED_Init(void);  //��ʼ��
#endif
