#ifndef HEADER_AST
#define HEADER_AST

#include "string.h"
#include "array.h"
#include <stdarg.h>

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
	double valor;
	struct AST_no *(*avaliar)(struct AST_no *, Array_AST_no *); // Recebe o nó e seus filhos a serem avaliados
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
AST_no *ast_avaliar(AST *arvore);
struct AST_no *ast_int_avaliar(AST_no *no, Array_AST_no *filhos);

#define ast_funcao_binop_headers(opname,op)\
struct AST_no *ast_funcao_##opname##_avaliar(AST_no *no, Array_AST_no *filhos);

ast_funcao_binop_headers(soma,+);
ast_funcao_binop_headers(mult,*);
ast_funcao_binop_headers(div,/);
ast_funcao_binop_headers(sub,-);

#endif
