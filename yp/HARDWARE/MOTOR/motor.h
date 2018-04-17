#ifndef motor_h
#define motor_h
#include "sys.h"

//#define L_PWM   TIM3->CCR1
//#define R_PWM   TIM3->CCR2


//void DC_motor_init(void);  //电机初始化，带方向位
//void PWM_set(s16 L_motor,s16 R_motor);
//void stop(void);
//u8 L_DC_direction(u8 mode);
//u8 R_DC_direction(u8 mode);
float myabs(float a);
void desplay(void);
void run(void);
int DC_balance(float Angle,short Gyro);
extern	float pitch,roll,yaw; 	    //欧拉角
extern	short aacx,aacy,aacz;		//加速度传感器原始数据
extern  short gyrox,gyroy,gyroz;	//陀螺仪原始数据
#endif
