#include "s3c24xx.h"



static void SPI_GPIO_INIT(void)
{
	/* GPF1 OLED_CSn output */
    GPFCON &= ~(3<<(1*2)); //set to 0
    GPFCON |= (1<<(1*2)); //output
    GPFDAT |= (1<<1);

    /* GPG2 FLASH_CSn output
     * GPG4 OLED_DC   output
     * GPG5 SPIMISO   11 功能引脚
     * GPG6 SPIMOSI   11 功能引脚
     * GPG7 SPICLK    11 功能引脚
     */
    GPGCON &= ~((3<<(2*2)) | (3<<(4*2)) | (3<<(5*2)) | (3<<(6*2)) | (3<<(7*2)));
    GPGCON |= ((1<<(2*2)) | (1<<(4*2)) | (3<<(5*2)) | (3<<(6*2)) | (3<<(7*2))); //5 6 7设置成SPI功能引脚
    GPGDAT |= (1<<2);
}

void SPISendByte(unsigned char val)
{
	while(!(SPSTA1 & 1));
	SPTDAT1 = val;
}

unsigned char SPIRecvByte(void)
{
	SPTDAT1 = 0xff;
	while(!(SPSTA1 & 1));
	return SPRDAT1;
}

static void SPIControllerInit(void)
{
	/* OLED: 100ns, 10MHz
	 * FLASH: max = 104MHz
	 * 取 10MHz
	 * Baud rate = PCLK / 2 / (Prescaler value + 1) 其中Baud rate=10 PCLK=50
	 * Prescaler value = 1.5 = 2
	 * Baud rate = 50/2/3=8.3MHz
	 */
	SPPRE0 = 2;
	SPPRE1 = 2;

	/* SPCONn:
	 * [6:5]: 00  polling mode
	 * [4]: 1 SCK enabled
	 * [3]: 1 = master
	 * [2]: 0 = active high
	 * [1]: 0 = format A
	 * [0]: 0 = normal mode
	 */
	SPCON0 = (1<<4)|(1<<3);
	SPCON1 = (1<<4)|(1<<3);
	
}
void SPIInit(void)
{
	/*初始化引脚*/
	SPI_GPIO_INIT();

	/* 初始化管脚控制器 */
	SPIControllerInit();
}

