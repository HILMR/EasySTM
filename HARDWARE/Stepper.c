#include "Stepper.h"
//步进电机时间计数
int Stepper_Count=0;
//步进电机列表
Stepper Stepper_LIST[Stepper_SUM];
//定时器中断，这里使用TIM2定时器
void TIM2_IRQHandler(void)
{
	u8 i=0;
	
	if ( TIM_GetITStatus(Stepper_Timer,TIM_IT_Update) != RESET ) 
	{	
		
		//循环计数算法
		if(Stepper_Count>=2147483647)
		{//溢出归零
			Stepper_Count=0;
			//溢出后对已有时刻的补差，因此这里得用int而不是u16
			for(i=0;i<Stepper_SUM;i++)
			{
				if (Stepper_LIST[i].T!=0)
				{
				Stepper_LIST[i].t=Stepper_LIST[i].t-2147483646;//注意是2147483646不是2147483647
				}
			}
		}
		else
		{
			Stepper_Count++;
		}
		
		//脉冲生成
		for(i=0;i<Stepper_SUM;i++)
			{
				//核心算法
				if ((Stepper_LIST[i].T!=0)&&((Stepper_Count-Stepper_LIST[i].t)>=Stepper_LIST[i].T))
				{
					if(Stepper_LIST[i].flag==0)
					{
						digitalWrite(Stepper_LIST[i].step,HIGH);
						Stepper_LIST[i].flag=1;
					}
					else
					{
						digitalWrite(Stepper_LIST[i].step,LOW);
						Stepper_LIST[i].flag=0;
					}
					//记录时刻点
					Stepper_LIST[i].t=Stepper_Count;
				}
			}
		//清除中断标记
		TIM_ClearITPendingBit(Stepper_Timer,TIM_FLAG_Update);  	
		
}
}
//初始化函数
void Stepper_Init(u8 id,u16 pin_dir,u16 pin_step,u16 pin_enable)
{
	Stepper_LIST[id].dir=pin_dir;
	Stepper_LIST[id].step=pin_step;
	Stepper_LIST[id].enable=pin_enable;
	
	pinMode(Stepper_LIST[id].dir,OUTPUT);
	pinMode(Stepper_LIST[id].step,OUTPUT);
	pinMode(Stepper_LIST[id].enable,OUTPUT);
	//启动定时器，尺度为1us（实际大于1us）
	timerInterrupt(Stepper_Timer,1,TIMER_US);
}

void Stepper_TimerCMD(u8 state)
{
	switch(state)
	{
		case 0:Timer_End(Stepper_Timer);break;
		case 1:Timer_Start(Stepper_Timer);break;
	}
}

//方向控制
void Stepper_SetDir(u8 id,u8 direction)
{
	digitalWrite(Stepper_LIST[id].dir,direction);
}
//速度控制
void Stepper_SetSpeed(u8 id,u8 state,int Th)
{	
	digitalWrite(Stepper_LIST[id].enable,state);	
	if((state==0)&&(Th!=0))
		{
		Stepper_LIST[id].T=Th;
	}
	else
	{
		Stepper_LIST[id].T=0;
	}
}