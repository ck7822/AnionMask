#include "SysTick.h"
#include "stm32f0xx.h"


static uint8_t  fac_us=0;//us��ʱ������
static uint16_t fac_ms=0;//ms��ʱ������

/*************************************************
����: void SysTick_Init(uint8_t SYSCLK)
����: �δ�ʱ����ʼ��
����: SYSCLK:ϵͳʱ��,Cotex-M0���ʱ��Ϊ48MHz
����: SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
**************************************************/
void SysTick_Init(uint8_t SYSCLK)
{
//	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick->CTRL = 0xfffffffb;	// �رն�ʱ��,����ʱ������0ʱ�����쳣,ѡ���ⲿʱ��Դ
	
	fac_us=SYSCLK/8;		    
	fac_ms=(uint16_t)fac_us*1000;
}



/*************************************************
����: void delay_ms(uint16_t nms)
����: ������ʱ
����: ��ʱn����
����: ��
**************************************************/
void delay_ms(uint16_t nms)
{
	uint32_t temp;
	
	SysTick->LOAD = (uint32_t)nms*fac_ms;	//װ�ؼ���ֵ
	SysTick->VAL = 0x00;					//��ռ�����
	SysTick->CTRL = 0x01;					//������ʼ
	
	do
	{
		temp = SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ���ʱ����
	
	SysTick->CTRL = 0x00;					//�رռ�����
	SysTick->VAL = 0x00;					//��ռ�����
}

/*************************************************
����: void delay_us(uint16_t nus)
����: ΢����ʱ
����: ��ʱn΢��
����: ��
**************************************************/
void delay_us(uint16_t nus)
{
	uint32_t temp;
	
	SysTick->LOAD = (uint32_t)nus*fac_us;	//װ�ؼ���ֵ
	SysTick->VAL = 0x00;					//��ռ�����
	SysTick->CTRL = 0x01;					//������ʼ
	
	do
	{
		temp = SysTick->CTRL;
	}
	while((temp&0x01)&&(!(temp&(1<<16))));	//�ȴ���ʱ����
	
	SysTick->CTRL = 0x00;					//�رռ�����
	SysTick->VAL = 0x00;					//��ռ�����
}






