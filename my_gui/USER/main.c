#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"
#include "led.h"
#include "beep.h"
#include "timer.h"
#include "touch.h"
#include "sdio_sdcard.h"
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "includes.h"
#include "WM.h"
#include "DIALOG.h"
#include "mygui.h"
#include "key.h"
#include "stmflash.h" 

u8 son_flag=0;
u8 father_flag=0;
u8 mother_flag=0;
u8 sss[1];


#define Son 1
#define Father 2
#define Mother 3



//任务优先级
#define START_TASK_PRIO				3
//任务堆栈大小	
#define START_STK_SIZE 				1024
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//TOUCH任务
//设置任务优先级
#define TOUCH_TASK_PRIO				4
//任务堆栈大小
#define TOUCH_STK_SIZE				128
//任务控制块
OS_TCB TouchTaskTCB;
//任务堆栈
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch任务
void touch_task(void *p_arg);


//任务优先级
#define KEY_TASK_PRIO		5
//任务堆栈大小	
#define KEY_STK_SIZE 		164
//任务控制块
OS_TCB KEY_TaskTCB;
//任务堆栈	
CPU_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void KEY_task(void *p_arg);

//EMWINDEMO任务
//设置任务优先级
#define EMWINDEMO_TASK_PRIO			6
//任务堆栈大小
#define EMWINDEMO_STK_SIZE			3000
//任务控制块
OS_TCB EmwindemoTaskTCB;
//任务堆栈
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task任务
void emwindemo_task_1(void *p_arg);


//设置任务优先级
#define DATAMATCH_TASK_PRIO			7
//任务堆栈大小
#define DATAMATCH_STK_SIZE			128
//任务控制块
OS_TCB DATAMATCH_TaskTCB;
//任务堆栈
CPU_STK DATAMATCH_TASK_STK[DATAMATCH_STK_SIZE];
//emwindemo_task任务
void datamatch_task(void *p_arg);



int main(void)
{
	int i;
	char q='\31';
	OS_ERR err;
	CPU_SR_ALLOC();
	delay_init(168);       	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//中断分组配置
	uart_init(115200);    	//串口波特率设置
	TFTLCD_Init();			//初始化LCD
	W25QXX_Init();			//初始化W25Q128   -- SPI  16M的flash
	LED_Init();   			//LED初始化
	BEEP_Init();			//初始化蜂鸣器 
	KEY_Init();
	FSMC_SRAM_Init(); 		//SRAM初始化	  -- 外部IS62WV51216  1M
	mem_init(SRAMIN); 		//内部RAM初始化   内部192K的SRAM
	mem_init(SRAMEX); 		//外部RAM初始化
	mem_init(SRAMCCM);		//CCM初始化
	
	exfuns_init();			//为fatfs文件系统分配内存
	f_mount(fs[0],"0:",1);	//挂载SD卡
	f_mount(fs[1],"1:",1);	//挂载FLASH

	TP_Init();				//初始化触摸屏
	OSInit(&err);			//初始化UCOSIII
	OS_CRITICAL_ENTER();	//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);  //开启UCOSIII
	while(1){};
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//开启CRC时钟
	WM_SetCreateFlags(WM_CF_MEMDEV); //启动所有窗口的存储设备
	GUI_Init();  			//STemWin初始化
	
	OS_CRITICAL_ENTER();	//进入临界区
	//创建按键任务
	OSTaskCreate((OS_TCB 	* )&KEY_TaskTCB,		
				 (CPU_CHAR	* )"KEY task", 		
                 (OS_TASK_PTR )KEY_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )KEY_TASK_PRIO,     	
                 (CPU_STK   * )&KEY_TASK_STK[0],	
                 (CPU_STK_SIZE)KEY_STK_SIZE/10,	
                 (CPU_STK_SIZE)KEY_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);		
	//STemWin Demo任务	
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,		
				 (CPU_CHAR*   )"Emwindemo task", 		
                 (OS_TASK_PTR )emwindemo_task_1, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,     
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//触摸屏任务
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);		
	//数据接受任务
	OSTaskCreate((OS_TCB*     )&DATAMATCH_TaskTCB,		
				 (CPU_CHAR*   )"Datamatch task", 		
                 (OS_TASK_PTR )datamatch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )DATAMATCH_TASK_PRIO,     
                 (CPU_STK*    )&DATAMATCH_TASK_STK[0],	
                 (CPU_STK_SIZE)DATAMATCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)DATAMATCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);				 
		 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//退出临界区
}

//家居控制任务
void emwindemo_task_1(void *p_arg)
{
	GUI_CURSOR_Show(); 
	
	//更换皮肤
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX); 

	while(1)
	{
   my_gui_create();
	}
}


//TOUCH任务
void touch_task(void *p_arg)
{
	static u16 num=0;
	static int xvalue,yvalue;
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
}

//按键任务
void KEY_task(void *p_arg)
{
	u8 key;
	u8 family_member=0;
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
		 son_flag=1;
		}
		else if (key==KEY2_PRES)
		{
		 mother_flag=1;
		}
		else if (key==WKUP_PRES)
		{
		 father_flag=1;
		}
		else if(key==KEY1_PRES)
		{
		 	   				   
		}   
 		delay_ms(10);
		
		switch(family_member)
		{
			case Son:
				break;
			case Father:
		  	break;
			case Mother:
				break;
		}
	}
}


void datamatch_task(void *p_arg)
{
	u16 t;  
	u16 len;
	OS_ERR err;
	while(1)
	{
	if(USART_RX_STA&0x8000)
	{					   
		sss[0]=USART_RX_BUF[0];
			
	if(sss[0]==49)
	{
		son_flag=1;
		father_flag=0;
		mother_flag=0;
		auto_config();
		
	}
	else if(sss[0]==50)
	{
		son_flag=0;
		father_flag=1;
		mother_flag=0;
		auto_config();
	}
	else if(sss[0]==51)
	{
		son_flag=0;
		father_flag=0;
		mother_flag=1;
		auto_config();
		
	}
	else 
	{
		son_flag=0;
		father_flag=0;
		mother_flag=0;
	
	}
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束				
		USART_RX_STA=0;
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//延时5ms
	}
	}

}


