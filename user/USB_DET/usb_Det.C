#include "usb_Det.h"


/*****************************************************************
**�������ܣ�usb���ϵ���GPIO��ʼ��
******************************************************************/
void usb_GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int usb_check(void)
{
	if(1 == usb_State)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

