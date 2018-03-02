#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "ast.h"
#include "parser.h"

int main(int argc, char **argv){
	ui_printLog("INICIOU","Ahhhh %u\n",COLOR_GREEN,10);
/*	AST_pilha *pilha = ast_criarPilha();*/
/*	AST_no *no = ast_criarNo(str_createString("teste"),VAR);*/
/*	AST_no *no2 = ast_criarNo(str_createString("abcdefghijklmnopqrstuvwxyz"),VAR);*/
/*	ast_pushPilha(pilha,no);*/
/*	printf("%s\n", pilha->raiz->dado->nome->data);*/
/*	String *a = str_createString("abcdefghijklmnopqrstuvwxyz");*/
/*	String *s = str_substr(a,0,1);*/
/*	if(s!=NULL)puts(s->data);*/
/*	ast_pushPilha(pilha,no2);*/
/*	printf("%s\n", pilha->raiz->dado->nome->data);*/
/*	ast_popPilha(pilha);*/
/*	printf("%s\n", pilha->raiz->dado->nome->data);*/
	//ui_interactiveMode();
	
	// TESTE DA ARVORE
/*	AST *arvore = ast_criarArvore();*/
/*	AST_no *raiz = ast_criarNo(str_createString("Raiz"), VAR);*/
/*	ast_definirRaizArvore(arvore,raiz);*/
/*	*/
/*	AST_no *no11 = ast_criarNo(str_createString("Nó 11"), VAR);*/
/*	ast_adicionarFilho(raiz,no11);*/
/*	AST_no *no111 = ast_criarNo(str_createString("Nó 111"), VAR);*/
/*	ast_adicionarFilho(no11,no111);*/
/*	AST_no *no12 = ast_criarNo(str_createString("Nó 12"), VAR);*/
/*	ast_adicionarFilho(raiz,no12);*/
/*	ast_adicionarFilho(raiz,NULL);*/
/*	*/
/*	ast_mostrarArvore(arvore);*/

	if(argc != 2){
		ui_printLog("FALHA","Preciso de um argumento\n",COLOR_YELLOW);
		return 1;
	}
	AST *arvore = parser(str_createString(argv[1]));
	ast_mostrarArvore(arvore);
	
	return 0;
}
