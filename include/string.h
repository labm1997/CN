#ifndef HEADER_STRING
#define HEADER_STRING

#include <stdlib.h>
#include "ui.h"

typedef struct String{
  char *data;
  unsigned int length; /* Com '\0' */
} String;

unsigned int str_length(char *);
void str_pushChar(String *, char);
String *str_createString(char *);
char str_compare(String *, String *);
void str_clean(String *);
String *str_substr(String *, unsigned int, unsigned int);

#endif
