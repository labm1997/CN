#ifndef HEADER_UI
#define HEADER_UI

#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "color.h"

#define UI_LABELSIZE 10

void ui_printLog(char *label, char *message, char *color, ...);
void ui_interactiveMode();
char ui_verbose();

#endif

