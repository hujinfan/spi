#ifndef _OLED_H_
#define _OLED_H_

void OLEDPrint(int page, int col, char *str);
void OLEDInit(void);
void OLEDPutChar(int page, int col, char c);

void OLEDCleanPage(int page);

#endif
