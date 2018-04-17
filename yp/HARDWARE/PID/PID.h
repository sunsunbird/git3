#ifndef  _PID_h
#include "sys.h"
#define _PID_h
#include "delay.h"

//#define IncPID 1    //ʹ������ʽPID
#define LocPID 1  //ʹ��λ��ʽPID

/*����ʽPID*/
#if IncPID
void IncPIDInit(void);   //PID��ʼ��
int IncPIDCalc(int NextPoint); //PID����ֵ�ļ���
void IncPIDSet(int);//PID�趨ֵ���趨
void IncP_I_D_Set(double P, double I,double D);   //�����趨PID��������
#endif

/*λ��ʽPID*/
#if LocPID
void LocPIDInit(void);   //PID��ʼ��
int LocPIDCalc(int NextPoint); //PID����ֵ�ļ���
void LocPIDSet(int Point);//PID�趨ֵ���趨
void LocP_I_D_Set(double P, double I,double D);   //�����趨PID��������
#endif




#endif


