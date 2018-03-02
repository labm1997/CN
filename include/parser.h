#ifndef HEADER_PARSER
#define HEADER_PARSER

#include "string.h"
#include "ast.h"

AST *parser(String *str);
AST_no *parser_constroiNo(AST_pilha *pilha, String *str);

#endif
