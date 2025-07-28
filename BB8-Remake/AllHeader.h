/**
* @par Copyright (C): 2016-2026, Shenzhen Yahboom Tech
* @file         // ALLHeader.h
* @author       // lly
* @version      // V1.0
* @date         // 240628
* @brief        // 相关所有的头文件 All related header files
* @details      
* @par History  //
*               
*/


#ifndef __ALLHEADER_H
#define __ALLHEADER_H


//头文件 Header Files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "app_mode.h"
#include "myenum.h"

#include "delay.h"
#include "bsp.h"
#include "bsp_battery.h"
#include "bsp_beep.h"
#include "bsp_LED.h"
#include "bsp_timer.h"
#include "bsp_key.h"

//Usart
#include "usart.h"	

//bluetooth
#include "bsp_bluetooth.h"
#include "app_bluetooth.h"

//K210
#include "bsp_usart2.h"
#include "app_k210.h"
#include "app_k210_ai.h"
#include "app_line.h"
#include "app_follow.h"


//LIDAR
#include "bsp_lidar.h"
#include "app_lidar.h"
#include "app_lidar_car.h"

//OLED
#include "bsp_oled.h"
#include "bsp_oled_i2c.h"
#include "oled_show.h"

//ps2
#include "bsp_ps2.h"
#include "app_ps2.h"


//Mpu6050
#include "IOI2C.h"
#include "MPU6050.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

//Motor
#include "motor.h"
#include "encoder.h"
#include "app_motor.h"



//超声波 ultrasonic
#include "bsp_ultrasonic.h"

//4路循迹 infrared sensor 
#include "bsp_irtracking.h"
#include "app_tracking.h"

//电磁循迹 Electromagnetic sensor
#include "bsp_ele_track.h"
#include "app_ele_tracking.h"

//CCD
#include "bsp_ccd.h"
#include "app_ccd_tracking.h"

//平衡车整体控制 Balance car overall control
#include "app_control.h"
#include "pid_control.h"

//filtering alforithm
#include "filter.h"
#include "KF.h"




//CCD显示画面指针 CCD display screen pointer
extern u8 CCD_Zhongzhi,CCD_Yuzhi;
extern u8* CCDShowBuf;


//引出的通用变量 General variables introduced
extern float Velocity_Left,Velocity_Right; 								//轮子的速度 The speed of the wheels
extern uint8_t GET_Angle_Way;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波  Algorithm for obtaining angles, 1: Quaternion 2: Kalman 3: Complementary filtering
extern float Angle_Balance,Gyro_Balance,Gyro_Turn;     		//平衡倾角 平衡陀螺仪 转向陀螺仪 Balance tilt angle balance gyroscope steering gyroscope
extern int Motor_Left,Motor_Right;                 	  		//电机PWM变量 Motor PWM variable
extern int Temperature;                                		//温度变量 Temperature variable
extern float Acceleration_Z;                           		//Z轴加速度计  Z-axis accelerometer
extern int 	Mid_Angle;                          				//机械中值  Mechanical median
extern float Move_X,Move_Z;															//Move_X:前进速度（Forward speed）  Move_Z：转向速度(Turning speed)
extern float battery; 																	//电池电量	battery level 
extern u8 lower_power_flag; 														//低电压标志,电压恢复标志 Low voltage sign, voltage recovery sign
extern u32 g_distance; 																	//超声波距离值 Ultrasonic distance value
extern u8 Flag_velocity; 																//速度控制相关变量 Speed control related variables
extern enCarState g_newcarstate; 												//小车状态标志 Car status indicator
extern u8 Stop_Flag;																		//停止标志  Stop sign
extern  float Car_Target_Velocity,Car_Turn_Amplitude_speed; //前进速度 旋转速度  Forward speed and rotational speed

extern int Mid_Angle;																		//机械中值  Mechanical median

extern Car_Mode mode; 																	//模式选择  Mode selection

#endif


