#include "Stepper.h"
//�������ʱ�����
int Stepper_Count=0;
//��������б�
Stepper Stepper_LIST[Stepper_SUM];
//��ʱ���жϣ�����ʹ��TIM2��ʱ��
void TIM2_IRQHandler(void)
{
	u8 i=0;
	
	if ( TIM_GetITStatus(Stepper_Timer,TIM_IT_Update) != RESET ) 
	{	
		
		//ѭ�������㷨
		if(Stepper_Count>=2147483647)
		{//�������
			Stepper_Count=0;
			//����������ʱ�̵Ĳ������������int������u16
			for(i=0;i<Stepper_SUM;i++)
			{
				if (Stepper_LIST[i].T!=0)
				{
				Stepper_LIST[i].t=Stepper_LIST[i].t-2147483646;//ע����2147483646����2147483647
				}
			}
		}
		else
		{
			Stepper_Count++;
		}
		
		//��������
		for(i=0;i<Stepper_SUM;i++)
			{
				//�����㷨
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
					//��¼ʱ�̵�
					Stepper_LIST[i].t=Stepper_Count;
				}
			}
		//����жϱ��
		TIM_ClearITPendingBit(Stepper_Timer,TIM_FLAG_Update);  	
		
}
}
//��ʼ������
void Stepper_Init(u8 id,u16 pin_dir,u16 pin_step,u16 pin_enable)
{
	Stepper_LIST[id].dir=pin_dir;
	Stepper_LIST[id].step=pin_step;
	Stepper_LIST[id].enable=pin_enable;
	
	pinMode(Stepper_LIST[id].dir,OUTPUT);
	pinMode(Stepper_LIST[id].step,OUTPUT);
	pinMode(Stepper_LIST[id].enable,OUTPUT);
	//������ʱ�����߶�Ϊ1us��ʵ�ʴ���1us��
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

//�������
void Stepper_SetDir(u8 id,u8 direction)
{
	digitalWrite(Stepper_LIST[id].dir,direction);
}
//�ٶȿ���
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