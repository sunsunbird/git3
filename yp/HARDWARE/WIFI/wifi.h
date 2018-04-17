#ifndef wifi_h
#define wifi_h	

#include "sys.h"	
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	 	 	 	 	 	 
#include "malloc.h"
#include "string.h"    
#include "usart3.h" 




//u8 client(void);	//WIFI AP+STA模式测试
void client_init(void);   //客户端初始化
void client_start(void);  //开启透传
void client_back(void);   //退出透传

#endif



