#ifndef HEADER_COMMANDS
#define HEADER_COMMANDS

#include "string.h"

typedef struct command{
  String *hotwords;
  unsigned int n_hotwords;
  void (*function)();
} Command;

typedef struct commands_list{
	Command *commands;
	unsigned int n_commands;
} Commands_list;

void commands_loadCommands();
void commands_cleanCommands();
void commands_runCommand(String);
char commands_quit();

#endif

