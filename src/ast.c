#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ui.h"
#include "array.h"

#define AST_BLOCO 10

Array_define(AST_no, struct AST_no *); // Implementa funções de Array_AST_no

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
		printf("Nó %p (%s)\n", no, no->nome->data);
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

