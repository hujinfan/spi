#include "spi_flash.h"
#include "s3c24xx.h"
#include "gpio_spi.h"

static void SPIFlash_Set_CS(char val)
{
	/* GPG2 FLASH_CSn output */
	if(val)
		GPGDAT |= (1 << 2);
	else
		GPGDAT &= ~(1 << 2);
}


static void SPIFlashSendAddr(unsigned int addr)
{
	/* 连续发出3字节为0的数据，总共24bit */
	SPISendByte(addr >> 16);  // 将高8bit置0
	SPISendByte(addr >> 8);   //将中间8bit置0
	SPISendByte(addr & 0xff); //将低8bit置0
}

/*
 *
 */
void SPIFlashReadID(int *pMID, int *pDID)
{
	SPIFlash_Set_CS(0); /* 选中SPI FLASH */

	SPISendByte(0x90);
	
	SPIFlashSendAddr(0);

	
	*pMID = SPIRecvByte();
	*pDID = SPIRecvByte();
	
	SPIFlash_Set_CS(1); /* 取消选中SPI FLASH */
}

