/**
* @par Copyright (C): 2018-2028, DarrenPig
* @file         // main.c
* @author       // lly
* @version      // V1.0
* @date         // 250726
* @brief        // 程序入口 Program entry
* @details      
* @par History  // 修改历史记录列表，每条修改记录应包括修改日期、修改者及
*               // 修改内容简述  Modification history list, each modification record should include the modification date, modifier and a brief description of the modification content
*/ 

#include "AllHeader.h"
#include "intsever.h"
//注意:操作蜂鸣器的时候，要判断是否处于正常电压
//Attention: When operating the buzzer, check if it is at normal voltage

uint8_t GET_Angle_Way=2;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波  //Algorithm for obtaining angles, 1: Quaternion 2: Kalman 3: Complementary filtering
float Angle_Balance,Gyro_Balance,Gyro_Turn;     		//平衡倾角 平衡陀螺仪 转向陀螺仪 //Balance tilt angle balance gyroscope steering gyroscope
int Motor_Left,Motor_Right;                 	  		//电机PWM变量 //Motor PWM variable
int Temperature;                                		//温度变量 		//Temperature variable
float Acceleration_Z;                           		//Z轴加速度计  //Z-axis accelerometer
int Mid_Angle;                          						//机械中值  //Mechanical median
float Move_X,Move_Z; //Move_X:前进速度  Move_Z：转向速度  //Move_X: Forward speed Move_Z: Steering speed
u8 Stop_Flag = 1; //0:开始 1:停止  //0: Start 1: Stop


char showbuf[20]={'\0'};
u8* CCDShowBuf = NULL;

extern u8 newLineReceived;//蓝牙接收 //Bluetooth reception
extern u8 g_lidar_go_flag;
extern u8 bulettohflag;

int main(void)
{	
		
	bsp_init();//基本外设初始化 //Basic peripheral initialization
	
	Mode_select(); //按下按键结束模式选择 //Press the button to end mode selection
	
	bsp_mode_init();//根据模式初始化扩展外设 //Initialize and expand peripherals based on the pattern
	
	
	MPU6050_EXTI_Init();		//此中断服务函数放到最后  //This interrupt service function is placed last
	
	
	OLED_Draw_Line("put down key start!", 2, false, true); 
	
	while(!Key1_State(1) && Stop_Flag ==1 );
	Stop_Flag = 0; //开始控制  //Start controlling

	
	OLED_Draw_Line("start control!        ", 2, false, true); 
	


	while(1)
	{
		if(mode >= LiDar_avoid)//开启雷达模式 接收的数据 //Activate radar mode to receive data
		{
				if(lidar_new_pack == 1)  //放在这解算雷达数据,不可在中断解算  //Put it here to solve radar data, do not interrupt the calculation
				{
					lidar_new_pack = 0;
					Deal_lidardata();
				}
		}
		

		if(mode == Normal || mode == Weight_M)//正常模式、负重模式  //Normal mode, load mode
		{
			if (newLineReceived) //蓝牙遥控服务  //Bluetooth remote control service
			{
				ProtocolCpyData();
				Protocol();
			}
			if(bulettohflag == 1) 
			{
				bulettohflag = 0;
				SendAutoUp();//蓝牙自动上报数据 Bluetooth automatically reports data 
			}
					
			sprintf(showbuf,"dis =%d mm   ",g_distance);
			OLED_Draw_Line(showbuf, 3, false, true); 
		}
		
		else if(mode == U_Follow) //超声波跟随模式 Ultrasonic follow mode
		{
			sprintf(showbuf,"dis =%d mm   ",g_distance);
			OLED_Draw_Line(showbuf, 3, false, true); 
		}
		
		else if(mode == U_Avoid) //避障模式  //Obstacle avoidance mode
		{
			APP_avoid();
		}
		
		else if(mode == PS2_Control) //PS2控制模式   //PS2 control mode
		{
			sprintf(showbuf,"speed = %d  ",speed_flag);
			OLED_Draw_Line(showbuf, 3, false, true); 
//			PS2_Contorl_Car(); //在平衡中断服务处理了 加快响应 In the balance interrupt service processing to speed up the response
		}
		
		else if(mode == Line_Track || mode == Diff_Line_track) //4路巡线模式  //4-way patrol mode
		{
			sprintf(showbuf,"x1 = %d  x2 = %d    ",IN_X1,IN_X2);
			OLED_Draw_Line(showbuf, 2, false, true); 
			sprintf(showbuf,"x3 = %d  x4 = %d    ",IN_X3,IN_X4);
			OLED_Draw_Line(showbuf, 3, false, true); 
		}
		
		else if(mode == CCD_Mode) //CCD巡线模式  //CCD patrol mode
		{
			OLED_Show_CCD_Image(CCDShowBuf);//CCD显示 //CCD display
		}
		
		else if(mode == ElE_Mode) //电磁巡线模式 //Electromagnetic patrol mode
		{
			EleDataDeal();//显示结果  //Display results
		}
		
		else if(mode == K210_QR) //识别二维码模式  //Identify QR code patterns
		{
			Change_state_QR();//识别  //Identify
		}
		else if(mode == K210_SelfLearn) //自主学习模式 //Self directed learning mode
		{
			Change_state_self();
		}
		else if(mode == K210_mnist) //识别数字模式  //Identify numerical patterns
		{
			Change_state_minst();
		}
		
		else if(mode == LiDar_avoid)//雷达避障模式  //Radar obstacle avoidance mode
		{
			Car_Avoid();//避障  //Obstacle avoidance
		}
		else if(mode == LiDar_Follow)//雷达跟随模式  //Radar Follow Mode
		{
			Car_Follow();//跟随 //Follow me
		}
		else if(mode == LiDar_aralm)//雷达警卫模式  //Radar security mode
		{
			Car_Alarm();//警卫  //Security Guard
		}
		else if(mode == LiDar_Patrol)//雷达巡逻模式  //Radar patrol mode
		{
			Car_Patrol();//巡逻 //Patrol
		}
		else if(mode == LiDar_Line)//雷达直线模式  //Radar linear mode
		{
			if(g_lidar_go_flag == 1) //只操作一次  //Operate only once
			{
				g_lidar_go_flag = 0;
				OLED_Draw_Line("start track!     ", 3, false, true);
			}
		}
		
		
		
	}
}


