#ifndef __Stepper_H
#define __Stepper_H 

#include "EasySTM32F103.h"

/*【EasySTM32F103-步进电机库 函数说明】
通过一个定时器的分线程处理，可以实现多路步进电机的独立驱动
作者：LMR
版本号：V1.0
创建日期：2019-3-20
*/

//定义最大装载的步进电机数量，默认为6个，可扩展添加
#define Stepper_SUM 6
//注意，步进电机驱动会占用一个定时器，在这里定义所使用的定时器
#define Stepper_Timer TIM2

/*【步进电机数据结构体】
用于定义一个步进电机对象
*/
typedef struct
{
	u16 dir; //DIR引脚（方向）
	u16 step; //STEP引脚（脉冲）
	u16 enable;//ENABLE引脚（使能）
	
	int t;//定时器时刻记录
	int T;//脉冲半周期记录
	u8 flag;//高低脉冲标记
}Stepper;

/*【初始化步进电机】
id 步进电机编号
pin_dir DIR引脚
pin_step STEP引脚
pin_enable ENABLE引脚
*/

void Stepper_Init(u8 id,u16 pin_dir,u16 pin_step,u16 pin_enable);
/*【步进电机定时器开启与关闭】
建议启用再开启，否则系统可能会不稳定
*/
void Stepper_TimerCMD(u8 state);

/*【设置步进电机方向参数】
id 电机编号
direction 方向
*/
void Stepper_SetDir(u8 id,u8 direction);
/*【设置步进电机速度参数】
id 电机编号
state 步进电机状态 Stepper_RUN运行 Stepper_STOP停止
Th 脉冲半周期
*/
#define Stepper_RUN 0
#define Stepper_STOP 1
void Stepper_SetSpeed(u8 id,u8 state,int Th);
#endif