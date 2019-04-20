#ifndef __EasySTM32F103_H
#define __EasySTM32F103_H 

/*
	【EasySTM32F103-标准库 函数说明】
	本库集成封装了STM32F103系列单片机多种基本功能，简化设置，易于入门，
	贴近Arduino的编程风格，尤其适合从Arduino进阶进入STM32的学习
	主要功能有：数字输出、上下拉数字输入、模拟输入、PWM输出、串口通信、
	数据类型转换、外部中断、定时器中断
	
作者：LMR
版本号：V1.0
创建日期：2018-4-20
更新 V1.0.1
更新内容：计时器加入单位转换、启动和停止

*/

#include "stm32f10x.h"

#include "stdio.h"
#include "stdlib.h"

//快捷引脚号定义区
#define A0 100
#define A1 101
#define A2 102
#define A3 103
#define A4 104
#define A5 105
#define A6 106
#define A7 107
#define A8 108
#define A9 109
#define A10 110
#define A11 111
#define A12 112
#define A13 113
#define A14 114
#define A15 115
#define B0 200
#define B1 201
#define B2 202
#define B3 203
#define B4 204
#define B5 205
#define B6 206
#define B7 207
#define B8 208
#define B9 209
#define B10 210
#define B11 211
#define B12 212
#define B13 213
#define B14 214
#define B15 215
#define C0 300
#define C1 301
#define C2 302
#define C3 303
#define C4 304
#define C5 305
#define C6 306
#define C7 307
#define C8 308
#define C9 309
#define C10 310
#define C11 311
#define C12 312
#define C13 313
#define C14 314
#define C15 315
#define D0 400
#define D1 401
#define D2 402
#define D3 403
#define D4 404
#define D5 405
#define D6 406
#define D7 407
#define D8 408
#define D9 409
#define D10 410
#define D11 411
#define D12 412
#define D13 413
#define D14 414
#define D15 415
#define E0 500
#define E1 501
#define E2 502
#define E3 503
#define E4 504
#define E5 505
#define E6 506
#define E7 507
#define E8 508
#define E9 509
#define E10 510
#define E11 511
#define E12 512
#define E13 513
#define E14 514
#define E15 515
#define F0 600
#define F1 601
#define F2 602
#define F3 603
#define F4 604
#define F5 605
#define F6 606
#define F7 607
#define F8 608
#define F9 609
#define F10 610
#define F11 611
#define F12 612
#define F13 613
#define F14 614
#define F15 615
#define G0 700
#define G1 701
#define G2 702
#define G3 703
#define G4 704
#define G5 705
#define G6 706
#define G7 707
#define G8 708
#define G9 709
#define G10 710
#define G11 711
#define G12 712
#define G13 713
#define G14 714
#define G15 715


/*引脚归属信息查询函数区
*/
GPIO_TypeDef* getGPIOX(u16 GPIO_Pin); //获取GPIO组别，A\B\C\D\E\F\G
u16 getGPIOP(u16 GPIO_Pin);//获取GPIO引脚号 0~15
TIM_TypeDef* getPWMTIM(u16 GPIO_Pin);//获取引脚对应的PWM定时器
u8 getPWMCHN(u16 GPIO_Pin);//获取引脚对应的PWM定时器通道

//输入输出功能区

/*【pinMode函数】
	说明：设置引脚的使用方式
	调用：GPIO_Pin 引脚号 如A3
				GPIO_Mode 使用方式 
				可选OUTPUT(数字电平输出)、UINPUT(数字电平上拉输入，即浮空高电平)、DINPUT(数字电平下拉输入，即浮空低电平)、AINPUT（模拟输入）
*/
#define OUTPUT 1
#define UINPUT 2
#define DINPUT 3
#define AINPUT 4
void pinMode(u16 GPIO_Pin,u8 GPIO_Mode);

/*【digitalWrite函数】
	说明：设置引脚的高低电平，HIGH为高，LOW为低
*/
#define HIGH 1
#define LOW 0
void digitalWrite(u16 GPIO_Pin,u8 DW_Mode);

/*【digitalRead函数】
	说明：读取引脚的高低电平，返回1为高电平，0为低电平
*/
u8 digitalRead(u16 GPIO_Pin);

/*【ADCRead函数】
		说明：读取模拟值电压原始信号，3.3对应4096
*/
u16 ADCRead(u16 GPIO_Pin);
/*【analogRead函数】
		说明：读取均值滤波后的模拟值信号，且已映射至0~1023
*/
u16 analogRead(u16 GPIO_Pin);


//PWM功能区

/*【setPWM函数】
	说明：设置PWM输出引脚
				GPIO_Pin 引脚号 如A3
				PWM_MAX PWM最大值 如255
				PWM_CMP 反置设置，PPWM为正向，NPWM为反向，这将影响VCC与GND接入方式
*/
#define PPWM 1
#define NPWM 0
void setPWM(u16 GPIO_Pin,u16 PWM_MAX,u8 PWM_CMP);

/*【analogWrite函数】
		说明：输出PWM值
*/
void analogWrite(u16 GPIO_Pin,u16 PWM_VALUE);

//串口通讯功能区

/*【setSerial函数】
		说明：设置串口通信
		SerialID 串口编号，目前支持1~3
		bound 串口波特率设置
*/
void setSerial(u8 SerialID,u32 bound);

/*【Serialwrite函数】
		说明：串口写入单一数据
*/
void Serialwrite(u8 SerialID,char Data);

/*【Serialprint函数】
		说明：串口发送字符串
		SerialID 串口编号
		SData 字符串，注意不支持直接输入整型、浮点型，请用函数转换后再输入
*/
void Serialprint(u8 SerialID,char* SData);

/*【Serialread函数】
		说明：串口接收函数，返回字符串，请用函数转换得到整型、浮点型
		SerialID 串口编号
		SFlag 起始位标记号（char）
*/
u8* Serialread(u8 SerialID,u8 SFlag);

void Serialclear(u8 SerialID);

/*【数据类型转换函数区】
	说明：为方便串口数据进行转换读取，特提供常用的数据类型转换函数，依赖C标准库"stdio.h"及"stdlib.h"
	int2str 将u32整型数据转换为字符串，可与Serialprint直接对接，依赖stdio.h
	flo2str 将float浮点数据转换为字符串，超出部分四舍五入，可与Serialprint直接对接，依赖stdio.h
	stringtoint 不依赖库自建字符串转整型函数
	另外库本身提供函数可进行更丰富的转换
	sprintf 格式化输出，可与Serialprint直接对接实现printf的输出效果，依赖stdio.h
	atof 将字符串转换为双精度浮点型值，依赖stdlib.h
	atoi 将字符串转换为双精度整型值，依赖stdlib.h
	atol 将字符串转换为双精度长整型值，依赖stdlib.h
*/
char* int2str(u32 oriint);
char* flo2str(float oriflo);
u32 stringtoint(char* str);

//中断设置功能区

/*【attachInterrupt函数】
		说明：外部中断设置
		GPIO_Pin 引脚编号
		IPT_Mode 中断类型，包括RISING（上升沿触发）、FALLING（下降沿触发）、CHANGE（边沿触发）
		IPT_Pre（抢占优先级）与IPT_Sub（响应优先级）负责管理中断的响应顺序，均为数字越小优先级别越高
		且IPT_Pre又比IPT_Sub优先级高，同级响应则谁先触发谁响应
*/
#define RISING 0
#define FALLING 1
#define CHANGE 2
void attachInterrupt(u16 GPIO_Pin,u8 IPT_Mode,u8 IPT_Pre,u8 IPT_Sub);

/*【Interruptclear函数】
		说明：中断标志位清除函数，避免重复触发
*/
void Interruptclear(u16 GPIO_Pin);

/*【timerInterrupt函数】
		说明：定时器中断函数
		TIMx 定时器编号，包括TIM1,TIM2,TIM3,TIM4,TIM5(C8T6无)
		tdelta 中断间隔时间
		sunit 计时的时间单位，包含秒TIMER_S、毫秒TIMER_MS、微秒TIMER_US
*/
#define TIMER_S 0
#define TIMER_MS 1
#define TIMER_US 2
void timerInterrupt(TIM_TypeDef* TIMx,u16 tdelta, u8 sunit);
/*【Timer_Start函数】
		说明：定时器启动
*/
void Timer_Start(TIM_TypeDef* TIMx);
	/*【Timer_End函数】
		说明：定时器关闭
*/
void Timer_End(TIM_TypeDef* TIMx);
	
#endif