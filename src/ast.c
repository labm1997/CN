#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ui.h"
#include "array.h"

#define AST_BLOCO 10

Array_define(AST_no, struct AST_no *); // Implementa funções de Array_AST_no

struct AST_no *ast_int_avaliar(AST_no *no, Array_AST_no *filhos){
	return no;
}

// Operações binárias
#define ast_funcao_binop(opname,op)\
	\
	struct AST_no *ast_funcao_##opname##_avaliar(AST_no *no, Array_AST_no *filhos){\
		AST_no *ret, *app1, *app2;\
		double res;\
		if(filhos->tamanho == 2){\
			if(filhos->data[0]->avaliar == NULL || filhos->data[1]->avaliar == NULL){\
				ui_printLog("FALHA","Falha ao avaliar nó %p (%s): Sem definição de aplicação para algum filho\n",COLOR_RED,no,no->nome->data);\
				return NULL;\
			}\
			app1 = (filhos->data[0]->avaliar(filhos->data[0],filhos->data[0]->filhos));\
			app2 = (filhos->data[1]->avaliar(filhos->data[1],filhos->data[1]->filhos));\
			if(app1 != NULL && app2 != NULL){\
				res = app1->valor op app2->valor;\
			}\
			else {\
				ui_printLog("FALHA","Falha ao avaliar nó %p (%s)\n",COLOR_RED,no,no->nome->data);\
				return NULL;\
			}\
		}\
		else {\
			ui_printLog("FALHA","Operação " #opname " requer exatamente dois argumentos\n",COLOR_RED);\
			return NULL;\
		}\
		ret = ast_criarNo(str_createString(NULL),INT);\
		ret->valor = res;\
		return ret;\
	}\

ast_funcao_binop(soma,+);
ast_funcao_binop(mult,*);
ast_funcao_binop(div,/);
ast_funcao_binop(sub,-);


AST_no *ast_avaliar(AST *arvore){
	if(arvore == NULL){
		ui_printLog("FALHA","Não é possível avaliar árvore nula\n",COLOR_RED);
		return NULL;
	}
	if(arvore->raiz == NULL){
		ui_printLog("FALHA","Não é possível avaliar árvore com raiz nula\n",COLOR_RED);
		return NULL;
	}
	if(arvore->raiz->avaliar == NULL){
		ui_printLog("FALHA","Não é possível avaliar árvore com nó sem função de avaliação\n",COLOR_RED);
		return NULL;
	}
	return arvore->raiz->avaliar(arvore->raiz,arvore->raiz->filhos);
	
}

AST *ast_criarArvore(){
	AST *ret = (AST *)malloc(sizeof(AST));
	if(ret == NULL){
		ui_printLog("MALLOC","Falha ao alocar memória para criação de árvore\n",COLOR_RED);
		return NULL;
	}
	ret->raiz = NULL;
	return ret;
}

bool ast_definirRaizArvore(AST *arvore, AST_no *raiz){
	if(arvore == NULL){
		ui_printLog("FALHA","Árvore nula\n",COLOR_RED);
		return false;
	}
	arvore->raiz = raiz;
	if(raiz == NULL){
		ui_printLog("WARNING","Nó raiz é NULL\n",COLOR_YELLOW);	
	}
	return true;
}

AST_no *ast_criarNo(String *nome, AST_notipo tipo){
	AST_no *ret = (AST_no *)malloc(sizeof(AST_no));
	if(ret == NULL){
		ui_printLog("MALLOC","Falha ao alocar memória para criação de nó\n",COLOR_RED);
		return NULL;
	}
	ret->filhos = Array_AST_no_criar(AST_BLOCO);
	ret->tipo = tipo;
	ret->nome = nome;
	ret->avaliar = NULL;
	return ret;
}

bool ast_adicionarFilho(AST_no *pai, AST_no *filho){
	if(pai == NULL){
		ui_printLog("FALHA","Ponteiro para nó pai é nulo\n",COLOR_RED);	
		return false;
	}
	
	if(!Array_AST_no_push(pai->filhos,filho)){
		ui_printLog("FALHA","Falha realloc, falha ao adicionar um nó como filho.",COLOR_RED);	
		return false;
	}
	return true;
}

void ast_mostrarArvore(AST *arvore){
	AST_pilha *pilha = ast_criarPilha();
	if(arvore->raiz == NULL){
		ui_printLog("WARNING","Árvore vazia\n",COLOR_YELLOW);
		return;
	}
	ast_mostrarNo(pilha,arvore->raiz);
}

void ast_mostrarNo(AST_pilha *pilha, AST_no *no){
	unsigned int i=0,j;
	if(ast_pushPilha(pilha,no)){
		if(no == NULL){
			ui_printLog("WARNING","Nó nulo\n",COLOR_YELLOW);
			return;
		}
		for(j=1;j<pilha->altura;j++) printf(" ");
		if(no->tipo == INT) printf("Nó %p (%s): Valor = %lf\n", no, no->nome->data, no->valor);
		else printf("Nó %p (%s)\n", no, no->nome->data);
		for(;i<no->filhos->tamanho;i++){
			if(no->filhos->data[i] == NULL){
				ui_printLog("WARNING","Nó nulo entre filhos de %p\n",COLOR_YELLOW, no);
			}
			else {
				ast_mostrarNo(pilha, no->filhos->data[i]);
			}
		}
		ast_popPilha(pilha);
	}
}

AST_pilha *ast_criarPilha(){
	AST_pilha *ret = (AST_pilha *)malloc(sizeof(AST_pilha));
	if(ret == NULL){
		ui_printLog("MALLOC","Falha ao alocar memória para criação de pilha\n",COLOR_RED);
		return NULL;
	}
	ret->raiz = NULL;
	ret->altura = 0;
	return ret;
}

bool ast_pushPilha(AST_pilha *pilha, AST_no *no){
	AST_pilha_e *novo = (AST_pilha_e *)malloc(sizeof(AST_pilha_e)),*tmp;
	if(novo == NULL){
		ui_printLog("MALLOC","Falha ao alocar memória push em pilha %p\n",COLOR_RED,pilha);
		return false;
	}
	if(pilha == NULL){
		ui_printLog("ARG","Ponteiro inválido de pilha\n",COLOR_RED);
		free(novo);
		return false;
	}
	if(no == NULL){
		ui_printLog("WARNING","Ponteiro para nó nulo na pilha\n",COLOR_YELLOW);	
	}
	novo->abaixo = pilha->raiz;
	novo->dado = no;
	pilha->raiz = novo;
	pilha->altura++;
	return true;
}

AST_pilha_e *ast_popPilha(AST_pilha *pilha){
	AST_pilha_e *ret;
	if(pilha == NULL){
		ui_printLog("WARNING","Não pode fazer pop de ponteiro nulo\n",COLOR_YELLOW);
		return NULL;
	}
	ret = pilha->raiz;
	if(pilha->raiz != NULL) pilha->raiz = pilha->raiz->abaixo;
	pilha->altura--;
	return ret;
}

