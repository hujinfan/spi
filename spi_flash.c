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
	/* ��������3�ֽ�Ϊ0�����ݣ��ܹ�24bit */
	SPISendByte(addr >> 16);  // ����8bit��0
	SPISendByte(addr >> 8);   //���м�8bit��0
	SPISendByte(addr & 0xff); //����8bit��0
}

/*
 *
 */
void SPIFlashReadID(int *pMID, int *pDID)
{
	SPIFlash_Set_CS(0); /* ѡ��SPI FLASH */

	SPISendByte(0x90);
	
	SPIFlashSendAddr(0);

	
	*pMID = SPIRecvByte();
	*pDID = SPIRecvByte();
	
	SPIFlash_Set_CS(1); /* ȡ��ѡ��SPI FLASH */
}

