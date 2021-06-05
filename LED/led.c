#include "led.h"

char LED_Status = 0;


void LEDConfig(void){
	//Enable clock for GPOIA
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//PA0
	GPIO_InitTypeDef	GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

char readLEDStatus(void){
	B1.LED_Status = (GPIOD->ODR&(0x0F000))>>12;
	LED_Status = (B1.LED_Status)|(B2.LED_Status);
	return LED_Status;
}
