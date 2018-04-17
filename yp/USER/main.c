#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "usart3.h"
#include "timer.h"
#include "oled.h"
#include "PID.h"
#include "motor.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "filter.h"
#include "string.h"
/************************************************
pitch   Χ��X����ת��Ҳ����������
yaw     Χ��Y��ѡװ��Ҳ���������
roll    Χ��Z����ת��Ҳ����������
D0-PC0  RES-PG15
D1-PC1  DC-PD3  CS-PD6
PWM-PA6,PA7,PB0,PB1
SCL-PB10  SDA-PB11
************************************************/
void Time6_Init(u16 arr,u16 psc);   
void Time7_Init(u16 arr,u16 psc); 
void judge ();
u8 wifi_config(u8 value);
u8 balance_car_init(void);
u8 data_maching(void);
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float pitch,roll,yaw; 		//ŷ����
short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
short gyrox,gyroy,gyroz;	//������ԭʼ����
float d1=0.1,d2=0.1;
extern int Balance_Pwm;
extern float bias,ggg;
float Encoder1_Number=0; //������1����ֵ
float DC_motor1_speed=0;
u16 len;
char sss[20]={1};
int main(void)
{	
	u8 s;u8 key;u8 flag=1;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	USART2_Init(115200);
	delay_init();	    	 //��ʱ������ʼ��	  
 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();			//��ʼ��OLED  
	KEY_Init();
	MPU_Init();	
	Encoder1_Init(); 
 	TIM3_PWM_Init(7199,0);	 //����Ƶ��PWMƵ��=72000000/900=80Khz
	Time6_Init(4999,72-1);//5ms����һ��  ��Ҫ�ĺ���
	OLED_ShowString(0,0,"mpu:on",12);
	OLED_ShowString(0,13,"P:",12);
	OLED_ShowString(64,13,"I:",12);
	OLED_ShowString(0,26,"D:",12);
	OLED_ShowString(0,39,"pitch:",12);
	OLED_ShowString(0,50,"gyrox:",12);
	OLED_ShowString(68,50,"PWM:",12);
	OLED_Refresh_Gram();		//������ʾ��OLED 
	while(wifi_config(flag));
	while(mpu_dmp_init())
 	{
		OLED_ShowString(22,0,"error",12);
		OLED_Refresh_Gram();		//������ʾ��OLED 
		delay_ms(200);
	}    
	
//	LocP_I_D_Set(sum,0,0);
   	while(1)
	{			
		OLED_ShowNum(24,39,pitch,3,12);
		OLED_ShowNum(30,50,gyroy,3,12);
		OLED_ShowNum(86,50,Balance_Pwm,3,12);
		OLED_Refresh_Gram();		//������ʾ��OLED 
//		printf("speed=%f\t",DC_motor1_speed);
		balance_car_init();
		while(1){
		data_maching();
		judge();
		delay_ms(1000);
			
		
		}
	}	 
 }

u8 wifi_config(u8 value)
{
	int key;
	key=KEY_Scan(0);
//	printf("wifi_config ok");
	if(key==KEY0_PRES){
		u3_printf("AT+RST\r\r\n");		
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);
		u3_printf("AT+CWMODE=1\r\r\n");	
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);
		u3_printf("AT+CWJAP=\"TP-LINK_135\",\"19791984\"\r\r\n");
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);		
		}	
		if(key==KEY1_PRES)	{	
		u3_printf("AT+CIPSTART=\"TCP\",\"192.168.1.60\",1234\r\r\n");
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);	
		u3_printf("AT+CIPMODE=1\r\r\n");
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);	
		u3_printf("AT+CIPSEND\r\r\n");				
		}
		if(key==KEY2_PRES)	{
			return 0;				
		}
		return 1;		
	  
}

u8 balance_car_init(void)
{
//		u8 key;
//		printf("car enableed");
//	 	printf("pitch=%f\t",pitch);
//		printf("gyroy=%d\n",gyroy-10);	
//		printf("d1=%f\t",d1);
//		printf("PWM=%d\n",Balance_Pwm);		
//		printf("gyroz=%d\n",gyroz);	 	
//		printf("aacx=%d\t",aacx);
//		printf("aacy=%d\t",aacy);	
//		printf("aacz=%d\n",aacz);
		Encoder1_Number=0;
//		delay_ms(5);
		Time7_Init(1999,72-1); //�ɼ��ж�
//		key=KEY_Scan(0);	//�õ���ֵ
//	   	if(key)
//		{						   
//			switch(key)
//			{				 
//				case 1:	
//				Time7_Init(1999,72-1);//8ms����һ��  ��Ҫ�ĺ���
//					break;
//				case 2:			
//				d1=d1+0.1;
//				OLED_ShowNum(36,26,d1,3,12);
//				OLED_Refresh_Gram();		//������ʾ��OLED 
//					break;
//				case 3:	
//				d2++;
//				OLED_ShowNum(54,26,d2,3,12);
//				OLED_Refresh_Gram();		//������ʾ��OLED 
//					break;
//				case 4:	 
//				
//					break;

//			}
//		}
		
}

u8 data_maching(void)
{

	u16 t;  
	extern u16 len;

//	printf("send ok");
	if(USART2_RX_STA&0x8000)
		{					   
			len=USART2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			for(t=0;t<len;t++)
			{
			    sss[t]=USART2_RX_BUF[t];
				u3_printf("%c",USART2_RX_BUF[t]);
//				u3_printf("%c\r\n",ttt1[t]);
//				USART_SendData(USART2, USART2_RX_BUF[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���				
			}

			USART2_RX_STA=0;
//			sss[t]=0;
		}
		else return 5;
		return 0;
}	
 
void judge ()
{
	u16 mode1;
	u16 t,i;  
	extern u16 len;
	extern int increment_1,increment_2,increment_3,increment_4;
	char *ttt1="forward";
	char *ttt2="backward";
	char *ttt3="left";
	char *ttt4="right";
	char *ttt5="111";
			mode1=memcmp(ttt1,sss,len);
			if(mode1==0)t=1;
			mode1=memcmp(ttt2,sss,len);
			if(mode1==0)t=2;
			mode1=memcmp(ttt3,sss,len);
			if(mode1==0)t=3;
			mode1=memcmp(ttt4,sss,len);
			if(mode1==0)t=4;
	        mode1=memcmp(ttt5,sss,len);
			if(mode1==0)t=5;


	switch (t) {case 1:u3_printf("1\r\n");increment_1=0;increment_2=250;increment_3=250;increment_4=0;break;
				 case 2:u3_printf("2\r\n");increment_1=250;increment_2=0;increment_3=0;increment_4=250;break;
			     case 3:u3_printf("3\r\n");increment_1=250;increment_2=0;increment_3=0;increment_4=0;break;
				 case 4:u3_printf("4\r\n");increment_1=0;increment_2=0;increment_3=0;increment_4=250;break;
				 case 5:u3_printf("5\r\n");increment_1=0;increment_2=0;increment_3=0;increment_4=0;break;
	}
	for(i=0;i<21;i++)
	{
		sss[i]=0;
	}
//	delay_ms(10000);
}

