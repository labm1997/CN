#include "ui.h"
#include "commands.h"
#include "string.h"

static char verbose = 1;

void ui_printLog(char *label, char *message, char *color, ...){
	unsigned int i,labelLength=str_length(label);
	va_list arglist;
	va_start(arglist, color);
	if(labelLength > UI_LABELSIZE){
	  vprintf(message, arglist);
	  return;
	}
	printf("[");
	for(i=0;i<(UI_LABELSIZE-labelLength)/2;i++) putchar(' ');
	printf("%s%s%s", color, label, COLOR_NORMAL);
	for(i=0;i<(UI_LABELSIZE-labelLength)/2;i++) putchar(' ');
	printf("] ");
	vprintf(message, arglist);
}

void ui_interactiveMode(){
  char c;
  String command;
  commands_loadCommands();
  while(!commands_quit()){
    command = str_createString(NULL);
    printf(">> ");
    while((c=fgetc(stdin)) != '\n') str_pushChar(&command, c);
    commands_runCommand(command);
    str_clean(&command);
  }
  commands_cleanCommands();
}

char ui_verbose(){
  return verbose;
} 
