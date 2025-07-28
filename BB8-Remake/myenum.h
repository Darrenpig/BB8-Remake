#ifndef __MYENUM_H_
#define __MYENUM_H_


////JTAG模式设置定义 JTAG mode setting definition
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00



//For specific implementation ideas, refer to Chapter 5 (pages 87 to 92) of <<CM3 Authoritative Guide>>.
//IO port operation macro definition
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射    IO port address mapping
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO port operation, only for a single IO port!
//Make sure the value of n is less than 16!
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 Output
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 Input

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 Output
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 Input

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 Output
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 Input

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 Output
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 Input

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 Output
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入 Input

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 Output
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入 Input

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 Output
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入 Input

//电机
//Motor ML MR
typedef enum {
    MOTOR_ID_ML = 0,
    MOTOR_ID_MR,
    MAX_MOTOR
} Motor_ID;

/*小车运行状态枚举 Car running status enumeration */
typedef enum enCarState_t{
  enSTOP = 0,
  enRUN,
  enBACK,
  enLEFT,
  enRIGHT,
  enTLEFT,
  enTRIGHT,
	
	//ps2模拟值生效 ps2 simulation value takes effect
	enps2Fleft, //前左旋  Front left turn
	enps2Fright,//前右旋  Front right turn
	enps2Bleft, //后左旋  Back left turn
	enps2Bright,//后右旋  Back right turn
	
	enAvoid, //超声波躲避  Ultrasonic avoidance
	enFollow, //超声波跟随  Ultrasonic Follow
	enError
}enCarState;


typedef enum Car_mode_t{
	
	
	Normal, //正常模式,包含蓝牙控制 //Normal mode, including Bluetooth controlled 
	U_Follow,//超声波跟随   //Ultrasonic Follow
	U_Avoid, //超声波避障   //Ultrasonic obstacle avoidance
	Weight_M,//负重模式     //Load bearing mode
	PS2_Control,//ps2控制  //PS2 control
	
	Line_Track,//4路巡线   //4-way patrol line
	Diff_Line_track, //高难度4路巡线  High-difficulty 4-way patrol
  	
	K210_QR,//k210识别二维码  //K210 recognition QR code
	K210_Line,//k210巡线      //K210 patrol line
	K210_Follow,//k210跟随    //K210 Follow
	K210_SelfLearn,//k210自主学习  需要KPU模型  //K210 autonomous learning requires KPU model
	K210_mnist,//k210识别数字  需要KPU模型      //K210 requires KPU model to recognize numbers
	
	LiDar_avoid,//雷达避障   //Radar obstacle avoidance
	LiDar_Follow,//雷达跟随  //Radar Follow
	LiDar_aralm,//雷达警卫   //Radar Guard
	LiDar_Patrol,//雷达巡逻  //Radar patrol
	LiDar_Line, //雷达巡墙边做直线  //Make a straight line around the radar wall
	LiDar_wall_Line, //雷达沿着墙边走  //The radar is walking along the wall
	
	CCD_Mode,//ccd巡线     //CCD patrol line
	ElE_Mode,//电磁巡线    //Electromagnetic patrol line
	
	Mode_Max //最后模式的界限 如果要增加模式，在雷达避障前添加新模式  //If the boundary of the final mode needs to be increased, add a new mode before radar obstacle avoidance
	
	
}Car_Mode;


#endif

