#include "wifi.h"

void client_init()   //�ͻ��˳�ʼ��
{
//		u3_printf("AT+CWMODE=3");             //����WIFI AP+STAģʽ
//		delay_ms(500);
//		u3_printf("AT+CIOBAUD=921600");       //����ģ�鲨����
//		delay_ms(500);
		u3_printf("AT+RST\r\r\n");									 //����ģ�� 
		delay_ms(1000);         //��ʱ4S�ȴ������ɹ�
		delay_ms(1000);
		delay_ms(1000);
//	  delay_ms(1000);
	  LED0=0;
		//�������ӵ���WIFI��������/���ܷ�ʽ/����,�⼸��������Ҫ�������Լ���·�������ý����޸�!!	
		u3_printf("AT+CWJAP=\"OnePlus 5\",\"575ee6147930\"\n");   //������������
		delay_ms(1000);
		delay_ms(1000);
//		u3_printf("AT+CIPMUX=0");	  //0�������ӣ�1��������
		delay_ms(1000);
	  u3_printf("AT+CIPSTART=\"TCP\",\"192.168.43.155\",4300\r\r\n");
		delay_ms(1000);
		delay_ms(1000);
	  LED0=1;
}

void client_start()      //��ʼ͸��
{
	 u3_printf("AT+CIPMODE=1\r\r\n");
	 delay_ms(800);
	 u3_printf("AT+CIPSEND\r\r\n");
	 delay_ms(800);
	 LED1=0;
	delay_ms(10);
//	 LCD_ShowString(30,130,200,16,16,"ready..........");		
	 u3_printf("��ע��...............\r\r\n"); 
	 delay_ms(1000);
	 u3_printf("��ʼѲ��..............\r\r\n"); 
//   LCD_ShowString(30,150,200,16,16,"GO..........");
	 delay_ms(1000);
	 u3_printf("��ʼѲ��..............\r\r\n"); 
//	 LCD_ShowString(30,170,200,16,16,"GO..........");
	 delay_ms(1000);
	 u3_printf("��ʼѲ��..............\r\r\n"); 
//	 LCD_ShowString(30,190,200,16,16,"GO..........");
}

void client_back()
{
   u8 t;
	 u3_printf("\r\r\n\n\n"); 
	 delay_ms(1000);
   u3_printf("Ѳ�߽���..............\r\r\n"); 
//   LCD_ShowString(30,150,200,16,16,"END..........");
	 delay_ms(1000);
	 u3_printf("Ѳ�߽���..............\r\r\n");
	 delay_ms(1000);
	 u3_printf("Ѳ�߽���..............\r\r\n"); 
	 delay_ms(1000);
	 u3_printf("Ѳ�߽���..............\r\r\n"); 
	 delay_ms(1000);
	for(t=0;t<4;t++)
	{
	  u3_printf("+++"); 
    delay_ms(500);
	}
	 LED1=1;
	 delay_ms(1000);
	 u3_printf("AT\r\r\n"); 
	 delay_ms(1000);
	 u3_printf("AT\r\r\n");
	 delay_ms(1000);
	 u3_printf("AT+CIPMODE=0");     //�ر�͸��ģʽ
	 delay_ms(10);
}


