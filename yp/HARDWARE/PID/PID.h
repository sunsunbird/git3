#ifndef  _PID_h
#include "sys.h"
#define _PID_h
#include "delay.h"

//#define IncPID 1    //使用增量式PID
#define LocPID 1  //使用位置式PID

/*增量式PID*/
#if IncPID
void IncPIDInit(void);   //PID初始化
int IncPIDCalc(int NextPoint); //PID反馈值的计算
void IncPIDSet(int);//PID设定值的设定
void IncP_I_D_Set(double P, double I,double D);   //调用设定PID三个参数
#endif

/*位置式PID*/
#if LocPID
void LocPIDInit(void);   //PID初始化
int LocPIDCalc(int NextPoint); //PID反馈值的计算
void LocPIDSet(int Point);//PID设定值的设定
void LocP_I_D_Set(double P, double I,double D);   //调用设定PID三个参数
#endif




#endif


