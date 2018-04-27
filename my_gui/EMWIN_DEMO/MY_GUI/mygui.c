#include "GUI.h"
#include "DIALOG.h"
#include "BUTTON.h"
#include "led.h"
#include "beep.h"
#include "mygui.h"
#include "stmflash.h"
#include "usart.h"
#include "CHECKBOX.h"
//#include "checkboxdemo.h"

extern u8 son_flag;
extern u8 father_flag;
extern u8 mother_flag;

u32 set_son_Buffer[16]   ={  0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u32 set_father_Buffer[16]={  0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u32 set_mother_Buffer[16]={  0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	
#define len_son sizeof(set_son_Buffer)	 	
#define size_son len_son/4+((len_son%4)?1:0)
#define len_father sizeof(set_father_Buffer)	 	
#define size_father len_father/4+((len_father%4)?1:0)
#define len_mother sizeof(set_mother_Buffer)	 	
#define size_mother len_mother/4+((len_mother%4)?1:0)

u32 datatemp_son[size_son];
u32 datatemp_father[size_father];
u32 datatemp_mother[size_mother];

int i,j,k,l=0;
int mode_son=1,mode_father=0,mode_mother=0;
int  flag_0,flag_1,flag_2,flag_3,flag_4,flag_5,flag_6,flag_7,
	 flag_8,flag_9,flag_10,flag_11,flag_12,flag_13,flag_14,flag_15,flag_16;
	
WM_HWIN CreateFramewin_1(void);
WM_HWIN CreateFramewin_2(void);

/***************界面一********************/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x07)
#define ID_BUTTON_0 (GUI_ID_USER + 0x09)
#define ID_BUTTON_1 (GUI_ID_USER + 0x0B)
#define ID_BUTTON_2 (GUI_ID_USER + 0x0C)
#define ID_BUTTON_3 (GUI_ID_USER + 0x0D)
#define ID_BUTTON_4 (GUI_ID_USER + 0x0E)
#define ID_BUTTON_5 (GUI_ID_USER + 0x0F)
#define ID_BUTTON_6 (GUI_ID_USER + 0x10)
#define ID_BUTTON_7 (GUI_ID_USER + 0x11)
#define ID_BUTTON_8 (GUI_ID_USER + 0x12)
#define ID_BUTTON_9 (GUI_ID_USER + 0x13)
#define ID_BUTTON_10 (GUI_ID_USER + 0x14)
#define ID_BUTTON_11 (GUI_ID_USER + 0x15)
#define ID_BUTTON_12 (GUI_ID_USER + 0x16)
#define ID_BUTTON_13 (GUI_ID_USER + 0x17)
#define ID_BUTTON_14 (GUI_ID_USER + 0x18)
#define ID_BUTTON_15 (GUI_ID_USER + 0x19)

/***********共用**************/
#define ID_TEXT_0 (GUI_ID_USER + 0x1B)
#define ID_TEXT_1 (GUI_ID_USER + 0x1C)
#define ID_TEXT_2 (GUI_ID_USER + 0x1D)
#define ID_TEXT_3 (GUI_ID_USER + 0x1E)
#define ID_BUTTON_16     (GUI_ID_USER + 0x21)
#define ID_BUTTON_17     (GUI_ID_USER + 0x22)

/***************界面二********************/
//#define ID_FRAMEWIN_1 (GUI_ID_USER + 0x1F)
#define ID_CHECKBOX_0 (GUI_ID_USER + 0x23)
#define ID_CHECKBOX_1 (GUI_ID_USER + 0x24)
#define ID_CHECKBOX_2 (GUI_ID_USER + 0x25)
#define ID_CHECKBOX_3 (GUI_ID_USER + 0x26)
#define ID_CHECKBOX_4 (GUI_ID_USER + 0x27)
#define ID_CHECKBOX_5 (GUI_ID_USER + 0x28)
#define ID_CHECKBOX_6 (GUI_ID_USER + 0x29)
#define ID_CHECKBOX_7 (GUI_ID_USER + 0x30)
#define ID_CHECKBOX_8 (GUI_ID_USER + 0x31)
#define ID_CHECKBOX_9 (GUI_ID_USER + 0x32)
#define ID_CHECKBOX_10 (GUI_ID_USER + 0x33)
#define ID_CHECKBOX_11 (GUI_ID_USER + 0x34)
#define ID_CHECKBOX_12 (GUI_ID_USER + 0x35)
#define ID_CHECKBOX_13 (GUI_ID_USER + 0x36)
#define ID_CHECKBOX_14 (GUI_ID_USER + 0x37)
#define ID_CHECKBOX_15 (GUI_ID_USER + 0x38)
#define ID_DROPDOWN_0 (GUI_ID_USER + 0x39)
#define ID_BUTTON_del (GUI_ID_USER + 0x40)
#define ID_BUTTON_save (GUI_ID_USER + 0x41)
#define ID_BUTTON_read (GUI_ID_USER + 0x42)


/***********对话框资源表**************/
//智能配置对话框
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_2[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0,  0, 0, 800, 480, 0, 0x64, 0   }, //MY_HOME方框
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_0,  150, 70, 100, 35, 0, 0x0, 0  },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_1,  300, 70, 100, 35, 0, 0x0, 0  },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_2,  450, 70, 130, 35, 0, 0x0, 0  },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_3,  600, 70, 100, 35, 0, 0x0, 0  },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_4,  150, 140, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_5,  300, 140, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_6,  450, 140, 130, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_7,  600, 140, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_8,  150, 210, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_9,  300, 210, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_10, 450, 210, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_11, 600, 210, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_12, 150, 280, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_13, 300, 280, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_14, 450, 280, 100, 35, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_15, 600, 280, 100, 35, 0, 0x0, 0 },
  { TEXT_CreateIndirect,     "Text",     ID_TEXT_0,      30, 75, 98, 20, 0, 0x64, 0   },
  { TEXT_CreateIndirect,     "Text",     ID_TEXT_1,      30, 145, 104, 20, 0, 0x64, 0 },//文本
  { TEXT_CreateIndirect,     "Text",     ID_TEXT_2,      30, 215, 80, 20, 0, 0x64, 0  },
  { TEXT_CreateIndirect,     "Text",     ID_TEXT_3,      30, 285, 80, 20, 0, 0x64, 0  },
  { BUTTON_CreateIndirect,   "Button",   ID_BUTTON_16,   5, 5, 122, 40, 0, 0x0, 0     },//按键
  { BUTTON_CreateIndirect,   "Button",   ID_BUTTON_17,   150, 5, 120, 40, 0, 0x0, 0   },
  { BUTTON_CreateIndirect,   "Button",   ID_BUTTON_del,  500, 380, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect,   "Button",   ID_BUTTON_save, 650, 380, 100, 35, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0,  650, 5, 135, 100, 0, 0x0, 0  },//下拉菜单
  { BUTTON_CreateIndirect,   "READ",     ID_BUTTON_read, 5, 380, 100, 35, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//家居控制对话框
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_1[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 150, 70, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 300, 70, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 450, 70, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_3, 600, 70, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_4, 150, 140, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_5, 300, 140, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_6, 450, 140, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_7, 600, 140, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_8, 150, 210, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_9, 300, 210, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_10, 450, 210, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_11, 600, 210, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_12, 150, 280, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_13, 300, 280, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_14, 450, 280, 100, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_15, 600, 280, 100, 35, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 30, 75, 98, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 30, 145, 104, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 30, 215, 80, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 30, 285, 80, 20, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_16, 5, 5, 122, 40, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_17, 150, 5, 120, 40, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//对话框回调函数
static void _cbDialog_1(WM_MESSAGE * pMsg);//家居控制
static void _cbDialog_2(WM_MESSAGE * pMsg);//智能配置


//智能配置
static void _cbDialog_2(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

	
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:    //初始化消息,创建窗口/控件时有效,比如在这里设置一些控件的初始参数
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 45);
    FRAMEWIN_SetText(hItem, "MY_HOME");
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_1);
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "LED");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
	  //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "FAN");
	  CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
    CHECKBOX_SetText(hItem, "air conditioner");
		CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
    CHECKBOX_SetText(hItem, "others");
		CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_4);
    CHECKBOX_SetText(hItem, "LED");
		CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_5);
    CHECKBOX_SetText(hItem, "FAN");
	  CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_6);
    CHECKBOX_SetText(hItem, "air conditioner");
		CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_7);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_8);
    CHECKBOX_SetText(hItem, "LED");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_9);
    CHECKBOX_SetText(hItem, "FAN");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_10);
    CHECKBOX_SetText(hItem, "Cooker");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_11);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_12);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_13);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_14);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_15);
    CHECKBOX_SetText(hItem, "others");
    CHECKBOX_SetFont(hItem, GUI_FONT_20_1);
		//
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "book room:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "living room:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "kitchen:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "others:");
	  //
    // Initialization of 'Button'
    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "home_control");
	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_read);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "Read");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "configuration");
		// Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_del);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "DELETE");
		// Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_save);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "SAVE_ALL");
		//
    // Initialization of 'Dropdown'
    //
	hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_SetFont(hItem, GUI_FONT_32_1);
    DROPDOWN_AddString(hItem, "son");
    DROPDOWN_AddString(hItem, "father");
    DROPDOWN_AddString(hItem, "mother");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
    case WM_NOTIFY_PARENT:               //操作触发消息处理(操作屏幕程序会跑到这里),比如点击按键、点击编辑框(任何的操作)等等......
    Id    = WM_GetId(pMsg->hWinSrc);      //返回小工具的ID
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_CHECKBOX_0: // Notifications sent by 'Checkbox' 
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:      //复选框已被点击
//				LED0=!LED0;
        break;
      case WM_NOTIFICATION_RELEASED:		  flag_0++;         //已释复选框
											 if(flag_0==2&&mode_son==1){    
												set_son_Buffer[0]=0;flag_0=0;
											  }
											 if(flag_0==1&&mode_son==1)
												set_son_Buffer[0]=1;    
											  if(flag_0==2&&mode_father==1){
												set_father_Buffer[0]=0;flag_0=0;
											  }
											  if(flag_0==1&&mode_father==1)
												set_father_Buffer[0]=1;
											  if(flag_0==2&&mode_mother==1){
												set_mother_Buffer[0]=0;flag_0=0;
											  }if(flag_0==1&&mode_mother==1)
												set_mother_Buffer[0]=1;
        break;
	  case WM_NOTIFICATION_MOVED_OUT:LED0=0; //复选框已被点击，且指针已移出框并且没有被释放
		break;
      case WM_NOTIFICATION_VALUE_CHANGED://复选框的状态已被改变
        break;
		}	  
		break;
		case ID_CHECKBOX_1: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
												flag_1++;
												if(flag_1==2&&mode_son==1){
												set_son_Buffer[1]=0;flag_1=0;
											  }
											  if(flag_1==1&&mode_son==1)
												set_son_Buffer[1]=1;
											  if(flag_1==2&&mode_father==1){
												set_father_Buffer[1]=0;flag_1=0;
											  }
											  if(flag_1==1&&mode_father==1)
												set_father_Buffer[1]=1;
											  if(flag_1==2&&mode_mother==1){
											  set_mother_Buffer[1]=0;flag_1=0;
											  }
											  if(flag_1==1&&mode_mother==1)
												set_mother_Buffer[1]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	  
		break;
		case ID_CHECKBOX_2: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
											  flag_2++;
											  if(flag_2==2&&mode_son==1){
												set_son_Buffer[2]=0;flag_2=0;
											  }
											  if(flag_2==1&&mode_son==1)
												 set_son_Buffer[2]=1;
											  if(flag_2==2&&mode_father==1){
												set_father_Buffer[2]=0;flag_2=0;
											  }
											  if(flag_2==1&&mode_father==1)
												 set_father_Buffer[2]=1;
											  if(flag_2==2&&mode_mother==1){
												set_mother_Buffer[2]=0;flag_2=0;
											  }
											  if(flag_2==1&&mode_mother==1)
												set_mother_Buffer[2]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	  
		break;
		case ID_CHECKBOX_3: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
											  flag_3++;
											  if(flag_3==2&&mode_son==1){
												set_son_Buffer[3]=0;flag_3=0;
											  }
											  if(flag_3==1&&mode_son==1)
												  set_son_Buffer[3]=1;
											  if(flag_3==2&&mode_father==1){
													set_father_Buffer[3]=0;flag_3=0;
											  }
											  if(flag_3==1&&mode_father==1)
												  set_mother_Buffer[3]=1;
											  if(flag_3==2&&mode_mother==1){
												set_mother_Buffer[3]=0;flag_3=0;}
											  if(flag_3==1&&mode_mother==1)
												  set_mother_Buffer[3]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	  
		break;
		case ID_CHECKBOX_4: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
//				LED1=!LED1;
        break;
      case WM_NOTIFICATION_RELEASED:
											  flag_4++;
											  if(flag_4==2&&mode_son==1){
												  set_son_Buffer[4]=0;flag_4=0;
											  }
											  if(flag_4==1&&mode_son==1)
												  set_son_Buffer[4]=1;
											  if(flag_4==2&&mode_father==1){
												set_father_Buffer[4]=0;flag_4=0;
											  }
											  if(flag_4==1&&mode_father==1)
												  set_father_Buffer[4]=1;
											  if(flag_4==2&&mode_mother==1){
												set_mother_Buffer[4]=0;flag_4=0;
											  }
											  if(flag_4==1&&mode_mother==1)
												  set_mother_Buffer[4]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	  
		break;
		case ID_CHECKBOX_5: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:flag_5++;if(flag_5==2&&mode_son==1){
												set_son_Buffer[5]=0;flag_5=0;
											  }
											  if(flag_5==1&&mode_son==1)
												  set_son_Buffer[5]=1;
											  if(flag_5==2&&mode_father==1){
												  set_father_Buffer[5]=0;flag_5=0;
											  }
											  if(flag_5==1&&mode_father==1)
												  set_father_Buffer[5]=1;
											  if(flag_5==2&&mode_mother==1){
												  set_mother_Buffer[5]=0;flag_5=0;
											  }
											  if(flag_5==1&&mode_mother==1)
												  set_mother_Buffer[5]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	  
		break;
		case ID_CHECKBOX_6: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:flag_6++;if(flag_6==2&&mode_son==1){
												set_son_Buffer[6]=0;flag_6=0;
											  }if(flag_6==1&&mode_son==1)
												set_son_Buffer[6]=1;
											  if(flag_6==2&&mode_father==1){
												set_father_Buffer[6]=0;flag_6=0;
											  }
											  if(flag_6==1&&mode_father==1)
												  set_father_Buffer[6]=1;
											  if(flag_6==2&&mode_mother==1){
												  set_mother_Buffer[6]=0;flag_6=0;
											  }
											  if(flag_6==1&&mode_mother==1)
												  set_mother_Buffer[6]=1;
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        break;
		}	
		break;
		case ID_CHECKBOX_7: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_7++;if(flag_7==2&&mode_son==1){
												set_son_Buffer[7]=0;flag_7=0;
											  }if(flag_7==1&&mode_son==1)
												set_son_Buffer[7]=1;
											  if(flag_7==2&&mode_father==1){
											  set_father_Buffer[7]=0;flag_7=0;
											  }
											  if(flag_7==1&&mode_father==1)
												  set_father_Buffer[7]=1;
											  if(flag_7==2&&mode_mother==1){
												set_mother_Buffer[7]=0;flag_7=0;
											  }
											  if(flag_7==1&&mode_mother==1)
												  set_mother_Buffer[7]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_8: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_8++;if(flag_8==2&&mode_son==1){
													set_son_Buffer[8]=0;flag_8=0;
											  }
											  if(flag_8==1&&mode_son==1)
													set_son_Buffer[8]=1;
											  if(flag_8==2&&mode_father==1){
													set_father_Buffer[8]=0;flag_8=0;
											  }
											  if(flag_8==1&&mode_father==1)
												  set_father_Buffer[8]=1;
											  if(flag_8==2&&mode_mother==1){
													set_mother_Buffer[8]=0;flag_8=0;
											  }
											  if(flag_8==1&&mode_mother==1)
													set_mother_Buffer[8]=1;
 
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_9: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_9++;if(flag_9==2&&mode_son==1){
													set_son_Buffer[9]=0;flag_9=0;
											  }
											  if(flag_9==1&&mode_son==1)
													set_son_Buffer[9]=1;
											  if(flag_9==2&&mode_father==1){
													set_father_Buffer[9]=0;flag_9=0;
											  }
											  if(flag_9==1&&mode_father==1)
												  set_father_Buffer[9]=1;
											  if(flag_9==2&&mode_mother==1){
													set_mother_Buffer[9]=0;flag_9=0;
											  }
											  if(flag_9==1&&mode_mother==1)
												  set_mother_Buffer[9]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_10: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_10++;if(flag_10==2&&mode_son==1){
													set_son_Buffer[10]=0;flag_10=0;
											  }
											  if(flag_10==1&&mode_son==1)
												  set_son_Buffer[10]=1;
											  if(flag_10==2&&mode_father==1){
													set_father_Buffer[10]=0;flag_10=0;
											  }
											  if(flag_10==1&&mode_father==1)
												  set_father_Buffer[10]=1;
											  if(flag_10==2&&mode_mother==1){
													set_mother_Buffer[10]=0;flag_10=0;
											  }
											  if(flag_10==1&&mode_mother==1)
												  set_mother_Buffer[10]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	 
		break;
		case ID_CHECKBOX_11: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_11++;if(flag_11==2&&mode_son==1){
													set_son_Buffer[11]=0;flag_11=0;
											  }
											  if(flag_11==1&&mode_son==1)
												  set_son_Buffer[11]=1;
											  if(flag_11==2&&mode_father==1){
													set_father_Buffer[11]=0;flag_11=0;
											  }
											  if(flag_11==1&&mode_father==1)
												  set_father_Buffer[11]=1;
											  if(flag_11==2&&mode_mother==1){
													set_mother_Buffer[11]=0;flag_11=0;
											  }
											  if(flag_11==1&&mode_mother==1)
												  set_mother_Buffer[11]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_12: // Notifications sent by 'Checkbox'
      switch(NCode) {
	  case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:flag_12++;if(flag_12==2&&mode_son==1){
												set_son_Buffer[12]=0;flag_12=0;
											  }
											  if(flag_12==1&&mode_son==1)
												  set_son_Buffer[12]=1;
											  if(flag_12==2&&mode_father==1){
											  set_father_Buffer[12]=0;flag_12=0;
											  }
											  if(flag_12==1&&mode_father==1)
												  set_father_Buffer[12]=1;
											  if(flag_12==2&&mode_mother==1){
												set_mother_Buffer[12]=0;flag_12=0;
											  }
											  if(flag_12==1&&mode_mother==1)
												  set_mother_Buffer[12]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_13: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_13++;if(flag_13==2&&mode_son==1){
												set_son_Buffer[13]=0;flag_13=0;
											  }
											  if(flag_13==1&&mode_son==1)
												  set_son_Buffer[13]=1;
											  if(flag_13==2&&mode_father==1){
												set_father_Buffer[13]=0;flag_13=0;
											  }
											  if(flag_13==1&&mode_father==1)
												  set_father_Buffer[13]=1;
											  if(flag_13==2&&mode_mother==1){
												set_mother_Buffer[13]=0;flag_13=0;
											  }
											  if(flag_13==1&&mode_mother==1)
												  set_mother_Buffer[13]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_14: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
 
        break;
      case WM_NOTIFICATION_RELEASED:flag_14++;if(flag_14==2&&mode_son==1){
												set_son_Buffer[14]=0;flag_14=0;
											  }
											  if(flag_14==1&&mode_son==1)
												  set_son_Buffer[14]=1;
											  if(flag_14==2&&mode_father==1){
												set_father_Buffer[14]=0;flag_14=0;
											  }
											  if(flag_14==1&&mode_father==1)
												  set_father_Buffer[14]=1;
											  if(flag_14==2&&mode_mother==1){
												set_mother_Buffer[14]=0;flag_14=0;
											  }
											  if(flag_14==1&&mode_mother==1)
												  set_mother_Buffer[14]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_CHECKBOX_15: // Notifications sent by 'Checkbox'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

        break;
      case WM_NOTIFICATION_RELEASED:flag_15++;if(flag_15==2&&mode_son==1){
												set_son_Buffer[15]=0;flag_15=0;
											  }
											  if(flag_15==1&&mode_son==1)
												  set_son_Buffer[15]=1;
											  if(flag_15==2&&mode_father==1){
												set_father_Buffer[15]=0;flag_15=0;
											  }
											  if(flag_15==1&&mode_father==1)
												  set_father_Buffer[15]=1;
											  if(flag_15==2&&mode_mother==1){
												set_mother_Buffer[15]=0;flag_15=0;
											  }
											  if(flag_15==1&&mode_mother==1)
												  set_mother_Buffer[15]=1;

        break;
      case WM_NOTIFICATION_VALUE_CHANGED:

        break;
		}	  
		break;
		case ID_BUTTON_16: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
         GUI_EndDialog(pMsg->hWin, 0);
         CreateFramewin_1();
			break;
      case WM_NOTIFICATION_RELEASED:

        break;

      }
      break;
		case ID_BUTTON_del: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

			break;
      case WM_NOTIFICATION_RELEASED:
									 for(i=0;i<20;i++)
									 {
										 set_son_Buffer[i]=0;
										 set_father_Buffer[i]=0;
										 set_mother_Buffer[i]=0;
										 
									 }
									 
									 flag_0=0;flag_1=0;flag_2=0;flag_3=0;flag_4=0;flag_5=0;flag_6=0;flag_7=0;flag_8=0;
									 flag_9=0;flag_10=0;flag_11=0;flag_12=0;flag_13=0;flag_14=0;flag_15=0;
									
/***********************************************************************************************************************************/
									
//									
/***********************************************************************************************************************************/
		  							GUI_EndDialog(pMsg->hWin, 0);
									CreateFramewin_2();
									
									
        break;
      }
      break;
		case ID_BUTTON_save: // Notifications sent by 'Button'           save
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:

			break;
      case WM_NOTIFICATION_RELEASED:
/***********************************************************************************************************************************/
									if(mode_son==1&&mode_father==0&&mode_mother==0)
									 STMFLASH_Write(FLASH_SON_SAVE_ADDR,(u32*)set_son_Buffer,size_son);
									
									if(mode_son==0&&mode_father==1&&mode_mother==0)
									 STMFLASH_Write(FLASH_FATHER_SAVE_ADDR,(u32*)set_father_Buffer,size_father);
									
									if(mode_son==0&&mode_father==0&&mode_mother==1)
									 STMFLASH_Write(FLASH_MOTHER_SAVE_ADDR,(u32*)set_mother_Buffer,size_mother);
/***********************************************************************************************************************************/
//									 printf("write ok!");
//									 GUI_EndDialog(pMsg->hWin, 0);
//									 CreateFramewin_2();
        break;

      }
      break;
		case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
//				    switch(DROPDOWN_GetListbox()){
//						
//						}		
									l++;
									if(l==0)
									{
										mode_son=1;mode_father=0;mode_mother=0;
									}
									if(l==1)
									{	
										mode_son=0;mode_father=1;mode_mother=0;
										flag_0=0;flag_1=0;flag_2=0;flag_3=0;flag_4=0;flag_5=0;flag_6=0;flag_7=0;
										flag_8=0;flag_9=0;flag_10=0;flag_11=0;flag_12=0;flag_13=0;flag_14=0;flag_15=0;
									}
									if(l==2)
									{	
										mode_son=0;mode_father=0;mode_mother=1;
										flag_0=0;flag_1=0;flag_2=0;flag_3=0;flag_4=0;flag_5=0;flag_6=0;flag_7=0;
									    flag_8=0;flag_9=0;flag_10=0;flag_11=0;flag_12=0;flag_13=0;flag_14=0;flag_15=0;
									}
									if(l==3)
									{	
										l=0;
										mode_son=1;mode_father=0;mode_mother=0;
										flag_0=0;flag_1=0;flag_2=0;flag_3=0;flag_4=0;flag_5=0;flag_6=0;flag_7=0;flag_8=0;
										flag_9=0;flag_10=0;flag_11=0;flag_12=0;flag_13=0;flag_14=0;flag_15=0;
									}
									 GUI_EndDialog(pMsg->hWin, 0);
									 CreateFramewin_2();
									
        break;
      }
	  break;
	  
	  case ID_BUTTON_read: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
//					                printf("son:\r\n");
									STMFLASH_Read(FLASH_SON_SAVE_ADDR,(u32*)datatemp_son,size_son);
//									for(i=0;i<16;i++)
//									{
//									printf("%d",datatemp_son[i]);
//									}		
//									printf("\r\n");
//									printf("father:\r\n");
									STMFLASH_Read(FLASH_FATHER_SAVE_ADDR,(u32*)datatemp_father,size_father);
//									for(i=0;i<16;i++)
//									{
//									printf("%d",datatemp_father[i]);
//									}		
//		  							printf("\r\n");
//									printf("mother:\r\n");
									STMFLASH_Read(FLASH_MOTHER_SAVE_ADDR,(u32*)datatemp_mother,size_mother);
//									for(i=0;i<16;i++)
//									{
//									printf("%d",datatemp_mother[i]);
//									}	
									read_config();
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;
      }
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

static void _cbDialog_1(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {                   //区分各种消息类型
  case WM_INIT_DIALOG:                     //外观初始化
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 45);
    FRAMEWIN_SetText(hItem, "MY_HOME");
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_1);
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "LED");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "FAN");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "air conditioner");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetText(hItem, "others");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "LED");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetText(hItem, "FAN");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "air conditioner");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_7);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "TV");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_8);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "LED");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_9);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "FAN");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_10);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "Cooker");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_11);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    BUTTON_SetText(hItem, "others");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_12);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_13);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_14);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_15);
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "book room:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "living room:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "kitchen:");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_20_1);
    TEXT_SetText(hItem, "others:");
	  //
    // Initialization of 'Button'
    //
		hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_16);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "home_control");
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_17);
    BUTTON_SetFont(hItem, GUI_FONT_20_1);
    BUTTON_SetText(hItem, "configuration");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					LED0=!LED0;
			break;
		  case WM_NOTIFICATION_RELEASED:
			break;
		}
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					FAN0=!FAN0;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:

					AIR_C0 =!AIR_C0;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					OTHER1=!OTHER1;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_4: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					LED1=!LED1;

			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_5: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					FAN1=!FAN1;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_6: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					AIR_C1=!AIR_C1;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_7: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					TV=!TV;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_8: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					LED2=!LED2;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_9: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					FAN2=!FAN2;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_10: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					COOKER=!COOKER;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_11: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
					OTHER2=!OTHER2;
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_12: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:

			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_13: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:

			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_14: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:

			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_15: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:

			break;
		  case WM_NOTIFICATION_RELEASED:

			break;

      }
      break;
    case ID_BUTTON_17: // Notifications sent by 'Button'
      switch(NCode) {
		  case WM_NOTIFICATION_CLICKED:
				   GUI_EndDialog(pMsg->hWin, 0);
				   CreateFramewin_2();
			break;
		  case WM_NOTIFICATION_RELEASED:

			break;
    }
    break;

	}
	break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}


/***********创建对话框***************/

//创建界面1:家居控制
WM_HWIN CreateFramewin_1(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate_1, GUI_COUNTOF(_aDialogCreate_1), _cbDialog_1, WM_HBKWIN, 0, 0);
  return hWin;
}
//创建界面2:智能配置
WM_HWIN CreateFramewin_2(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate_2, GUI_COUNTOF(_aDialogCreate_2), _cbDialog_2, WM_HBKWIN, 0, 0);
  return hWin;
}

void my_gui_create(void)
{
	WM_HWIN hWin;
	hWin=CreateFramewin_1();
	while(1)
	{
		GUI_Delay(100);
	}
}
//LISTBOX_Handle DROPDOWN_GetListbox();

void read_config(void)
{
	son_flag=1;
	if(son_flag==1)
	{
//	STMFLASH_Read(FLASH_SON_SAVE_ADDR,(u32*)datatemp_son,size_son);
		for(i=0;i<16;i++){
		if(datatemp_son[i]==1){
		switch (i){
			case 0: LED0=!LED0;break;
			case 1: FAN0=!FAN0;break;
			case 2: AIR_C0=!AIR_C0;break;
			case 3: OTHER1=!OTHER1;break;
			case 4: LED1=!LED1;break;
			case 5: FAN1=!FAN1;break;
			case 6: AIR_C1=!AIR_C1;break;
			case 7: TV=!TV;break;
			case 8: LED2=!LED2;break;
			case 9: FAN2=!FAN2;break;
			case 10:COOKER=!COOKER; break;
			case 11:OTHER2=!OTHER2; break;
			case 12: break;
			case 13: break;
			case 14: break;
			case 15: break;	
		}			
		}
		}
		
	}
	if(father_flag==1)
	{
//	STMFLASH_Read(FLASH_FATHER_SAVE_ADDR,(u32*)datatemp_father,size_father);
		for(i=0;i<16;i++){
		if(datatemp_father[i]==1){
		switch (i){
			case 0: LED0=!LED0;break;
			case 1: FAN0=!FAN0;break;
			case 2: AIR_C0=!AIR_C0;break;
			case 3: OTHER1=!OTHER1;break;
			case 4: LED1=!LED1;break;
			case 5: FAN1=!FAN1;break;
			case 6: AIR_C1=!AIR_C1;break;
			case 7: TV=!TV;break;
			case 8: LED2=!LED2;break;
			case 9: FAN2=!FAN2;break;
			case 10:COOKER=!COOKER; break;
			case 11:OTHER2=!OTHER2; break;
			case 12: break;
			case 13: break;
			case 14: break;
			case 15: break;	
		}			
		}
		}
	}
	if(mother_flag==1)
	{
//	STMFLASH_Read(FLASH_MOTHER_SAVE_ADDR,(u32*)datatemp_mother,size_mother);
		for(i=0;i<16;i++){
		if(datatemp_mother[i]==1){
		switch (i){
			case 0: LED0=!LED0;break;
			case 1: FAN0=!FAN0;break;
			case 2: AIR_C0=!AIR_C0;break;
			case 3: OTHER1=!OTHER1;break;
			case 4: LED1=!LED1;break;
			case 5: FAN1=!FAN1;break;
			case 6: AIR_C1=!AIR_C1;break;
			case 7: TV=!TV;break;
			case 8: LED2=!LED2;break;
			case 9: FAN2=!FAN2;break;
			case 10:COOKER=!COOKER; break;
			case 11:OTHER2=!OTHER2; break;
			case 12: break;
			case 13: break;
			case 14: break;
			case 15: break;	
		}			
		}
		}
	}



}

