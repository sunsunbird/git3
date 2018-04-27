#include "GUI.h"
#include "DIALOG.h"
#include "BUTTON.h"
#include "led.h"
#include "beep.h"
#include "buttonbmp.h"
#include "buttonbmpdisp.h"



#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_0 (GUI_ID_USER + 0x03)
#define ID_BUTTON_1 (GUI_ID_USER + 0x04)
#define ID_BUTTON_2 (GUI_ID_USER + 0x05)
#define ID_DROPDOWN_0 (GUI_ID_USER + 0x06)



//对话框资源表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 154, 82, 120, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 155, 200, 120, 45, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 154, 143, 120, 45, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 12, 12, 121, 126, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

//对话框回调函数 	
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 40);
    FRAMEWIN_SetText(hItem, "Old_wang");
    FRAMEWIN_SetFont(hItem, GUI_FONT_20_1);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    FRAMEWIN_SetTextColor(hItem, 0x00FFFFFF);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "LED0");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetText(hItem, "BEEP");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetText(hItem, "LED1");
    BUTTON_SetFont(hItem, GUI_FONT_16_1);
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_SetFont(hItem, GUI_FONT_20_1);
		DROPDOWN_SetAutoScroll(hItem,1);	//启用自动使用滚动条
    DROPDOWN_AddString(hItem, "son");

    DROPDOWN_AddString(hItem, "father");

    DROPDOWN_AddString(hItem, "mother");
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
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        	    LED0=~LED0;		//LED0反转
//							led0flag=~led0flag;
//							BUTTON_SetBitmapEx(hItem,0,led0flag?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        	    LED1=~LED1;		//LED1反转
//							led1flag=~led1flag;
//							BUTTON_SetBitmapEx(hItem,0,led1flag?&buttonbmp_tab[1]:&buttonbmp_tab[0],0,0);	
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
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
				BEEP=~BEEP;		//蜂鸣器反转

        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

//创建一个对话框
WM_HWIN CreateFramewin(void);
//WM_HWIN CreateFramewin(void) 
//{
//	WM_HWIN hWin;
//	buttonbmp_tab[0]=bmBUTTONOFF;
//	buttonbmp_tab[1]=bmBUTTONON;
//	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
//	return hWin;
//}
WM_HWIN CreateFramewin(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

//BUTTON按钮上显示位图
void Buttonbmp_Demo(void)
{
	WM_HWIN hWin;
	hWin=CreateFramewin();
	while(1)
	{
		GUI_Delay(100);
	}
}

































