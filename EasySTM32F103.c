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

#include "EasySTM32F103.h"
#include "delay.h"

#define SerialMAXBUF 32 //串口最大数据接收大小（字节）

GPIO_TypeDef* getGPIOX(u16 GPIO_Pin)
{
	switch ((int)(GPIO_Pin/100))
	{
		case 1:return GPIOA;break;
		case 2:return GPIOB;break;
		case 3:return GPIOC;break;
		case 4:return GPIOD;break;
		case 5:return GPIOE;break;
		case 6:return GPIOF;break;
		case 7:return GPIOG;break;
	}
}

u16 getGPIOP(u16 GPIO_Pin)
{
	switch(GPIO_Pin-(int)(GPIO_Pin/100)*100)
	{
		case 0:return GPIO_Pin_0;break;
		case 1:return GPIO_Pin_1;break;
		case 2:return GPIO_Pin_2;break;
		case 3:return GPIO_Pin_3;break;
		case 4:return GPIO_Pin_4;break;
		case 5:return GPIO_Pin_5;break;
		case 6:return GPIO_Pin_6;break;
		case 7:return GPIO_Pin_7;break;
		case 8:return GPIO_Pin_8;break;
		case 9:return GPIO_Pin_9;break;
		case 10:return GPIO_Pin_10;break;
		case 11:return GPIO_Pin_11;break;
		case 12:return GPIO_Pin_12;break;
		case 13:return GPIO_Pin_13;break;
		case 14:return GPIO_Pin_14;break;
		case 15:return GPIO_Pin_15;break;
	}
}

TIM_TypeDef* getPWMTIM(u16 GPIO_Pin)
{
	if((GPIO_Pin==108)||(GPIO_Pin==109)||(GPIO_Pin==110)||(GPIO_Pin==111))
		{
			return TIM1;
		}
		
	if((GPIO_Pin==100)||(GPIO_Pin==101)||(GPIO_Pin==102)||(GPIO_Pin==103))
		{
			return TIM2;
		}
	if((GPIO_Pin==106)||(GPIO_Pin==107)||(GPIO_Pin==200)||(GPIO_Pin==201))//PB4无法PWM
		{
			return TIM3;
		}
	if((GPIO_Pin==206)||(GPIO_Pin==207)||(GPIO_Pin==208)||(GPIO_Pin==209))
		{
			return TIM4;
		}
}

u8 getPWMCHN(u16 GPIO_Pin)
{
	if((GPIO_Pin==100)||(GPIO_Pin==106)||(GPIO_Pin==206)||(GPIO_Pin==108)) 
	{
		return 1;
	}
	if((GPIO_Pin==101)||(GPIO_Pin==107)||(GPIO_Pin==207)||(GPIO_Pin==205)||(GPIO_Pin==109)) 
	{
		return 2;
	}
	if((GPIO_Pin==102)||(GPIO_Pin==200)||(GPIO_Pin==208)||(GPIO_Pin==110))
	{
		return 3;
	}
	if((GPIO_Pin==103)||(GPIO_Pin==201)||(GPIO_Pin==209)||(GPIO_Pin==111)) 
	{
		return 4;
	}
}

void pinMode(u16 GPIO_Pin,u8 GPIO_Mode)
{	
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	switch ((int)(GPIO_Pin/100))
	{
		case 1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);break;
		case 2:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);break;
		case 3:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);break;
		case 4:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);break;
		case 5:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);break;
		case 6:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);break;
		case 7:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);break;
	}
	
	GPIO_InitStructure.GPIO_Pin=getGPIOP(GPIO_Pin);
	
	switch(GPIO_Mode)
	{
		case 1:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;break;
		case 2:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;break;
		case 3:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;break;
		case 4:GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;break;
	}
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(getGPIOX(GPIO_Pin), &GPIO_InitStructure);	
	
	if (GPIO_Mode==4)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1	, ENABLE );
		RCC_ADCCLKConfig(RCC_PCLK2_Div6);
		ADC_DeInit(ADC1);  //复位ADC1 
		
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
		ADC_InitStructure.ADC_NbrOfChannel = 16;	//顺序进行规则转换的ADC通道的数目
		ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
		
		ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
		ADC_ResetCalibration(ADC1);	//使能复位校准  
		while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
		ADC_StartCalibration(ADC1);	 //开启AD校准
		while(ADC_GetCalibrationStatus(ADC1));
	}
 
	
}

void digitalWrite(u16 GPIO_Pin,u8 DW_Mode)
{
	switch(DW_Mode)
	{
		case 0:GPIO_ResetBits(getGPIOX(GPIO_Pin),getGPIOP(GPIO_Pin));break;
		case 1:GPIO_SetBits(getGPIOX(GPIO_Pin),getGPIOP(GPIO_Pin));break;
	}
}

u8 digitalRead(u16 GPIO_Pin)
{
	return GPIO_ReadInputDataBit(getGPIOX(GPIO_Pin),getGPIOP(GPIO_Pin));
}


void setPWM(u16 GPIO_Pin,u16 PWM_MAX,u8 PWM_CMP)
{
	//结构体定义
	GPIO_InitTypeDef GPIO_InitStructure;
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//初始化GPIO
	switch ((int)(GPIO_Pin/100))
	{
		case 1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);break;
		case 2:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);break;
		case 3:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);break;
		case 4:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);break;
		case 5:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);break;
		case 6:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);break;
		case 7:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);break;
	}
	
	if(GPIO_Pin==205)
	{//此复用功能待修正，区分部分重映射和完全重映射
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	}

	
	GPIO_InitStructure.GPIO_Pin = getGPIOP(GPIO_Pin);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(getGPIOX(GPIO_Pin), &GPIO_InitStructure);
	
	//初始化定时器
		
	TIM_TimeBaseStructure.TIM_Period = PWM_MAX; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =0; //设置用来作为TIMx时钟频率除数的预分频值，目前采用【不分频】
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	
	
	//使能定时器
	if(getPWMTIM(GPIO_Pin)==TIM1){RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);}
	if(getPWMTIM(GPIO_Pin)==TIM2){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);}
	if(getPWMTIM(GPIO_Pin)==TIM3){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);}
	if(getPWMTIM(GPIO_Pin)==TIM4){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);}
			
		
	//初始化PWM模式
	if (PWM_CMP==1){TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;} //选择定时器模式:TIM脉冲宽度调制模式1
	if (PWM_CMP==0){TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;} //选择定时器模式:TIM脉冲宽度调制模式1
	
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	switch(getPWMCHN(GPIO_Pin))
	{
		case 1:TIM_OC1Init(getPWMTIM(GPIO_Pin), &TIM_OCInitStructure);TIM_OC1PreloadConfig(getPWMTIM(GPIO_Pin), TIM_OCPreload_Enable);break;
		case 2:TIM_OC2Init(getPWMTIM(GPIO_Pin), &TIM_OCInitStructure);TIM_OC2PreloadConfig(getPWMTIM(GPIO_Pin), TIM_OCPreload_Enable);break;
		case 3:TIM_OC3Init(getPWMTIM(GPIO_Pin), &TIM_OCInitStructure);TIM_OC3PreloadConfig(getPWMTIM(GPIO_Pin), TIM_OCPreload_Enable);break;
		case 4:TIM_OC4Init(getPWMTIM(GPIO_Pin), &TIM_OCInitStructure);TIM_OC4PreloadConfig(getPWMTIM(GPIO_Pin), TIM_OCPreload_Enable);break;
	}
	
	TIM_Cmd(getPWMTIM(GPIO_Pin), ENABLE);
	
	if (getPWMTIM(GPIO_Pin)==TIM1){TIM_CtrlPWMOutputs(TIM1, ENABLE); }//高级定时器功能
}

void analogWrite(u16 GPIO_Pin,u16 PWM_VALUE)
{
	switch(getPWMCHN(GPIO_Pin))
	{
		case 1: TIM_SetCompare1(getPWMTIM(GPIO_Pin),PWM_VALUE);break;
		case 2: TIM_SetCompare2(getPWMTIM(GPIO_Pin),PWM_VALUE);break;
		case 3: TIM_SetCompare3(getPWMTIM(GPIO_Pin),PWM_VALUE);break;
		case 4: TIM_SetCompare4(getPWMTIM(GPIO_Pin),PWM_VALUE);break;
	}
}

u16 ADCRead(u16 GPIO_Pin)   
{
	u8 ADCCHN;
	switch(GPIO_Pin)
	{
		case 100: ADCCHN=ADC_Channel_0;break;
		case 101: ADCCHN=ADC_Channel_1;break;
		case 102: ADCCHN=ADC_Channel_2;break;
		case 103: ADCCHN=ADC_Channel_3;break;
		case 104: ADCCHN=ADC_Channel_4;break;
		case 105: ADCCHN=ADC_Channel_5;break;
		case 106: ADCCHN=ADC_Channel_6;break;
		case 107: ADCCHN=ADC_Channel_7;break;
		case 200: ADCCHN=ADC_Channel_8;break;
		case 201: ADCCHN=ADC_Channel_9;break;
		case 300: ADCCHN=ADC_Channel_10;break;
		case 301: ADCCHN=ADC_Channel_11;break;
		case 302: ADCCHN=ADC_Channel_12;break;
		case 303: ADCCHN=ADC_Channel_13;break;
		case 304: ADCCHN=ADC_Channel_14;break;
		case 305: ADCCHN=ADC_Channel_15;break;
	}
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ADCCHN,1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 analogRead(u16 GPIO_Pin)  
{
	float temp_val=0;
	u8 t;
	u8 tt=0;
	for(t=0;t<10;t++)
	{
		u32 temp=ADCRead(GPIO_Pin);
		//均值滤波
		if (temp>4096){tt+=1;continue;}
		if ((t>0)&&(temp>(temp_val/(t-tt)*1.5))){tt+=1;continue;}
		if ((t>0)&&(temp<(temp_val/(t-tt)*0.5))){tt+=1;continue;}
		
		temp_val+=temp;
		delay_ms(5);
	}
	return temp_val/4096*1024/(10-tt);
} 

void setSerial(u8 SerialID,u32 bound)
{
	GPIO_InitTypeDef GPIO_STX;
	GPIO_InitTypeDef GPIO_SRX;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_TypeDef* GPIO_GRP;
	USART_TypeDef* USARTx;


	switch (SerialID)
	{
		case 1:{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
			GPIO_STX.GPIO_Pin=GPIO_Pin_9;
			GPIO_SRX.GPIO_Pin=GPIO_Pin_10;
			GPIO_GRP=GPIOA;
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			USARTx=USART1;
			break;
		}
		
		case 2:{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			GPIO_STX.GPIO_Pin=GPIO_Pin_2;
			GPIO_SRX.GPIO_Pin=GPIO_Pin_3;
			GPIO_GRP=GPIOA;
			NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
			USARTx=USART2;
			break;
		}
		case 3:{
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			GPIO_STX.GPIO_Pin=GPIO_Pin_10;
			GPIO_SRX.GPIO_Pin=GPIO_Pin_11;
			GPIO_GRP=GPIOB;
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
			USARTx=USART3;
			break;
		}
		
	}
	
	GPIO_STX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_SRX.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_STX.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_SRX.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIO_GRP, &GPIO_STX);
	GPIO_Init(GPIO_GRP, &GPIO_SRX);

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	USART_Init(USARTx, &USART_InitStructure); //初始化串口
	USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);//开启接收中断
  USART_Cmd(USARTx, ENABLE);                    //使能串口
	
}

void Serialwrite(u8 SerialID,char Data)
{
	switch(SerialID)
	{
		case 1:USART_SendData(USART1,Data);while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET){};break;
		case 2:USART_SendData(USART2,Data);while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET){};break;
		case 3:USART_SendData(USART3,Data);while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET){};break;
		
	}
	
}

void Serialprint(u8 SerialID,char* SData)
{

	while(0!=*SData)
		{
			Serialwrite(SerialID,*SData);
			SData++;
		}
}

char* int2str(u32 oriint)
{
	char buf[32],*temp;//【警告】必须对指针进行赋值，否则使用sprintf后将会进入死循环
	temp=buf;
	sprintf(buf,"%d",oriint);
	return temp;
}

char* flo2str(float oriflo)
{
	char buf[32],*temp;
	temp=buf;
	sprintf(buf,"%f",oriflo);
	return temp;
}

u32 stringtoint(char* str)
{
	char* ori=str;//记录初始指针地址
	u32 temp=0;
	u8 t=0;
	u32 ttemp;
	u8 tt;
	while(0!=*str)
		{
			t+=1;
			str++;
		}
		str=ori;//指针归位
		while(0!=*str)
		{
			t-=1;//一定注意，如果不减法就会逆序输出数字
			ttemp=*str-'0';
			tt=0;
			while(tt!=t)
			{
				tt+=1;
				ttemp=ttemp*10;
			}
			temp=temp+ttemp;
			str++;
		}	
	return temp;
}

u8 u1_res[SerialMAXBUF];//串口数据缓存池
u8 u2_res[SerialMAXBUF];
u8 u3_res[SerialMAXBUF];
u8 u1_flg=0;//起始位标记
u8 u2_flg=0;
u8 u3_flg=0;
u8 u1_bufid=0;//读取数据编号
u8 u2_bufid=0;
u8 u3_bufid=0;


void USART1_IRQHandler(void)
{
	 
	u1_res[u1_bufid]=USART_ReceiveData(USART1);//接收数据
	 
	 if (USART_ReceiveData(USART1)==u1_flg)//辨别数据的有效性
	 {
		  for(u1_bufid=0;u1_bufid<SerialMAXBUF;u1_bufid++)
	 {
		 u1_res[u1_bufid]=0;
	 }
	 u1_bufid=0;
	 //包含起始位标记
	 //u1_bufid=1;//数据归位清除
	 //u1_res[0]=USART_ReceiveData(USART1);
	 
	 }
	 else
	 {
	 u1_bufid++;
	 }
 }

void USART2_IRQHandler(void)
{
	 
	u2_res[u2_bufid]=USART_ReceiveData(USART2);//接收数据
	 
	 if (USART_ReceiveData(USART2)==u2_flg)//辨别数据的有效性
	 {
		  for(u2_bufid=0;u2_bufid<SerialMAXBUF;u2_bufid++)
	 {
		 u2_res[u2_bufid]=0;
	 }
	 u2_bufid=0;
	 /*包含起始位标记
	 u2_bufid=1;//数据归位清除
	 u2_res[0]=USART_ReceiveData(USART2);
	 */
	 }
	 else
	 {
	 u2_bufid++;
	 }
 }

void USART3_IRQHandler(void)
{
	 
	u3_res[u3_bufid]=USART_ReceiveData(USART3);//接收数据
	 
	 if (USART_ReceiveData(USART3)==u3_flg)//辨别数据的有效性
	 {
		  for(u3_bufid=0;u3_bufid<SerialMAXBUF;u3_bufid++)
	 {
		 u3_res[u3_bufid]=0;
	 }
	 u3_bufid=0;
	 /*包含起始位标记
	 u3_bufid=1;//数据归位清除
	 u3_res[0]=USART_ReceiveData(USART3);
	 */
	 }
	 else
	 {
	 u3_bufid++;
	 }
 }

 u8 * Serialread(u8 SerialID,u8 SFlag)
 {
	 switch(SerialID)
	 {
		 case 1: u1_flg=SFlag;return u1_res;
		 case 2: u2_flg=SFlag;return u2_res;
		 case 3: u3_flg=SFlag;return u3_res;
	 }
	 
 }
 
 void Serialclear(u8 SerialID)
 {
	 switch(SerialID)
	 {
		  case 1:
		 {
			 for(u1_bufid=0;u1_bufid<SerialMAXBUF;u1_bufid++)
			 {
				 u1_res[u1_bufid]=0;
			 }
			 u1_bufid=0;
	 
		 }
		  case 2:
		 {
			 for(u2_bufid=0;u2_bufid<SerialMAXBUF;u2_bufid++)
			 {
				 u2_res[u2_bufid]=0;
			 }
			 u2_bufid=0;
	 
		 }
		 case 3:
		 {
			 for(u3_bufid=0;u3_bufid<SerialMAXBUF;u3_bufid++)
			 {
				 u3_res[u3_bufid]=0;
			 }
			 u3_bufid=0;
	 
		 } 
	 }
 }
 
 void attachInterrupt(u16 GPIO_Pin,u8 IPT_Mode,u8 IPT_Pre,u8 IPT_Sub)
 {
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 u8 GPIO_PortSource_x=GPIO_Pin/100-1;
	 u8 GPIO_PinSource_x=GPIO_Pin-(GPIO_PortSource_x+1)*100;
	 u32 EXTI_Line_x;
	 EXTITrigger_TypeDef EXTITri_x;
	 
	 switch(GPIO_PinSource_x)
	 {
		 case 0:EXTI_Line_x=EXTI_Line0;break;
		 case 1:EXTI_Line_x=EXTI_Line1;break;
		 case 2:EXTI_Line_x=EXTI_Line2;break;
		 case 3:EXTI_Line_x=EXTI_Line3;break;
		 case 4:EXTI_Line_x=EXTI_Line4;break;
		 case 5:EXTI_Line_x=EXTI_Line5;break;
		 case 6:EXTI_Line_x=EXTI_Line6;break;
		 case 7:EXTI_Line_x=EXTI_Line7;break;
		 case 8:EXTI_Line_x=EXTI_Line8;break;
		 case 9:EXTI_Line_x=EXTI_Line9;break;
		 case 10:EXTI_Line_x=EXTI_Line10;break;
		 case 11:EXTI_Line_x=EXTI_Line11;break;
		 case 12:EXTI_Line_x=EXTI_Line12;break;
		 case 13:EXTI_Line_x=EXTI_Line13;break;
		 case 14:EXTI_Line_x=EXTI_Line14;break;
		 case 15:EXTI_Line_x=EXTI_Line15;break;
	 }
	 
	 switch(IPT_Mode)
	 {
		 case 0:EXTITri_x=EXTI_Trigger_Rising;break;
		 case 1:EXTITri_x=EXTI_Trigger_Falling;break;
		 case 2:EXTITri_x=EXTI_Trigger_Rising_Falling;break;
	 }
	 
	 pinMode(GPIO_Pin,DINPUT);
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

   GPIO_EXTILineConfig(GPIO_PortSource_x,GPIO_PinSource_x);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line_x;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTITri_x;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	 
	  if(GPIO_PinSource_x==0){NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;}
		if(GPIO_PinSource_x==1){NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;}
		if(GPIO_PinSource_x==2){NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;}
		if(GPIO_PinSource_x==3){NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;}
		if(GPIO_PinSource_x==4){NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;}
		if((GPIO_PinSource_x>=5)&&(GPIO_PinSource_x<=9)){NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;}
		if((GPIO_PinSource_x>=10)&&(GPIO_PinSource_x<=15)){NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;}
		
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IPT_Pre;	//抢占优先级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = IPT_Sub;					//子优先级
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);

 }
 
 void Interruptclear(u16 GPIO_Pin)
 {
	 u32 EXTI_Line_x;
	 switch(GPIO_Pin-GPIO_Pin/100*100)
	 {
		 case 0:EXTI_Line_x=EXTI_Line0;break;
		 case 1:EXTI_Line_x=EXTI_Line1;break;
		 case 2:EXTI_Line_x=EXTI_Line2;break;
		 case 3:EXTI_Line_x=EXTI_Line3;break;
		 case 4:EXTI_Line_x=EXTI_Line4;break;
		 case 5:EXTI_Line_x=EXTI_Line5;break;
		 case 6:EXTI_Line_x=EXTI_Line6;break;
		 case 7:EXTI_Line_x=EXTI_Line7;break;
		 case 8:EXTI_Line_x=EXTI_Line8;break;
		 case 9:EXTI_Line_x=EXTI_Line9;break;
		 case 10:EXTI_Line_x=EXTI_Line10;break;
		 case 11:EXTI_Line_x=EXTI_Line11;break;
		 case 12:EXTI_Line_x=EXTI_Line12;break;
		 case 13:EXTI_Line_x=EXTI_Line13;break;
		 case 14:EXTI_Line_x=EXTI_Line14;break;
		 case 15:EXTI_Line_x=EXTI_Line15;break;
	 }
	 EXTI_ClearITPendingBit(EXTI_Line_x);
 }
 
 void timerInterrupt(TIM_TypeDef* TIMx,u16 tdelta,u8 sunit)
 {
	 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 
	 u16 psc;
	 u16 arr;
	 switch(sunit)
	 {
		 case 0:psc=7199;arr=tdelta*10000;break;
		 case 1:psc=7199;arr=tdelta*10;break;
		 case 2:psc=35;arr=tdelta;break;
	 }

	if(TIMx==TIM1){RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);}
	if(TIMx==TIM2){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);}
	if(TIMx==TIM3){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);}
	if(TIMx==TIM4){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);}
	if(TIMx==TIM5){RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);}
	
	
	 //定时器初始化
	 TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	 TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	 TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	 TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	 TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置【警告】TIM1不设置将无法正常工作
	 TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	 TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE ); //允许更新中断
	 
	 //中断优先级NVIC设置
	 if(TIMx==TIM1){NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;}
	 if(TIMx==TIM2){NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;}
	 if(TIMx==TIM3){NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;}
	 if(TIMx==TIM4){NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;}
	 if(TIMx==TIM5){NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;}
	 
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	 NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

 }
 
void Timer_Start(TIM_TypeDef* TIMx)
{
	    TIM_Cmd(TIMx, ENABLE);	
}

void Timer_End(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx, DISABLE);	
	TIMx->CNT=0;
}


