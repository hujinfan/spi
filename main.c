#include <stdio.h>
#include "serial.h"
#include "i2c.h"
#include "s3c2440_spi.h"
#include "oled.h"
#include "spi_flash.h"

unsigned char at24cxx_read(unsigned char address);
void at24cxx_write(unsigned char address, unsigned char data);


int main()
{
    char c;
    char str[200];
    int i;
	int address;
	int data;
	unsigned int mid,pid;
    
    uart0_init();   // 波特率115200，8N1(8个数据位，无校验位，1个停止位)

	SPIInit();
	OLEDInit();
	OLEDPrint(0,0,"hjf study spi");

	SPIFlashReadID(&mid, &pid);
	printf("SPI Flash: MID = 0x%02x, PID=0x%02x\n\r",mid,pid);

	sprintf(str,"spi: %02x,%02x",mid,pid);
	OLEDPrint(2,0,str);
	
	SPIFlashInit();
	
	SPIFlashEraseSector(4096);
	SPIFlashProgram(4096, "hujinfan", 9);
	SPIFlashRead(4096, str, 9);
	printf("SPI Flash read from 4096: %s\n\r",str);
	OLEDPrint(4,0,str);

	i2c_init();
	at24cxx_write(0, 0x55);
	data = at24cxx_read(0);

	OLEDCleanPage(2);
	OLEDCleanPage(3);
	
	if(data == 0x55)
		OLEDPrint(2,0,"I2C OK!");
	else
		OLEDPrint(2,0,"I2C Err!");
		
	Test_Adc();
    
    return 0;
}
