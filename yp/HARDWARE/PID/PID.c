#include "PID.h"

//2017/7/21 laowang

//#define IncPID 1    //使用增量式PID
#define LocPID 1  //使用位置式PID


#if IncPID      
/**************************增量式PID**********************************/
#define  P_DATA      30         //P参数
#define  I_DATA      0         //I参数
#define  D_DATA      60         //D参数


//定义PID结构体
typedef struct 
{
   __IO int      SetPoint;                  //设定目标 Desired Value
   __IO double   Proportion;                //比例常数 Proportional Const
   __IO double   Integral;                  //积分常数 Integral Const
   __IO double   Derivative;                //微分常数 Derivative Const
   __IO int      LastError;                 //Error[-1]
   __IO int      PrevError;                 //Error[-2]
}PID;


 PID sPID;
 PID *sptr = &sPID;

//PID参数初始化
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //比例常数 Proportional Const
    sptr->Integral=I_DATA;        //积分常数  Integral Const
    sptr->Derivative=D_DATA;      //微分常数 Derivative Const
    sptr->SetPoint=330;           //设定目标Desired Value     110,一圈1秒
}
/********************增量式PID控制设计************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //当前误差
  iError=sptr->SetPoint-NextPoint;                    //增量计算
  iIncpid=(sptr->Proportion * iError)                 //E[k]项
              -(sptr->Integral * sptr->LastError)     //E[k-1]项
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]项
              
  sptr->PrevError=sptr->LastError;                    //存储误差，用于下次计算
  sptr->LastError=iError;
  return(iIncpid);                                    //返回增量值
}

void IncPIDSet(int Point)
{
  sptr->SetPoint=Point;
}
void IncP_I_D_Set(double P, double I,double D)    //调用设定PID三个参数
{
  sptr->Proportion=P+sum;
	sptr->Integral=I;
	sptr->Derivative=D;
}
/********************************************************************/
#endif

#if LocPID
/**************************位置式PID**********************************/
#define  P_DATA      0         //P参数
#define  I_DATA      0         //I参数
#define  D_DATA      0     //D参数

//定义PID结构体
typedef struct 
{
  __IO int      SetPoint;                                 //设定目标 Desired Value
  __IO long     SumError;                                 //误差累计
  __IO double   Proportion;                               //比例常数 Proportional Const
  __IO double   Integral;                                 //积分常数 Integral Const
  __IO double   Derivative;                               //微分常数 Derivative Const
  __IO int      LastError;                                //Error[-1]
  __IO int      PrevError;                                //Error[-2]
}PID;

 PID sPID;
 PID *sptr = &sPID;

//PID参数初始化
void LocPIDInit() 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //比例常数 Proportional Const
    sptr->Integral=I_DATA;        //积分常数  Integral Const
    sptr->Derivative=D_DATA;      //微分常数 Derivative Const
    sptr->SetPoint;           //设定目标Desired Value
}

/********************位置式 PID 控制设计************************************/
int LocPIDCalc(int NextPoint)
{
  int iError,dError;
  iError = sptr->SetPoint - NextPoint; //偏差
  sptr->SumError += iError; //积分
//	
//		if(sptr->SumError > 1000.0)									//积分限幅1000
//		sptr->SumError = 1000.0;
//	else if(sptr->SumError < -1000.0)
//		sptr->SumError = -1000.0;	
//	
  dError = iError - sptr->LastError; //微分
  sptr->LastError = iError;
  return(sptr->Proportion * iError //比例项
  + sptr->Integral * sptr->SumError //积分项
  + sptr->Derivative * dError); //微分项
}

void LocPIDSet(int Point)    //设定目标值
{
  sptr->SetPoint=Point;
}

void LocP_I_D_Set(double P, double I,double D)    //调用设定PID三个参数
{
  sptr->Proportion=P;
	sptr->Integral=I;
	sptr->Derivative=D;
}
#endif


