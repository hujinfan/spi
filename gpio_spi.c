#include "s3c24xx.h"

/* ��GPIOģ��SPI */

static void SPIO_GPIO_INIT(void)
{
	/* GPF1 OLED_CSn output */
    GPFCON &= ~(3<<(1*2)); //set to 0
    GPFCON |= (1<<(1*2)); //output
    GPFDAT |= (1<<1);

    /* GPG2 FLASH_CSn output
     * GPG4 OLED_DC   output
     * GPG5 SPIMISO   input
     * GPG6 SPIMOSI   output
     * GPG7 SPICLK    output
     */
    GPGCON &= ~((3<<(2*2)) | (3<<(4*2)) | (3<<(5*2)) | (3<<(6*2)) | (3<<(7*2)));
    GPGCON |= ((1<<(2*2)) | (1<<(4*2)) | (1<<(6*2)) | (1<<(7*2))); //output
    GPGDAT |= (1<<2);
}
static void SPI_Set_CLK(char val)
{
	if(val)
		GPGDAT |= (1<<7);
	else
		GPGDAT |= ~(1<<7);
}

static void SPI_Set_DO(char val)
{
	if(val)
		GPGDAT |= (1<<6);
	else
		GPGDAT |= ~(1<<6);
}

void SPISendByte(unsigned char val)
{
	int i;
	for(i=0; i<8; i++)
	{
		/* һ��bit clk�źŴӵ͵��ߣ��������ط������� */
		SPI_Set_CLK(0);
		SPI_Set_DO(val & 0x80); //�ȷ������λ
		SPI_Set_CLK(1);
		val <<= 1;
	}
}

void SPIInit(void)
{
	/*��ʼ������*/
	SPIO_GPIO_INIT();
}
