#include "SPI_Device.h"


/*********************************************************************************************
**************************************SPI_Flash define****************************************
**********************************************************************************************/
//#define SPI_FLASH_PageSize      4096
#define SPI_FLASH_PageSize      			256
#define SPI_FLASH_PerWritePageSize      	256

/* Private define ------------------------------------------------------------*/
#define W25X_WriteEnable		      	0x06 
#define W25X_WriteDisable		      	0x04 
#define W25X_ReadStatusReg		    	0x05 
#define W25X_WriteStatusReg		    	0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      	0x0B 
#define W25X_FastReadDual		      	0x3B 
#define W25X_PageProgram		      	0x02 
#define W25X_BlockErase			      	0xD8 
#define W25X_SectorErase		      	0x20 
#define W25X_ChipErase			      	0xC7 
#define W25X_PowerDown			      	0xB9 
#define W25X_ReleasePowerDown	    	0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   		0x90 
#define W25X_JedecDeviceID		    	0x9F 

#define WIP_Flag                  		0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte                		0xFF
/*********************************************************************************************/

#ifdef	SPI1_MASTER_MODE
/*********************************************************************************************
*****************************************Master Mode******************************************
**********************************************************************************************/

#ifdef DEVICE_SPIFLASH

#if 0
void SPI1_InitConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
//	GPIO_PinAFConfig(GPIOA ,GPIO_PinSource4, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOB ,GPIO_PinSource3, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB ,GPIO_PinSource4, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB ,GPIO_PinSource5, GPIO_AF_0);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_NSS_HIGH();
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_Cmd(SPI1, ENABLE);
}

#else

void SPI1_InitConfig(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3 , GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_0);

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	SPI_NSS_HIGH();
	
	//SPI CONFIGURATION
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;         
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_CRCPolynomial = 7; 				
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI1, &SPI_InitStructure);
	
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	SPI_Init(SPI1, &SPI_InitStructure);
	
	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
	SPI_Cmd(SPI1, ENABLE); /* SPI enable */
          
}
#endif




uint8_t SPI_RW(uint8_t byte)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_SendData8(SPI1, byte);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	return SPI_ReceiveData8(SPI1);
}


uint16_t SPI_RWHalfWord(uint16_t HalfWord)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData16(SPI1, HalfWord);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	return SPI_I2S_ReceiveData16(SPI1);
}

/*********************************************************************************************
*******************************************SPI-Flash******************************************
**********************************************************************************************/


/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint8_t SPI_FLASH_ReadByte(void)
{
  return (SPI_RW(0xff));
}


/*******************************************************************************
* Function Name  : SPI_FLASH_WriteEnable
* Description    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Write Enable" instruction */
	SPI_RW(W25X_WriteEnable);

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
	uint8_t FLASH_Status = 0;

	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Read Status Register" instruction */
	SPI_RW(W25X_ReadStatusReg);

	/* Loop as long as the memory is busy with a write cycle */
	do
	{
		/* Send a dummy byte to generate the clock needed by the FLASH
		and put the value of the status register in FLASH_Status variable */
		FLASH_Status = SPI_RW(Dummy_Byte);	 
	}
	while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();
}


//进入掉电模式
void SPI_Flash_PowerDown(void)   
{ 
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Power Down" instruction */
	SPI_RW(W25X_PowerDown);

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();
}   

//唤醒
void SPI_Flash_WAKEUP(void) 
{
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Power Down" instruction */
	SPI_RW(W25X_ReleasePowerDown);

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();                   //等待TRES1
}


/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Read from Memory " instruction */
	SPI_RW(W25X_ReadData);

	/* Send the 24-bit address of the address to read from -----------------------*/
	/* Send ReadAddr high nibble address byte */
	SPI_RW((ReadAddr & 0xFF0000) >> 16);
	/* Send ReadAddr medium nibble address byte */
	SPI_RW((ReadAddr& 0xFF00) >> 8);
	/* Send ReadAddr low nibble address byte */
	SPI_RW(ReadAddr & 0xFF);
}


/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
uint32_t SPI_FLASH_ReadDeviceID(void)
{
	uint32_t Temp = 0;

	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "RDID " instruction */
	SPI_RW(W25X_DeviceID);
	SPI_RW(Dummy_Byte);
	SPI_RW(Dummy_Byte);
	SPI_RW(Dummy_Byte);

	/* Read a byte from the FLASH */
	Temp = SPI_RW(Dummy_Byte);

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();

	return Temp;
}


/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
uint32_t SPI_FLASH_ReadID(void)
{
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "RDID " instruction */
	SPI_RW(W25X_JedecDeviceID);

	/* Read a byte from the FLASH */
	Temp0 = SPI_RW(Dummy_Byte);

	/* Read a byte from the FLASH */
	Temp1 = SPI_RW(Dummy_Byte);

	/* Read a byte from the FLASH */
	Temp2 = SPI_RW(Dummy_Byte);

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();

	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return Temp;
}


/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();

	/* Send "Read from Memory " instruction */
	SPI_RW(W25X_ReadData);

	/* Send ReadAddr high nibble address byte to read from */
	SPI_RW((ReadAddr & 0xFF0000) >> 16);
	/* Send ReadAddr medium nibble address byte to read from */
	SPI_RW((ReadAddr& 0xFF00) >> 8);
	/* Send ReadAddr low nibble address byte to read from */
	SPI_RW(ReadAddr & 0xFF);

	while (NumByteToRead--) /* while there is data to be read */
	{
	/* Read a byte from the FLASH */
	*pBuffer = SPI_RW(Dummy_Byte);
	/* Point to the next location where the byte read will be saved */
	pBuffer++;
	}

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	/* Enable the write access to the FLASH */
	SPI_FLASH_WriteEnable();

	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();
	/* Send "Write to Memory " instruction */
	SPI_RW(W25X_PageProgram);
	/* Send WriteAddr high nibble address byte to write to */
	SPI_RW((WriteAddr & 0xFF0000) >> 16);
	/* Send WriteAddr medium nibble address byte to write to */
	SPI_RW((WriteAddr & 0xFF00) >> 8);
	/* Send WriteAddr low nibble address byte to write to */
	SPI_RW(WriteAddr & 0xFF);

	if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
	{
		NumByteToWrite = SPI_FLASH_PerWritePageSize;
		//printf("\n\r Err: SPI_FLASH_PageWrite too large!");
	}

	/* while there is data to be written on the FLASH */
	while (NumByteToWrite--)
	{
		/* Send the current byte */
		SPI_RW(*pBuffer);
		/* Point on the next byte to be written */
		pBuffer++;
	}

	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();

	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

	Addr = WriteAddr % SPI_FLASH_PageSize;
	count = SPI_FLASH_PageSize - Addr;
	NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
	NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

	if (Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
	{
		if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
		{
			SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
		}
		else /* NumByteToWrite > SPI_FLASH_PageSize */
		{
			while (NumOfPage--)
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}

			SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
		}
	}
	else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
	{
		if (NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
		{
			if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
			{
				temp = NumOfSingle - count;

				SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
				WriteAddr +=  count;
				pBuffer += count;

				SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
			}
			else
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
			}
		}
		else /* NumByteToWrite > SPI_FLASH_PageSize */
		{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
			NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

			SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
			WriteAddr +=  count;
			pBuffer += count;

			while (NumOfPage--)
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
				WriteAddr +=  SPI_FLASH_PageSize;
				pBuffer += SPI_FLASH_PageSize;
			}

			if (NumOfSingle != 0)
			{
				SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
			}
		}
	}
}


/*******************************************************************************
* Function Name  : SPI_FLASH_BulkErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BulkErase(void)
{
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();

	/* Bulk Erase */
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();
	/* Send Bulk Erase instruction  */
	SPI_RW(W25X_ChipErase);
	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();

	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	/* Send write enable instruction */
	SPI_FLASH_WriteEnable();
	SPI_FLASH_WaitForWriteEnd();
	/* Sector Erase */
	/* Select the FLASH: Chip Select low */
	SPI_NSS_LOW();
	/* Send Sector Erase instruction */
	SPI_RW(W25X_SectorErase);
	/* Send SectorAddr high nibble address byte */
	SPI_RW((SectorAddr & 0xFF0000) >> 16);
	/* Send SectorAddr medium nibble address byte */
	SPI_RW((SectorAddr & 0xFF00) >> 8);
	/* Send SectorAddr low nibble address byte */
	SPI_RW(SectorAddr & 0xFF);
	/* Deselect the FLASH: Chip Select high */
	SPI_NSS_HIGH();
	/* Wait the end of Flash writing */
	SPI_FLASH_WaitForWriteEnd();
}

#elif defined(DEVICE_OLED)
/*********************************************************************************************
*******************************************OLED***********************************************
**SCLK----->GPIOB13
**MOSI----->GPIOB15
**********************************************************************************************/

void SPI2_InitConfig(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;
	
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	
	/* 配置SPI2 管脚: SCK */     
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0);

	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;         
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI2, &SPI_InitStructure);
	
//	SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
//	SPI_RxFIFOThresholdConfig(SPI2, SPI_RxFIFOThreshold_QF);
	SPI_Cmd(SPI2, ENABLE); /* SPI enable */
          
}

void SPI_WriterByte(uint8_t dat)
{
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	SPI_SendData8(SPI2, dat);
}

#endif

#elif defined(SPI1_SLAVE_MODE)
/*********************************************************************************************
*******************************************Slave Mode*****************************************
**********************************************************************************************/
void SPI2_InitConfig(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(GPIOB , &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;         
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;   
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_I2S_ITConfig(SPI2,SPI_I2S_IT_RXNE, ENABLE);
	
	SPI_Cmd(SPI2, ENABLE);
}

void SPI_NVIC_InitConfig(void)
{
	NVIC_InitTypeDef NVIC_InitStructconfig;
	
	NVIC_InitStructconfig.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructconfig.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructconfig.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructconfig);
}


uint8_t SPI_RW(uint8_t byte)
{
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

	SPI_SendData8(SPI2, byte);

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

	return SPI_ReceiveData8(SPI2);
}


#endif

void SPI_InitConfig(void)
{
#ifdef	SPI1_MASTER_MODE

#ifdef DEVICE_SPIFLASH
	SPI1_InitConfig();
#elif defined(DEVICE_OLED)
	SPI2_InitConfig();
#endif
	
#elif defined(SPI1_SLAVE_MODE)
	SPI2_InitConfig();
	SPI_NVIC_InitConfig();
#endif
}
