#ifndef __Stepper_H
#define __Stepper_H 

#include "EasySTM32F103.h"

/*��EasySTM32F103-��������� ����˵����
ͨ��һ����ʱ���ķ��̴߳�������ʵ�ֶ�·��������Ķ�������
���ߣ�LMR
�汾�ţ�V1.0
�������ڣ�2019-3-20
*/

//�������װ�صĲ������������Ĭ��Ϊ6��������չ���
#define Stepper_SUM 6
//ע�⣬�������������ռ��һ����ʱ���������ﶨ����ʹ�õĶ�ʱ��
#define Stepper_Timer TIM2

/*������������ݽṹ�塿
���ڶ���һ�������������
*/
typedef struct
{
	u16 dir; //DIR���ţ�����
	u16 step; //STEP���ţ����壩
	u16 enable;//ENABLE���ţ�ʹ�ܣ�
	
	int t;//��ʱ��ʱ�̼�¼
	int T;//��������ڼ�¼
	u8 flag;//�ߵ�������
}Stepper;

/*����ʼ�����������
id ����������
pin_dir DIR����
pin_step STEP����
pin_enable ENABLE����
*/

void Stepper_Init(u8 id,u16 pin_dir,u16 pin_step,u16 pin_enable);
/*�����������ʱ��������رա�
���������ٿ���������ϵͳ���ܻ᲻�ȶ�
*/
void Stepper_TimerCMD(u8 state);

/*�����ò���������������
id ������
direction ����
*/
void Stepper_SetDir(u8 id,u8 direction);
/*�����ò�������ٶȲ�����
id ������
state �������״̬ Stepper_RUN���� Stepper_STOPֹͣ
Th ���������
*/
#define Stepper_RUN 0
#define Stepper_STOP 1
void Stepper_SetSpeed(u8 id,u8 state,int Th);
#endif