#ifndef HEADER_PARSER
#define HEADER_PARSER

#include "string.h"
#include "ast.h"
#include "array.h"

Array_define_headers(uint,unsigned int); // Define cabeçalho para Array_uint

typedef struct parser_cesp{ // caracter especial
	char caracter;
	Array_uint *array;
} parser_cesp;

AST *parser(String *str);
AST_no *parser_constroiNo(AST_pilha *pilha, String *str);

#endif
