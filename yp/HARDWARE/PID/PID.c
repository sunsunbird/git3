#include "PID.h"

//2017/7/21 laowang

//#define IncPID 1    //ʹ������ʽPID
#define LocPID 1  //ʹ��λ��ʽPID


#if IncPID      
/**************************����ʽPID**********************************/
#define  P_DATA      30         //P����
#define  I_DATA      0         //I����
#define  D_DATA      60         //D����


//����PID�ṹ��
typedef struct 
{
   __IO int      SetPoint;                  //�趨Ŀ�� Desired Value
   __IO double   Proportion;                //�������� Proportional Const
   __IO double   Integral;                  //���ֳ��� Integral Const
   __IO double   Derivative;                //΢�ֳ��� Derivative Const
   __IO int      LastError;                 //Error[-1]
   __IO int      PrevError;                 //Error[-2]
}PID;


 PID sPID;
 PID *sptr = &sPID;

//PID������ʼ��
void IncPIDInit(void) 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //�������� Proportional Const
    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
    sptr->SetPoint=330;           //�趨Ŀ��Desired Value     110,һȦ1��
}
/********************����ʽPID�������************************************/
int IncPIDCalc(int NextPoint) 
{
  int iError,iIncpid;                                 //��ǰ���
  iError=sptr->SetPoint-NextPoint;                    //��������
  iIncpid=(sptr->Proportion * iError)                 //E[k]��
              -(sptr->Integral * sptr->LastError)     //E[k-1]��
              +(sptr->Derivative * sptr->PrevError);  //E[k-2]��
              
  sptr->PrevError=sptr->LastError;                    //�洢�������´μ���
  sptr->LastError=iError;
  return(iIncpid);                                    //��������ֵ
}

void IncPIDSet(int Point)
{
  sptr->SetPoint=Point;
}
void IncP_I_D_Set(double P, double I,double D)    //�����趨PID��������
{
  sptr->Proportion=P+sum;
	sptr->Integral=I;
	sptr->Derivative=D;
}
/********************************************************************/
#endif

#if LocPID
/**************************λ��ʽPID**********************************/
#define  P_DATA      0         //P����
#define  I_DATA      0         //I����
#define  D_DATA      0     //D����

//����PID�ṹ��
typedef struct 
{
  __IO int      SetPoint;                                 //�趨Ŀ�� Desired Value
  __IO long     SumError;                                 //����ۼ�
  __IO double   Proportion;                               //�������� Proportional Const
  __IO double   Integral;                                 //���ֳ��� Integral Const
  __IO double   Derivative;                               //΢�ֳ��� Derivative Const
  __IO int      LastError;                                //Error[-1]
  __IO int      PrevError;                                //Error[-2]
}PID;

 PID sPID;
 PID *sptr = &sPID;

//PID������ʼ��
void LocPIDInit() 
{
    sptr->LastError=0;            //Error[-1]
    sptr->PrevError=0;            //Error[-2]
    sptr->Proportion=P_DATA;      //�������� Proportional Const
    sptr->Integral=I_DATA;        //���ֳ���  Integral Const
    sptr->Derivative=D_DATA;      //΢�ֳ��� Derivative Const
    sptr->SetPoint;           //�趨Ŀ��Desired Value
}

/********************λ��ʽ PID �������************************************/
int LocPIDCalc(int NextPoint)
{
  int iError,dError;
  iError = sptr->SetPoint - NextPoint; //ƫ��
  sptr->SumError += iError; //����
//	
//		if(sptr->SumError > 1000.0)									//�����޷�1000
//		sptr->SumError = 1000.0;
//	else if(sptr->SumError < -1000.0)
//		sptr->SumError = -1000.0;	
//	
  dError = iError - sptr->LastError; //΢��
  sptr->LastError = iError;
  return(sptr->Proportion * iError //������
  + sptr->Integral * sptr->SumError //������
  + sptr->Derivative * dError); //΢����
}

void LocPIDSet(int Point)    //�趨Ŀ��ֵ
{
  sptr->SetPoint=Point;
}

void LocP_I_D_Set(double P, double I,double D)    //�����趨PID��������
{
  sptr->Proportion=P;
	sptr->Integral=I;
	sptr->Derivative=D;
}
#endif


