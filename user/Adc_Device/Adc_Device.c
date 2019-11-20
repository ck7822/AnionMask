#include "Adc_Device.h"

__IO uint16_t ADC_ConvertedValue[50][2];//�������ADCת�������Ҳ��DMA��Ŀ���ַ
__IO uint16_t After_filter[2];    //���������ƽ��ֵ֮��Ľ��


void ADC_Mode_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef     ADC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//Select ADC Channel
	ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_239_5Cycles);
	
//	ADC_ContinuousModeCmd(ADC1, ENABLE);
	
	//Calibration ADC.
	ADC_GetCalibrationFactor(ADC1);
	
	//use DMA Circular Mode
	ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
	
	//Enable ADC
	ADC_Cmd(ADC1, ENABLE);
	//Wait Ready flag 
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY) == SET);
	//StartUp Conversion for the selected ADC channels
	ADC_StartOfConversion(ADC1);
	//Enable DMA
	ADC_DMACmd(ADC1, ENABLE);
}

void DMA_InitConfig(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;//�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//��ȡ��������
	DMA_InitStructure.DMA_BufferSize = 50*2;//���鳤��/�ڴ泤��50������λ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݿ��Ϊ����(16Bit)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�ڴ����ݿ��Ϊ����(16Bit)
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�����ȼ�
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�����ڴ浽�ڴ�İ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);//ʹ��DMA
}

void ADC_InitConfig(void)
{
	DMA_InitConfig();
	ADC_Mode_InitConfig();
}

/****************************************************
**�������ܣ���ȡADC�ɼ�ƽ��ֵ
*****************************************************/
void filter(uint8_t num)
{
	uint8_t i = 0;
//	uint16_t ret = 0;
	uint32_t Sum_Value = 0;
	
	for(i = 0;i < 50;i++)
		Sum_Value += ADC_ConvertedValue[i][num];
	
	After_filter[num] = (uint16_t)(Sum_Value/50);
}
/*
**�������ܣ���ȡXͨ��ADֵ��0~1023��
**����    ��channel---ģ���ͨ����
**����ȡֵ��	3~4
*/
uint16_t Get_Adc(uint8_t channel)
{
	uint8_t ch = 0;
	
	if(channel == 3)
		ch = 1;
	else if(channel == 4)
		ch = 0;
	else return 0;
	
	while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
	
 	filter(ch);
	return 	After_filter[ch];
}

/****************************************************
**�������ܣ�����ADC�ɼ���ѹֵ
*****************************************************/
float Get_Voltage(uint16_t adc_value)
{
	uint16_t temp = adc_value;
	float Value;

	Value = (float)temp * (3.3 / 4096);
//	return (float)(((Get_ADC_Value()* 3300) / 0xFFF) / 1000);
//	return (float)(((temp* 3300) / 0xFFF));
	return Value;
}

//BAT*R = 2R*V
float Get_BattryVoltage(void)
{
	return 2.0*Get_Voltage(Get_Adc(3));
}

