#include "motor.h"
#include "timer.h"
#include "oled.h"
#include "PID.h"
#include "filter.h"
#include "usart.h"
#include "inv_mpu.h"
#include "mpu6050.h"
int increment_1,increment_2,increment_3,increment_4;
int Balance_Pwm,Velocity_Pwm,Turn_Pwm;
float bias=0;
float ggg=0;
extern float d1,d2,Encoder1_Number,DC_motor1_speed;
//void DC_motor_init()  
//{
//	time3_PWM_Init(999,71);	 //不分频。PWM频率=72000000/900=80Khz   越大却快(370-899)
//	key1_Init();
////方向： 
//	RCC->APB2ENR|=1<<3;       //PORTB时钟使能 
//	GPIOB->CRH&=0X0000FFFF;   //PORTB12 13 14 15推挽输出
//	GPIOB->CRH|=0X22220000;   //PORTB12 13 14 15推挽输出
//}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
float myabs(float a)
{ 		   
	  float temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

void desplay(void)
{
	float t,s;
//	if((t%10)==0)
//	{ 
//		/*******************pitch*****************************/
		t=pitch;
	    s=myabs(pitch);
		if(t<0)
		{OLED_ShowString(32,15,"-",12);
		OLED_ShowNum(36,15,s,3,12);}
		else
		{OLED_ShowString(32,15,"+",12);
		OLED_ShowNum(36,15,s,3,12);}
		OLED_Refresh_Gram();
//		/*********************roll***************************/
//		t2=roll*10;
//		OLED_ShowNum(100,15,t2,3,12);
//		OLED_Refresh_Gram();
//		/*******************yaw*****************************/
//		t3=yaw*10;
//		OLED_ShowNum(36,30,t3,3,12);
//		OLED_Refresh_Gram();
//	}	

}

void run()
{
//	TIM_SetCompare1(TIM3,increment_1);TIM_SetCompare2(TIM3,increment_2);
//	TIM_SetCompare3(TIM3,increment_3);TIM_SetCompare4(TIM3,increment_4);
	
	int i,j; j=0; i=myabs(Balance_Pwm);
	if(i>6600)
		i=0;
	if(Balance_Pwm>0)
		{TIM_SetCompare1(TIM3,j+increment_1);TIM_SetCompare2(TIM3,i+increment_2);   //12 左轮，34右轮
		 TIM_SetCompare3(TIM3,i+increment_3);TIM_SetCompare4(TIM3,j+increment_4);}  //23正，14=0 后退
	if(Balance_Pwm<0)
		{TIM_SetCompare1(TIM3,i+increment_1);TIM_SetCompare2(TIM3,j+increment_2);   //23=0，14正 前进
		 TIM_SetCompare3(TIM3,j+increment_3);TIM_SetCompare4(TIM3,i+increment_4);}
}

void TIM6_IRQHandler(void)   //TIM6中断
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM6更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
		}
		
	DC_motor1_speed=Encoder1_Number*15;
	Balance_Pwm = DC_balance(pitch,gyroy);        //===平衡PID控制		
	run();
	Encoder1_Number=0;
}

void TIM7_IRQHandler(void)   //TIM7中断
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //检查TIM6更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);  //清除TIMx更新中断标志 
		}
		mpu_dmp_get_data();	                        //pitch
		MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据   gyroy

//		Kalman_Filter(aacx,gyrox);	
}

void  TIM2_IRQHandler(void)
{
 	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) == SET )              //捕获中断
	{
    Encoder1_Number++;  // 每来一个上升沿加一
		
	 TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	}
}

int DC_balance(float Angle,short Gyroy)
{  
/*********************电压8.28V电池******************************/

	int balance;
//   	 float i,j;
//	 i=myabs(Angle);
//	 j=myabs(Gyroy-10);  
//			 
//     if(i<0.1)
//	 {bias=0;}
//	 else if(i>0.1&&i<1)
//	 {if(Angle>0)bias=-1000;
//	 if(Angle<0)bias=1000;}       //1300   2600  5200  1000
//	 else if(i>1&&i<2)
//	 {bias=(0-Angle)*1200;}       //1300   1300  2600  1000
//	 else if(i>2&&i<3)
//	 {bias=(0-Angle)*1100;}       //1000               1000
//	 else if(i>3&&i<4)
//	 {bias=(0-Angle)*900;}        //850               1000
//	 else if(i>4&&i<5)
//	 {bias=(0-Angle)*800;}        //650               1000
//	 else if(i>5&&i<6)
//	 {bias=(0-Angle)*700;}        //550                800
//	 else if(i>6&&i<7)
//	 {bias=(0-Angle)*600;}        //500                800
//	 else if(i>7&&i<8)
//	 {bias=(0-Angle)*500;}        //450                800
//	 else if(i>8&&i<10)
//	 {bias=(0-Angle)*450;}        //500                660
//	 else if(i>10&&i<18)
//	 {bias=(0-Angle)*400;}        //450                360
//	 else if(i>18&&i<30)
//	 {bias=(0-Angle)*200;}        //220                220
//	 else if(i>30)
//	 {Angle=0;bias=0;}

//	 ggg=(Gyroy-10)*d1;

//     if((Angle*(Gyroy-10))<-200)
//		balance=bias-ggg ;	
//	 else balance=bias+ggg ;	
//	 return balance;
//	 Bias=LocPIDCalc(Angle);              //===求出平衡的角度中值 和机械相关 -0意味着身重中心在0度附近 如果身重中心在5度附近 那就应该减去5
//	 ggx=LocPIDCalc(Gyrox);
//	 balance=550*Bias+Gyro*0.1;//===计算平衡控制的电机PWM  PD控制   550是P系数 0.1是D系数 
//	 balance=-1000*Angle+Gyroy*0+DC_motor1_speed*5;
	 if(Angle<0)
	 balance=-1100*Angle+Gyroy*1.1+DC_motor1_speed*8;
	 else 
	 balance=-1100*Angle+Gyroy*1.1-DC_motor1_speed*8;
return balance;
/*******************************************************************

	 if(Angle>=0&&Gyrox+31>=0){
	 
	 }
	 if(Angle<=0&&Gyrox+31>=0){
	 balance=bias-ggg ;
	 }
	 if(Angle<=0&&Gyrox+31<=0){
	 balance=bias+ggg ;
	 }
	 if(Angle>=0&&Gyrox+31<=0){
	 balance=bias+ggg ;
	 }
	 
     return balance;
*/
}

/*-------------------------------------------------------------------------------------------------------------*/
/*       
        Q:过程噪声，Q增大，动态响应变快，收敛稳定性变坏
        R:测量噪声，R增大，动态响应变慢，收敛稳定性变好       
*/

//double KalmanFilter(const double ResrcData,
//                                        double ProcessNiose_Q,double MeasureNoise_R,double InitialPrediction)
//{
//        double R = MeasureNoise_R;
//        double Q = ProcessNiose_Q;

//        static        double x_last;

//        double x_mid = x_last;
//        double x_now;

//        static        double p_last;

//        double p_mid ;
//        double p_now;
//        double kg;       

//        x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
//        p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
//        kg=p_mid/(p_mid+R); //kg为kalman filter，R为噪声
//        x_now=x_mid+kg*(ResrcData-x_mid);//估计出的最优值
//               
//        p_now=(1-kg)*p_mid;//最优值对应的covariance       

//        p_last = p_now; //更新covariance值
//        x_last = x_now; //更新系统状态值

//        return x_now;               
//}

///*-------------------------------------------------------------------------------------------------------------*/

