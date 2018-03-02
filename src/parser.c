#include <stdio.h>
#include "ast.h"
#include "parser.h"
#include "array.h"

Array_define(uint,unsigned int); // Implementa o código para Array_uint

parser_cesp *parser_CriarCesp(char car){
	parser_cesp *cesp = (parser_cesp *)malloc(sizeof(parser_cesp));
	if(cesp == NULL){
		ui_printLog("FALHA","Não foi possível alocar memória para um cesp\n",COLOR_RED);
		return NULL;
	}
	cesp->caracter = car;
	cesp->array = Array_uint_criar(1);
	return cesp;
}

void parser_adicionarPosCesp(parser_cesp *cesp, unsigned int pos){
	if(cesp == NULL){
		ui_printLog("FALHA","Não se pode fazer nada com cesp nulo.\n",COLOR_RED);
		return;
	}
	if(!Array_uint_push(cesp->array,pos)){
		ui_printLog("FALHA","Não foi possível adicionar %u ao array de %p ('%c')\n",COLOR_RED,pos,cesp,cesp->caracter);
	}
}

AST *parser(String *str){
	AST_pilha *pilha = ast_criarPilha();
	AST_no *raiz = parser_constroiNo(pilha, str);
	AST *arvore = ast_criarArvore();
	ast_definirRaizArvore(arvore,raiz);
	return arvore;
}

AST_no *parser_constroiNo(AST_pilha *pilha, String *str){
	unsigned int i=0,fixo=0;
	String *nome,*sub_string;
	AST_no *filho,*pai;
	AST_pilha_e *pilha_e;
	
		for(;i<str->length;i++){
			if(str->data[i] == '('){
				// Função
				nome = str_substr(str,fixo,i); // Não inclui '('
				pai = ast_criarNo(nome,FUNCAO);
				ast_pushPilha(pilha,pai);
				sub_string = str_substr(str,i+1,str->length);
				return parser_constroiNo(pilha,sub_string);
			}
			else if(str->data[i] == ')'){
				// Fim de função
				nome = str_substr(str,fixo,i); // Não inclui ')'
				pilha_e = ast_popPilha(pilha);
				if(pilha_e == NULL){
					ui_printLog("FALHA","Erro de sintaxe, parênteses fechou sem ser aberto!\n",COLOR_RED);
					return NULL;
				}
				pai = pilha_e->dado;
				if(nome->length > 1){ // '\0' é contado
					filho = ast_criarNo(nome,VAR);
					ast_adicionarFilho(pai,filho);
				}
				if(pilha->raiz != NULL){
					ast_adicionarFilho(pilha->raiz->dado,pai);
					fixo = i+1;
				}
				else return pai; // Raiz da árvore, ignora o resto 
			}
			else if(str->data[i] == ','){
				// Fim de um argumento
				nome = str_substr(str,fixo,i); // Não inclui ')'
				if(nome->length > 1){
					if(pilha->raiz == NULL){
						ui_printLog("FALHA","Erro de sintaxe, ',' mas sem função pai!\n",COLOR_RED);
						return NULL;
					}
					pai = pilha->raiz->dado;
					filho = ast_criarNo(nome,VAR);
					ast_adicionarFilho(pai,filho);
				}
				fixo = i+1;
			}
		}
		
		// Se chegou aqui, é pq não ocorreu nenhum caracter especial '(', ')' ou ','
		return ast_criarNo(str,VAR);
		
}
