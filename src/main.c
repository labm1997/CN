#include <stdlib.h>
#include <stdio.h>
#include "ui.h"

int main(){
	ui_printLog("INICIOU","Ahhhh %u\n",COLOR_GREEN,10);
	ui_interactiveMode();
	return 0;
}
