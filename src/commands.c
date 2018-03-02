#include "commands.h"
#include "metodos.h"

static Commands_list *commands_list;
static char commands_quitValue = 0; /* Controla a saída do programa */

char commands_quit(){
  return commands_quitValue;
}

void commands_nada(){}

void commands_setQuit(){
  commands_quitValue = 1;
  ui_printLog("BYE","Tchau!\n",COLOR_GREEN);
}

void commands_test(){
  ui_printLog("COMMAND","Funciona!\n",COLOR_GREEN);
}

void commands_help(){
	printf("Comandos disponíveis:\n");
	printf("\tquit | exit | sair | x: Sair do programa\n");
	printf("\tbc: Método da bisseção\n");
	printf("\thelp: Mostra a ajuda\n");
}

Command *commands_addCommand(void (*f)()){
	if(commands_list->commands != NULL)
		commands_list->commands = (Command *)realloc(commands_list->commands, (commands_list->n_commands+1)*sizeof(Command));
	else commands_list->commands = (Command *)malloc(sizeof(Command));
	
  commands_list->commands[commands_list->n_commands].n_hotwords = 0;
  commands_list->commands[commands_list->n_commands].hotwords = NULL;
  commands_list->commands[commands_list->n_commands].function = f;
  commands_list->n_commands++;
  
  return &(commands_list->commands[commands_list->n_commands-1]);
}

void commands_addHotword(Command *c, char *str){
	if(c->hotwords != NULL)
		c->hotwords = (String **)realloc(c->hotwords, (c->n_hotwords+1)*sizeof(String *));
	else c->hotwords = (String **)malloc(sizeof(String *));
	
	c->hotwords[c->n_hotwords] = str_createString(str);
	c->n_hotwords++;	
}

void commands_cleanCommands(){
	unsigned int i,j;
	for(i=0;i<commands_list->n_commands;i++){
		for(j=0;j<commands_list->commands[i].n_hotwords;j++){
			str_clean(commands_list->commands[i].hotwords[j]);
		}
	}
	free(commands_list->commands);
	free(commands_list);
	commands_list = NULL;
}

/*!TODO Ler comandos de arquivo */

void commands_loadCommands(){
	Command *tmp;
  commands_list = (Commands_list *)malloc(sizeof(Commands_list));
	commands_list->n_commands = 0;
	commands_list->commands = NULL;
	
	tmp = commands_addCommand(commands_setQuit);
  commands_addHotword(tmp,"quit");
  commands_addHotword(tmp,"exit");
  commands_addHotword(tmp,"sair");
  commands_addHotword(tmp,"x");
  
	tmp = commands_addCommand(commands_test);
  commands_addHotword(tmp,"teste");
  
	tmp = commands_addCommand(metodo_bc);
  commands_addHotword(tmp,"bc");
  
	tmp = commands_addCommand(commands_help);
  commands_addHotword(tmp,"help");
  
	tmp = commands_addCommand(commands_nada);
  commands_addHotword(tmp,"");
  
}

void commands_runCommand(String *hotword){
  unsigned int i=0,j;
  char done=0;
  for(;i<commands_list->n_commands;i++){
  	for(j=0;j<commands_list->commands[i].n_hotwords;j++)
		  if(str_compare(hotword, commands_list->commands[i].hotwords[j])){
		    commands_list->commands[i].function();
		    done=1;
		  }
  }
  if(!done)
    ui_printLog("COMMAND","Comando inválido\n",COLOR_RED);
}
