#include "oledfont.h"
#include "gpio_spi.h"
#include "s3c24xx.h"


static void OLED_Set_DC(char val)
{
	if(val)
		GPGDAT |= (1<<4);
	else
		GPGDAT |= ~(1<<4);	
}

static void OLED_Set_CS(char val)
{
	if(val)
		GPFDAT |= (1<<1);
	else
		GPFDAT |= ~(1<<1);	
}

static void OLEDWriteCmd(unsigned char cmd)
{
	/* 发命令之前需要将OLED_DC引脚设置为0，表示要发送命令 */
	OLED_Set_DC(0);  /* command */

	OLED_Set_CS(0); /* 选中OLED */ 

	SPISendByte(cmd);

	OLED_Set_CS(1); /* de-select OLED */ 
	
	OLED_Set_DC(1);  /* data */
}

static void OLEDWriteDat(unsigned char dat)
{
	/* 发命令之前需要将OLED_DC引脚设置为0，表示要发送命令 */
	OLED_Set_DC(1);  /* data */

	OLED_Set_CS(0); /* 选中OLED */ 

	SPISendByte(dat);

	OLED_Set_CS(1); /* de-select OLED */ 
	
	OLED_Set_DC(0);  /* command */
}

static void OLEDSetPageAddrMode(void)
{
	OLEDWriteCmd(0x20);
	OLEDWriteCmd(0x02);
}

static void OLEDSetPos(int page, int col)
{
	OLEDWriteCmd(0xB0 + page); /* page address */

	OLEDWriteCmd(col & 0xf); /* Set Lower Column Start Address */

	OLEDWriteCmd(0x10 + (col >> 4)); /* Set Higher Column Start Address */	
}

void OLEDPutChar(int page, int col, char c)
{
	/* 得到字模 */
	const unsigned char *dots = oled_asc2_8x16[c - ' '];
	/* 发给OLED */
	OLEDSetPos(page, col); //两次操作，发出2次8字节数据才是一个字符
	/* 发出8字节数据 */
	int i;
	for(i=0; i<8; i++)
		OLEDWriteDat(dots[i]);
	
	OLEDSetPos(page+1, col);
	/* 发出8字节数据 */
	for(i=0; i<8; i++)
		OLEDWriteDat(dots[i+8]);
}

static OLEDClear(void)
{
	int page, i;
	for(page=0; page<8; page++)
	{
		OLEDSetPos(page, 0);
		for(i=0; i<128; i++)
			OLEDWriteDat(0);
		
	}
}

void OLEDInit(void)
{
	 /* 向OLED发命令以初始化 */
	OLEDWriteCmd(0xAE); /*display off*/ 
    OLEDWriteCmd(0x00); /*set lower column address*/ 
    OLEDWriteCmd(0x10); /*set higher column address*/ 
    OLEDWriteCmd(0x40); /*set display start line*/ 
    OLEDWriteCmd(0xB0); /*set page address*/ 
    OLEDWriteCmd(0x81); /*contract control*/ 
    OLEDWriteCmd(0x66); /*128*/ 
    OLEDWriteCmd(0xA1); /*set segment remap*/ 
    OLEDWriteCmd(0xA6); /*normal / reverse*/ 
    OLEDWriteCmd(0xA8); /*multiplex ratio*/ 
    OLEDWriteCmd(0x3F); /*duty = 1/64*/ 
    OLEDWriteCmd(0xC8); /*Com scan direction*/ 
    OLEDWriteCmd(0xD3); /*set display offset*/ 
    OLEDWriteCmd(0x00); 
    OLEDWriteCmd(0xD5); /*set osc division*/ 
    OLEDWriteCmd(0x80); 
    OLEDWriteCmd(0xD9); /*set pre-charge period*/ 
    OLEDWriteCmd(0x1f); 
    OLEDWriteCmd(0xDA); /*set COM pins*/ 
    OLEDWriteCmd(0x12); 
    OLEDWriteCmd(0xdb); /*set vcomh*/ 
    OLEDWriteCmd(0x30); 
    OLEDWriteCmd(0x8d); /*set charge pump enable*/ 
    OLEDWriteCmd(0x14); 

	OLEDSetPageAddrMode();

    OLEDClear();
	
    OLEDWriteCmd(0xAF); /*display ON*/ 
}


/* page: 0-7 (一页是8行，即8个像素)
 * col: 0-127
 * 字符: 8×16像素
 */
void OLEDPrint(int page, int col, char *str)
{
	int i;
	while(str[i])
	{
		OLEDPutChar(page, col, str[i]);
		col += 8;
		if(col > 127)
		{
			col = 0;
			page += 2;
		}
		i++;
	}
}

