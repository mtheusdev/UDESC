#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

typedef struct n{
	int i;
	struct n* proximo;
} No;


Fila* criar_fila(){ //Escopo da função
	Fila* f = malloc(sizeof(Fila)); //cria um ponteiro para a struct
	f->ultimo= NULL; //ponteiro da struct que aponta pra fila, apontará para Null nesse caso
	f->primeiro = NULL; // Mesma ação da linha anterior
	return f;// retorna o ponteiro criado
}

void colocar_fila(Fila* f, int i){

	No *n = malloc(sizeof(No)); // Cria um ponteiro para a struct
	n->proximo  = NULL; // faz esse ponteiro  com o atributo dentro da struct apontar para nullç;
	n->i = i; //o atributo(i) da struct recebe um inteiro

	if(f->primeiro == NULL){ //se for null, é o primeiro da fila

		f->primeiro = n; //o primeiro recebera o ponteiro da struct apontada
		n->proximo = NULL; // apontara para a proxima struct que nao existe por enquanto
		f->ultimo = n; //ultimo recebera o ponteiro que acabou de ser criado

	}else{//esse caso sera quando a fila nao for a primeira vez
		f->ultimo->proximo = n;//o ponteiro consegue mexer com atributos do nó, sendo assim, meu ultimo proximo recebera o ponteiro criada;
		f->ultimo = n; // o ponteiro ultimo recebera n;
	}



}
int retirar_fila(Fila* f){
	No *aux = f->primeiro;
	int i = aux->i;
	f->primeiro = aux->proximo;
	free(aux);
	return i;

}

int esta_vazia_fila(Fila* f){
	//função para verificar se a fila esta vazia, se sim retorna 1, senao retorna 0

	if(f->primeiro== NULL) return 1;
	else 	return 0;
}

void destruir_fila(Fila* f){
	No* aux = f->ultimo;
	while(aux->proximo != NULL){
		No* n = aux;
		aux = aux->proximo;
		free(n);
	}
	free(f->ultimo);
	free(f);
}// função que destroi a fila, faz-se isso percorrendo a fila com um loop, e dando free em cada uma das structs
//do primeiro até o ultimo cliente da fila, e quando chega no ultimo, aplicamos mais dois free's, um paara destruir a ultima struct
// e outro para destruir o ponteiro do tipo fila (f).
