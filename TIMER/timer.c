#include "timer.h"

void ITTimer_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_ClockDivision 				= TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_Prescaler 						= 8400-1;
	//TIM_TimeBaseStructure.TIM_Period 								= (int)(Ts*10000)-1; //10ms
	TIM_TimeBaseStructure.TIM_Period 								= 199; //20ms
	TIM_TimeBaseStructure.TIM_CounterMode 					= TIM_CounterMode_Up;
 	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
//	TIM_Cmd(TIM3,ENABLE);
	
	NVIC_InitTypeDef					NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel 										= TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority					= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void DLTimer_Config(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_DLBaseStruct;
	TIM_DLBaseStruct.TIM_Prescaler = 83;
	TIM_DLBaseStruct.TIM_Period = 999; //delay 1ms
	TIM_DLBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_DLBaseStruct.TIM_ClockDivision = 0;
	TIM_DLBaseStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM6, &TIM_DLBaseStruct);
	TIM_UpdateDisableConfig(TIM6, DISABLE);
	TIM_ARRPreloadConfig(TIM6, ENABLE);
}

void delay_ms(uint32_t milliSeconds){
	while (milliSeconds--){
		TIM_SetCounter(TIM6, 0);
		TIM_Cmd(TIM6, ENABLE);
		while (TIM_GetFlagStatus(TIM6, TIM_FLAG_Update) != SET);
		TIM_Cmd(TIM6, DISABLE);
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);
	}
}

void delay_us(uint32_t microSeconds){
	TIM_SetCounter(TIM6, 0);
	TIM_Cmd(TIM6, ENABLE);
	while (TIM_GetCounter(TIM6) < microSeconds);
	TIM_Cmd(TIM6, DISABLE);
}
