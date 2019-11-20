#include "Bluetooth.h"
#include "usart_device.h"
#include "ST_string.h"

/**********************************************************
**�������ܣ�WIFI ���Žӿڶ��壬��ʼ��
**B_IO0--------------PF1
**B_IO6--------------X
**B_RES--------------NRST
**B_EN---------------PA6
***********************************************************/
void Bluetooth_RF_BM_S02_Port_GPIO_Init(void)
{
	//����һ��GPIO_InitTypeDef���͵Ľṹ��
	GPIO_InitTypeDef GPIO_InitStructure;

	//����GPIOB������ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE); 

	//B_IO0-------PB15------�ָ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	//B_IO6-------PA5------����״ָ̬ʾ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
/*
	//B_RES-------F1------��λ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
*/
	//B_EN--------PA6------ʹ�ܷ��͹㲥
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//BRTS--------PB1------���ݷ������� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	//BCTS--------PA7------���������ź�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);
}

void Bluetooth_Sendmsg(uint8_t data[],uint8_t len)
{
	int i = 0;
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	//usart1_putstr("hello Bluetooth",st_strlen("hello Bluetooth"));
	for(i=0;i<len;i++)
	{
		usart1_putc(data[i]);
		//printf("%c",data_to_Bluetooth[i]);
	}
	//printf("\r\n");
	//delay_ms(5);
	//BRTS_State(GPIO_OUT_HIGH);
	//delay_ms(100);
	
	//return len; 
}

#define USART3_DEBUG

/**********************************************************
**�������ܣBBluetooth_RF_BM_S02�޸���������
***********************************************************/
void Bluetooth_RF_BM_S02_change_name(uint32_t id)
{
	unsigned char BLE_NAME[23];
	
	sprintf((char*)BLE_NAME,"TTM:REN-CLEANIE-A95-%d",id);
	Clear_USART_Buff(USART1_BUF);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	usart1_putstr(BLE_NAME,st_strlen((char*)BLE_NAME));
	delay_ms(5);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(100);
	
	//printf("change name��%s\r\n",Usart1_buff);
	Clear_USART_Buff(USART1_BUF);
#if 0
	while(st_strcmp(Usart1_buff,"TTM:REN-CLEANIE-A95\r\nTTM:OK\r\n\0") != 0)
	{
		printf("%s\r\n",Usart1_buff);
		Clear_USART_Buff(USART1_BUF);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(2);
		usart1_putstr("TTM:REN-CLEANIE-A95",st_strlen("TTM:REN-CLEANIE-A95"));
		delay_ms(5);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(1000);	
#ifdef USART3_DEBUG		
		printf("Bluetooth�޸�����failed��\r\n");
#endif		
	}
	Clear_USART_Buff(USART1_BUF);
#ifdef USART3_DEBUG
	printf("Bluetooth�޸�����OK��\r\n");
#endif

#endif
}
/**********************************************************
**�������ܣBBluetooth_RF_BM_S02�������ݵ�H5����
***********************************************************/
void Bluetooth_RF_BM_S02_MSGto_H5(void)
{		
	Clear_USART_Buff(USART1_BUF);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	usart1_putstr("TTM:HT5-ON",st_strlen("TTM:HT5-ON"));
	delay_ms(5);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(100);
	
	//printf("change name��%s\r\n",Usart1_buff);
	Clear_USART_Buff(USART1_BUF);
}
/**********************************************************
**�������ܣBBluetooth_RF_BM_S02��ȡMAC��ַ
***********************************************************/
void Bluetooth_RF_BM_S02_getMAC(void)
{
	Clear_USART_Buff(USART1_BUF);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	usart1_putstr("TTM:MAC-?",st_strlen("TTM:MAC-?"));
	delay_ms(5);
	BRTS_State(GPIO_OUT_HIGH);
	delay_ms(100);
#if 0
	while(st_strcmp(Usart1_buff,"TTM:MAC-?\r\nTTM:OK\r\n\0") != 0)
	{
		printf("%s\r\n",Usart1_buff);
		Clear_USART_Buff(USART1_BUF);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(2);
		usart1_putstr("TTM:REN-CLEANIE-A95",st_strlen("TTM:REN-CLEANIE-A95"));
		delay_ms(5);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(1000);	
#ifdef USART3_DEBUG		
		printf("Bluetooth�޸�����failed��\r\n");
#endif		
	}
	
	Clear_USART_Buff(USART1_BUF);
#ifdef USART3_DEBUG
	printf("Bluetooth�޸�����OK��\r\n");
#endif

#endif
}

/**********************************************************
**�������ܣBBluetooth_RF_BM_S02�޸Ĳ�����
***********************************************************/
void Bluetooth_RF_BM_S02_change_BPS(void)
{
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	usart1_putstr("TTM:BPS-115200",st_strlen("TTM:BPS-115200"));
	delay_ms(5);
	BRTS_State(GPIO_OUT_HIGH);
	delay_ms(100);
#if 0
	
	while(st_strcmp(Usart1_buff,"TTM:OK\r\n\0") != 0)
	{
		Clear_USART_Buff(USART1_BUF);
		delay_ms(1000);	
#ifdef USART3_DEBUG		
		printf("Bluetooth�޸Ĳ�����failed��\r\n");
#endif		
	}
	Clear_USART_Buff(USART1_BUF);
#ifdef USART3_DEBUG
	printf("Bluetooth�޸Ĳ�����OK��\r\n");
#endif
	
#endif
}


/**********************************************************
**�������ܣBBluetooth_RF_BM_S02�޸����Ӽ��ʱ��
***********************************************************/
void Bluetooth_RF_BM_S02_change_Connect_time(void)
{
	Clear_USART_Buff(USART1_BUF);
	BRTS_State(GPIO_OUT_LOW);
	delay_ms(2);
	usart1_putstr("TTM:CIT-100ms",st_strlen("TTM:CIT-100ms"));
	delay_ms(5);
	BRTS_State(GPIO_OUT_HIGH);
	delay_ms(100);
	printf("%s\r\n",Usart1_buff);
	Clear_USART_Buff(USART1_BUF);
#if 0
	while(st_strcmp(Usart1_buff,"TTM:CIT-20ms\r\nTTM:OK\r\n\0") != 0)
	{
		Clear_USART_Buff(USART1_BUF);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(2);
		usart1_putstr("TTM:CIT-20ms",st_strlen("TTM:CIT-20ms"));
		delay_ms(5);
		BRTS_State(GPIO_OUT_LOW);
		delay_ms(1000);	
#ifdef USART3_DEBUG		
		printf("Bluetooth�޸����Ӽ��ʱ��failed��\r\n");
#endif		
	}
	Clear_USART_Buff(USART1_BUF);
#ifdef USART3_DEBUG
	printf("Bluetooth�޸����Ӽ��ʱ��OK��\r\n");
#endif
	
#endif
}


/**********************************************************
**�������ܣBBluetooth_RF_BM_S02��������ģʽ
***********************************************************/
void Bluetooth_RF_BM_S02_Connect_Mode(void)
{
	BM_S02_EN(GPIO_OUT_LOW);
#ifdef USART3_DEBUG
	//printf("Bluetooth��������ģʽOK\r\n");
#endif
}

/**********************************************************
**�������ܣBBluetooth_RF_BM_S02����͹���ģʽ������˯��ģʽ
***********************************************************/
void Bluetooth_RF_BM_S02_Sleep_Mode(void)
{
	BM_S02_EN(GPIO_OUT_HIGH);
#ifdef USART3_DEBUG
	printf("Bluetooth����͹���ģʽOK\r\n");
#endif
	
}

/**********************************************************
**�������ܣ��ж�ģ���Ƿ�������
**����	ֵ��0------���ӳɹ�----IO6����͵�ƽ
**			1------����ʧ��----IO6����ߵ�ƽ
***********************************************************/
uint8_t Bluetooth_RF_BM_S02_Check_Connect_State(void)
{
	if(BM_S02_Check_Connect_State == Bit_RESET)
	{	
#ifdef USART3_DEBUG
		//printf("Bluetooth Connect OK\r\n");
#endif	
		return 0;
	}
	else
	{
	
#ifdef USART3_DEBUG	
		delay_ms(1000);
		//printf("Bluetooth connect failed!\r\n");
#endif
		return 1;
	}
}

/**********************************************************
**�������ܣ��ָ���������
**������0��ǳ�ָ�
		1����ָ�
***********************************************************/
void Bluetooth_RF_BM_S02_RestoreFactory(int i)
{
	int j = 0;
	if(i)
	{
		BM_S02_RestoreFactory(GPIO_OUT_LOW);
		for(j=0;j<21;j++)
		{
			delay_ms(1000);
		}		
		BM_S02_RestoreFactory(GPIO_OUT_HIGH);
	
#ifdef USART3_DEBUG
		printf("Bluetooth��ָ���������OK��\r\n");
#endif
	}
	else
	{
		BM_S02_RestoreFactory(GPIO_OUT_LOW);
		for(j=0;j<5;j++)
		{
			delay_ms(1000);
		}		
		BM_S02_RestoreFactory(GPIO_OUT_HIGH);
	
#ifdef USART3_DEBUG
		printf("Bluetoothǳ�ָ���������OK��\r\n");
#endif
	}
}
#if 0
/*********************************************************
**��������:����ģ�鸴λ
**********************************************************/
void Bluetooth_RF_BM_S02_ReSet(void)
{
	BM_S02_ReSet(GPIO_OUT_LOW);
	delay_ms(15);
	BM_S02_ReSet(GPIO_OUT_HIGH);
	
#ifdef USART3_DEBUG
	printf("Bluetooth Reset OK��\r\n");
#endif
}

#endif



