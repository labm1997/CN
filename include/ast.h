#ifndef HEADER_AST
#define HEADER_AST

#include "string.h"

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
	struct AST_no **filhos;
	unsigned int n_filhos;
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



#endif
