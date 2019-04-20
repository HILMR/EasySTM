#ifndef __EasySTM32F103_H
#define __EasySTM32F103_H 

/*
	��EasySTM32F103-��׼�� ����˵����
	���⼯�ɷ�װ��STM32F103ϵ�е�Ƭ�����ֻ������ܣ������ã��������ţ�
	����Arduino�ı�̷�������ʺϴ�Arduino���׽���STM32��ѧϰ
	��Ҫ�����У�����������������������롢ģ�����롢PWM���������ͨ�š�
	��������ת�����ⲿ�жϡ���ʱ���ж�
	
���ߣ�LMR
�汾�ţ�V1.0
�������ڣ�2018-4-20
���� V1.0.1
�������ݣ���ʱ�����뵥λת����������ֹͣ

*/

#include "stm32f10x.h"

#include "stdio.h"
#include "stdlib.h"

//������źŶ�����
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


/*���Ź�����Ϣ��ѯ������
*/
GPIO_TypeDef* getGPIOX(u16 GPIO_Pin); //��ȡGPIO���A\B\C\D\E\F\G
u16 getGPIOP(u16 GPIO_Pin);//��ȡGPIO���ź� 0~15
TIM_TypeDef* getPWMTIM(u16 GPIO_Pin);//��ȡ���Ŷ�Ӧ��PWM��ʱ��
u8 getPWMCHN(u16 GPIO_Pin);//��ȡ���Ŷ�Ӧ��PWM��ʱ��ͨ��

//�������������

/*��pinMode������
	˵�����������ŵ�ʹ�÷�ʽ
	���ã�GPIO_Pin ���ź� ��A3
				GPIO_Mode ʹ�÷�ʽ 
				��ѡOUTPUT(���ֵ�ƽ���)��UINPUT(���ֵ�ƽ�������룬�����ոߵ�ƽ)��DINPUT(���ֵ�ƽ�������룬�����յ͵�ƽ)��AINPUT��ģ�����룩
*/
#define OUTPUT 1
#define UINPUT 2
#define DINPUT 3
#define AINPUT 4
void pinMode(u16 GPIO_Pin,u8 GPIO_Mode);

/*��digitalWrite������
	˵�����������ŵĸߵ͵�ƽ��HIGHΪ�ߣ�LOWΪ��
*/
#define HIGH 1
#define LOW 0
void digitalWrite(u16 GPIO_Pin,u8 DW_Mode);

/*��digitalRead������
	˵������ȡ���ŵĸߵ͵�ƽ������1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
*/
u8 digitalRead(u16 GPIO_Pin);

/*��ADCRead������
		˵������ȡģ��ֵ��ѹԭʼ�źţ�3.3��Ӧ4096
*/
u16 ADCRead(u16 GPIO_Pin);
/*��analogRead������
		˵������ȡ��ֵ�˲����ģ��ֵ�źţ�����ӳ����0~1023
*/
u16 analogRead(u16 GPIO_Pin);


//PWM������

/*��setPWM������
	˵��������PWM�������
				GPIO_Pin ���ź� ��A3
				PWM_MAX PWM���ֵ ��255
				PWM_CMP �������ã�PPWMΪ����NPWMΪ�����⽫Ӱ��VCC��GND���뷽ʽ
*/
#define PPWM 1
#define NPWM 0
void setPWM(u16 GPIO_Pin,u16 PWM_MAX,u8 PWM_CMP);

/*��analogWrite������
		˵�������PWMֵ
*/
void analogWrite(u16 GPIO_Pin,u16 PWM_VALUE);

//����ͨѶ������

/*��setSerial������
		˵�������ô���ͨ��
		SerialID ���ڱ�ţ�Ŀǰ֧��1~3
		bound ���ڲ���������
*/
void setSerial(u8 SerialID,u32 bound);

/*��Serialwrite������
		˵��������д�뵥һ����
*/
void Serialwrite(u8 SerialID,char Data);

/*��Serialprint������
		˵�������ڷ����ַ���
		SerialID ���ڱ��
		SData �ַ�����ע�ⲻ֧��ֱ���������͡������ͣ����ú���ת����������
*/
void Serialprint(u8 SerialID,char* SData);

/*��Serialread������
		˵�������ڽ��պ����������ַ��������ú���ת���õ����͡�������
		SerialID ���ڱ��
		SFlag ��ʼλ��Ǻţ�char��
*/
u8* Serialread(u8 SerialID,u8 SFlag);

void Serialclear(u8 SerialID);

/*����������ת����������
	˵����Ϊ���㴮�����ݽ���ת����ȡ�����ṩ���õ���������ת������������C��׼��"stdio.h"��"stdlib.h"
	int2str ��u32��������ת��Ϊ�ַ���������Serialprintֱ�ӶԽӣ�����stdio.h
	flo2str ��float��������ת��Ϊ�ַ��������������������룬����Serialprintֱ�ӶԽӣ�����stdio.h
	stringtoint ���������Խ��ַ���ת���ͺ���
	����Ȿ���ṩ�����ɽ��и��ḻ��ת��
	sprintf ��ʽ�����������Serialprintֱ�ӶԽ�ʵ��printf�����Ч��������stdio.h
	atof ���ַ���ת��Ϊ˫���ȸ�����ֵ������stdlib.h
	atoi ���ַ���ת��Ϊ˫��������ֵ������stdlib.h
	atol ���ַ���ת��Ϊ˫���ȳ�����ֵ������stdlib.h
*/
char* int2str(u32 oriint);
char* flo2str(float oriflo);
u32 stringtoint(char* str);

//�ж����ù�����

/*��attachInterrupt������
		˵�����ⲿ�ж�����
		GPIO_Pin ���ű��
		IPT_Mode �ж����ͣ�����RISING�������ش�������FALLING���½��ش�������CHANGE�����ش�����
		IPT_Pre����ռ���ȼ�����IPT_Sub����Ӧ���ȼ�����������жϵ���Ӧ˳�򣬾�Ϊ����ԽС���ȼ���Խ��
		��IPT_Pre�ֱ�IPT_Sub���ȼ��ߣ�ͬ����Ӧ��˭�ȴ���˭��Ӧ
*/
#define RISING 0
#define FALLING 1
#define CHANGE 2
void attachInterrupt(u16 GPIO_Pin,u8 IPT_Mode,u8 IPT_Pre,u8 IPT_Sub);

/*��Interruptclear������
		˵�����жϱ�־λ��������������ظ�����
*/
void Interruptclear(u16 GPIO_Pin);

/*��timerInterrupt������
		˵������ʱ���жϺ���
		TIMx ��ʱ����ţ�����TIM1,TIM2,TIM3,TIM4,TIM5(C8T6��)
		tdelta �жϼ��ʱ��
		sunit ��ʱ��ʱ�䵥λ��������TIMER_S������TIMER_MS��΢��TIMER_US
*/
#define TIMER_S 0
#define TIMER_MS 1
#define TIMER_US 2
void timerInterrupt(TIM_TypeDef* TIMx,u16 tdelta, u8 sunit);
/*��Timer_Start������
		˵������ʱ������
*/
void Timer_Start(TIM_TypeDef* TIMx);
	/*��Timer_End������
		˵������ʱ���ر�
*/
void Timer_End(TIM_TypeDef* TIMx);
	
#endif