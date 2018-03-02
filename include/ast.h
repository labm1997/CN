#ifndef HEADER_AST
#define HEADER_AST

#include "string.h"
#include "array.h"

Array_define_headers(AST_no,struct AST_no *); // Define Array_AST_no e suas funções

typedef enum {
	FUNCAO,
	VAR,
	INT
} AST_notipo;

typedef enum {
	false,
	true
} bool;

typedef struct AST_no{
	Array_AST_no *filhos;
	AST_notipo tipo;
	String *nome;
} AST_no;

typedef struct AST{
	AST_no *raiz;
} AST;

typedef struct AST_pilha_e{
	AST_no *dado;
	struct AST_pilha_e *abaixo;
} AST_pilha_e;

typedef struct AST_pilha{
	AST_pilha_e *raiz;
	unsigned int altura;
} AST_pilha;

AST *ast_criarArvore();
bool ast_definirRaizArvore(AST *arvore, AST_no *raiz);
AST_no *ast_criarNo(String *nome, AST_notipo tipo);
bool ast_adicionarFilho(AST_no *pai, AST_no *filho);
AST_pilha *ast_criarPilha();
bool ast_pushPilha(AST_pilha *pilha, AST_no *no);
AST_pilha_e *ast_popPilha(AST_pilha *pilha);
void ast_mostrarArvore(AST *arvore);
void ast_mostrarNo(AST_pilha *pilha, AST_no *no);

#define INCREASE_ARRAYBLOCK(arraypointer,arraycounter,type,block,failmessage,failreturn) \
	type *increase_arrayblock_tmp;\
	if(arraypointer == NULL){\
		arraypointer = (type *)malloc(block*sizeof(type));\
	}\
	else if(arraycounter % block == 0){\
		increase_arrayblock_tmp = (type *)realloc(arraypointer,(arraycounter/block+1)*block*sizeof(type));\
		if(increase_arrayblock_tmp != NULL){\
			arraypointer = increase_arrayblock_tmp;\
		}\
		else {\
			ui_printLog("FALHA",failmessage,COLOR_RED);	\
			return failreturn;\
		}\
	}\

#endif
