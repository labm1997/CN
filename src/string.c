#include "string.h"

String *str_createString(char *str){
  unsigned int i=0;
  String *string = (String *)malloc(sizeof(String));
  if(string == NULL){
  	ui_printLog("FALHA","Não há memória para alocar string: %s\n",COLOR_RED,str);
  	return NULL;
  }
  string->data = (char *)malloc(1); /* Espaço para '\0' */
  
  /* Falha em alocação de memória */
  if(string->data == NULL){
    if(ui_verbose()) ui_printLog("FALHA","Não há memória\n",COLOR_RED);
    string->length = 0;
    return string;
  }
  if(str != NULL)
    while(str[i]!='\0'){
      string->data = (char *)realloc(string->data, ++i+1);
      string->data[i-1] = str[i-1];
    }
  string->data[i] = '\0';
  string->length = i+1;
  return string;
}

void str_pushChar(String *string, char c){
  string->data = (char *)realloc(string->data, ++string->length); // Cuidado, e se retornar NULL?
  string->data[string->length-2] = c;
  string->data[string->length-1] = '\0';
}

unsigned int str_length(char *str){
  unsigned int i=0;
  while(str[i++]!='\0');
  return i;
}

char str_compare(String *str1, String *str2){
  unsigned int i=0;
  for(;str1->data[i] != '\0' && str2->data[i] != '\0';i++)
    if(str1->data[i] != str2->data[i]) return 0;
  if(str1->data[i] != '\0' || str2->data[i] != '\0') return 0;
  return 1;
}

void str_clean(String *string){
  free(string->data);
  string->data = NULL;
}

String *str_substr(String *string, unsigned int l1, unsigned int l2){
	String *ret = str_createString(NULL);
	unsigned int i=l1;
	if(l1 > l2){
  	ui_printLog("FALHA","substr: l1>l2\n",COLOR_RED);
		return NULL;
	}
	l2 = (l2 > string->length) ? string->length : l2;
	for(;i<l2;i++) str_pushChar(ret,string->data[i]);
	return ret;
}
