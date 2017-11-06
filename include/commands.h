#ifndef HEADER_COMMANDS
#define HEADER_COMMANDS

#include "string.h"

typedef struct command{
  String hotword;
  void (*function)();
} Command;

void commands_loadCommands();
void commands_runCommand(String);
char commands_quit();

#endif

