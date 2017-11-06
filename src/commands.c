#include "commands.h"

static Command *commands_list;
static unsigned int commands_listLength = 2;
static char commands_quitValue = 0; /* Controla a saída do programa */

char commands_quit(){
  return commands_quitValue;
}

void commands_setQuit(){
  commands_quitValue = 1;
  ui_printLog("BYE","Tchau!\n",COLOR_GREEN);
}

void commands_test(){
  ui_printLog("COMMAND","Funciona!\n",COLOR_GREEN);
}

void commands_loadCommands(){
  commands_list = (Command *)malloc(commands_listLength*sizeof(Command));
  commands_list[0].hotword = str_createString("quit");
  commands_list[0].function = commands_setQuit;
  commands_list[1].hotword = str_createString("teste");
  commands_list[1].function = commands_test;
}

void commands_runCommand(String hotword){
  unsigned int i=0;
  char done=0;
  for(;i<commands_listLength;i++)
    if(str_compare(hotword, commands_list[i].hotword)){
      commands_list[i].function();
      done=1;
    }
  if(!done)
    ui_printLog("COMMAND","Comando inválido\n",COLOR_RED);
}
