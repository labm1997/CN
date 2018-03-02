/* Contém implementação e cabeçalho */

#ifndef HEADER_ARRAY
#define HEADER_ARRAY

#include <stdlib.h>

typedef enum {
	ARRAY_ERRO,
	ARRAY_OK
} Array_status;

// Array parametrizado por uma estrutura de dados

#define Array_define_headers(nome,tipo)\
\
	typedef struct Array_##nome{\
		tipo *data;\
		unsigned int tamanho;\
		unsigned int tamanho_bloco;\
	} Array_##nome;\
	\
	Array_##nome *Array_##nome##_criar(unsigned int tamanho_bloco);\
	Array_status Array_##nome##_push(Array_##nome *array, tipo dado);\
	Array_status Array_##nome##_limpar(Array_##nome *array);

// Implementação

#define Array_define(nome,tipo)\
	Array_##nome *Array_##nome##_criar(unsigned int tamanho_bloco){\
		Array_##nome *array = (Array_##nome *)malloc(sizeof(Array_##nome));\
		if(array == NULL) return NULL;\
		array->data = NULL;\
		array->tamanho = 0;\
		array->tamanho_bloco = tamanho_bloco;\
	}\
	\
	Array_status Array_##nome##_push(Array_##nome *array, tipo dado){\
		if(array == NULL) return ARRAY_ERRO;\
		\
		tipo *tmp;\
		if(array->data == NULL){\
			array->data = (tipo *)malloc(array->tamanho_bloco*sizeof(tipo));\
		}\
		else if(array->tamanho % array->tamanho_bloco == 0){\
			tmp = (tipo *)realloc(array->data,(array->tamanho/array->tamanho_bloco+1)*array->tamanho_bloco*sizeof(tipo));\
			if(tmp != NULL){\
				array->data = tmp;\
			}\
			else {\
				return ARRAY_ERRO;\
			}\
		}\
		array->data[array->tamanho] = dado;\
		array->tamanho++;\
		return ARRAY_OK;\
	}\
	\
	Array_status Array_##nome##_limpar(Array_##nome *array){\
		if(array == NULL) return ARRAY_ERRO;\
		if(array->data != NULL) free(array->data);\
		free(array);\
		return ARRAY_OK;\
	}\

// Conversor de macro para struct array

#define Array(nome) Array_##nome


#endif
