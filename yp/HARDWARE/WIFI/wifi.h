#ifndef wifi_h
#define wifi_h	

#include "sys.h"	
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	 	 	 	 	 	 
#include "malloc.h"
#include "string.h"    
#include "usart3.h" 




//u8 client(void);	//WIFI AP+STAģʽ����
void client_init(void);   //�ͻ��˳�ʼ��
void client_start(void);  //����͸��
void client_back(void);   //�˳�͸��

#endif



