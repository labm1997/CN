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

bool parser_verificaNomeInt(String *nome){
	unsigned int i=0,j;
	bool ok;
	char permitidos[] = {'0','1','2','3','4','5','6','7','8','9','-','.'};
	for(;i<nome->length-1;i++){
		ok = false;
		for(j=0;j<12;j++)
			if(nome->data[i] == permitidos[j]) ok = true;
		if(!ok) return false;
	}
	return true;
}

AST_no *parser_constroiNoIntVar(String *nome){
	AST_no *filho;
	if(parser_verificaNomeInt(nome)){
		filho = ast_criarNo(nome,INT);
		filho->avaliar = ast_int_avaliar;
		sscanf(nome->data,"%lf",&(filho->valor));
	}
	else filho = ast_criarNo(nome,VAR);
	return filho;
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
				
				if(str_compareraw(nome,"+")){
					pai->avaliar = ast_funcao_soma_avaliar;
				}
				else if(str_compareraw(nome,"*")){
					pai->avaliar = ast_funcao_mult_avaliar;
				}
				else if(str_compareraw(nome,"/")){
					pai->avaliar = ast_funcao_div_avaliar;
				}
				else if(str_compareraw(nome,"-")){
					pai->avaliar = ast_funcao_sub_avaliar;
				}
				
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
					filho = parser_constroiNoIntVar(nome);
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
					filho = parser_constroiNoIntVar(nome);
					ast_adicionarFilho(pai,filho);
				}
				fixo = i+1;
			}
		}
		
		// Se chegou aqui, é pq não ocorreu nenhum caracter especial '(', ')' ou ','
		return parser_constroiNoIntVar(str);
		
}
