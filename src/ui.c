#include "ui.h"

void ui_printLog(char *label, char *message, char *color, ...){
	unsigned int i,labelLength=strlen(label);
	va_list arglist;
	va_start(arglist, color);
	printf("[");
	for(i=0;i<(UI_LABELSIZE-labelLength)/2;i++) putchar(' ');
	printf("%s%s%s", color, label, COLOR_NORMAL);
	for(i=0;i<(UI_LABELSIZE-labelLength)/2;i++) putchar(' ');
	printf("] ");
	vprintf(message, arglist);
}
