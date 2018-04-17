#include "wifi.h"

void client_init()   //客户端初始化
{
//		u3_printf("AT+CWMODE=3");             //设置WIFI AP+STA模式
//		delay_ms(500);
//		u3_printf("AT+CIOBAUD=921600");       //设置模块波特率
//		delay_ms(500);
		u3_printf("AT+RST\r\r\n");									 //重启模块 
		delay_ms(1000);         //延时4S等待重启成功
		delay_ms(1000);
		delay_ms(1000);
//	  delay_ms(1000);
	  LED0=0;
		//设置连接到的WIFI网络名称/加密方式/密码,这几个参数需要根据您自己的路由器设置进行修改!!	
		u3_printf("AT+CWJAP=\"OnePlus 5\",\"575ee6147930\"\n");   //连接室内无线
		delay_ms(1000);
		delay_ms(1000);
//		u3_printf("AT+CIPMUX=0");	  //0：单连接，1：多连接
		delay_ms(1000);
	  u3_printf("AT+CIPSTART=\"TCP\",\"192.168.43.155\",4300\r\r\n");
		delay_ms(1000);
		delay_ms(1000);
	  LED0=1;
}

void client_start()      //开始透传
{
	 u3_printf("AT+CIPMODE=1\r\r\n");
	 delay_ms(800);
	 u3_printf("AT+CIPSEND\r\r\n");
	 delay_ms(800);
	 LED1=0;
	delay_ms(10);
//	 LCD_ShowString(30,130,200,16,16,"ready..........");		
	 u3_printf("请注意...............\r\r\n"); 
	 delay_ms(1000);
	 u3_printf("开始巡逻..............\r\r\n"); 
//   LCD_ShowString(30,150,200,16,16,"GO..........");
	 delay_ms(1000);
	 u3_printf("开始巡逻..............\r\r\n"); 
//	 LCD_ShowString(30,170,200,16,16,"GO..........");
	 delay_ms(1000);
	 u3_printf("开始巡逻..............\r\r\n"); 
//	 LCD_ShowString(30,190,200,16,16,"GO..........");
}

void client_back()
{
   u8 t;
	 u3_printf("\r\r\n\n\n"); 
	 delay_ms(1000);
   u3_printf("巡逻结束..............\r\r\n"); 
//   LCD_ShowString(30,150,200,16,16,"END..........");
	 delay_ms(1000);
	 u3_printf("巡逻结束..............\r\r\n");
	 delay_ms(1000);
	 u3_printf("巡逻结束..............\r\r\n"); 
	 delay_ms(1000);
	 u3_printf("巡逻结束..............\r\r\n"); 
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
	 u3_printf("AT+CIPMODE=0");     //关闭透传模式
	 delay_ms(10);
}


