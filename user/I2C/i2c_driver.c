#include "i2c_driver.h"
#include "SysTick.h"




void I2C_GPIOInitConfig(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,I2C_SCL_PIN);
	GPIO_SetBits(GPIOB,I2C_SDA_PIN);
}

static void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,I2C_SDA_PIN);
}

static void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCL_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCL_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,I2C_SCL_PIN);
}
/**************************************
**************************************/
void I2C_Start()
{
	SDA_OUT();
    I2C_SDA_1();
    I2C_SCL_1();       
    delay_us(8);     
    I2C_SDA_0(); 
    delay_us(8);   
    I2C_SCL_0();  
}

/**************************************
**************************************/
void I2C_Stop()
{
	SDA_OUT();
	I2C_SDA_0();
	I2C_SCL_1();  
	delay_us(8);
    I2C_SDA_1();
    delay_us(8);
}

/**************************************
**************************************/
void I2C_SendACK(u8 ack)
{
	SDA_OUT();
	I2C_SCL_0();
	delay_us(8);
	if(ack)
		I2C_SDA_1();
	else I2C_SDA_0();
	I2C_SCL_1(); 
	delay_us(8);
	I2C_SCL_0();
	delay_us(8);
}

/**************************************
**************************************/
u8 I2C_RecvACK(void)
{
	u8 ucErrTime=0;

 	SDA_IN();
	I2C_SDA_1();
	delay_us(4);	   
	I2C_SCL_1();
	delay_us(4);
		 
	while(I2C_SDA_READ())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_Stop();
			return 1;
		}
	}
	I2C_SCL_0();
	return 0;  
}

/**************************************
**************************************/
void I2C_SendByte(u8 dat)
{
	u8 t; 
	SDA_OUT(); 	    
    I2C_SCL_0();
    for(t=0;t<8;t++)
    {
		if(dat&0x80)
			I2C_SDA_1();
		else I2C_SDA_0();
        dat<<=1; 	  
		delay_us(5);
		I2C_SCL_1();
		delay_us(5); 
		I2C_SCL_0();
		delay_us(5);
    }
}

/**************************************
**************************************/	

u8 I2C_RecvByte(void)
{
	int i = 0;
	u8 byte = 0;
	SDA_IN();
	for(i = 0;i < 8;i++)
	{
		delay_us(5);
		I2C_SCL_1();
		delay_us(5);
		byte <<= 1;
		if(I2C_SDA_READ())
		{
			byte |= 0x01;
		}
		I2C_SCL_0();
		delay_us(5);
	}
	return byte;
}


/****************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    �Σ�_Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
****************************************************************************/
uint8_t I2C_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	I2C_Start();		/* ���������ź� */

	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	I2C_SendByte(_Address | I2C_WR);
	ucAck = I2C_RecvACK();	/* ����豸��ACKӦ�� */

	I2C_Stop();			/* ����ֹͣ�ź� */

	return ucAck;
}

