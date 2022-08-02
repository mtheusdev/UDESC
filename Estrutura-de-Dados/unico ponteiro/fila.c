#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

typedef struct n{
	int i;
	struct n* proximo;
} No;
// struct Nó contendo um ponteiro e o conteudo, nesse caso, um inteiro que representará o tempo que certo cliente ficará no caixa


Fila* criar_fila(){
	Fila* f = malloc(sizeof(Fila));
	f->ultimo= NULL;
	return f;
} // essa função cria uma fila, faz isso alocando um ponteiro do tipo struct fila, setando-o para NULL  e retornando-o.

void colocar_fila(Fila* f, int i){
//funcao que coloca os clientes em fila.
	No* n = malloc(sizeof(No)); // aloca-se uma struct Nó.
	n->i = i; // atribuimos o valor "i" recebido pela funçao ao inteiro i da struct Nó anteriormente alocada.

	if(f->ultimo == NULL){
		f->ultimo = n;

		n->proximo = NULL;
	} /* na condição acima, faz-se uma verificação se o ponteiro da fila está apontando para NULL, caso estiver,
		 esse ponteiro irá receber o endereço de n (Nó alocado), e o ponteiro contido no Nó receberá NULL..
		 (condição que serve para quando a fila ainda nao conter ninguem, ou seja para quando a fila estiver vazia)*/
	else{
		No* aux = f->ultimo;
		f->ultimo = n;

		n->proximo = aux;
		/*Caso a fila ja conter alguem (algum nó), criamos um ponteiro para um nó auxiliar  que recebe o endereço
		do ultimo nó da fila (conteudo recebido pela função), tendo esse endereço guardado, agora podemos setar como
		ultimo nó a struct nó anteriormente alocada, após esse passo, oque nos resta é apenas colocarmos nosso
		nó armazenado na struc auxiliar no ponteiro n->proximo, seguindo esses passos, teremos sempre teremos uma fila
		ordenada corretamente nunca perdendo a sequencia correta dos clientes na fila.
		 */
	}

}

int retirar_fila(Fila* f){

	No* aux = f->ultimo;
	int i;

	if(aux->proximo == NULL){
		i = aux->i;

		free(aux);
		f->ultimo = NULL;
		return i;
	}/* nessa função, retiraremos clientes da fila quando for solicitado, para isso, inciamos guardando o ponteiro
		da fila que atualmente esta apontando para o ultimo cliente da fila, alem de criar uma variavel para armazenar
		inteiros, apos isso o programa entra em uma condição que verifica se o ponteiro do nó está apontando para NULL,
		pois se estiver, significa que a fila contem apenas um cliente), se entrar nessa condiçao, o programa guarda
		o conteudo do nó(inteiro) na variavel i, desaloca a struct nó com a função free, seta o ponteiro da fila para NULL
		e retorna o conteudo i;
		(a fila fica vazia novamente)
	*/

	while(aux->proximo->proximo != NULL){

		 aux = aux->proximo;
	}

	No* aux1 = aux->proximo;
	i = aux1 -> i;
	aux->proximo = NULL;
	free(aux1);
	return i;
	/* o programa avança e econtra um looping, que serve para percorrer a fila do ultimo cliente até o segundo
	 e quando o encontra, armazena-o em um nó auxiliar anteriormente setado,(faz-se isso para nao perder as suas informações)
	 em seguida, criamos mais um nó auxliar (aux1) no qual usamos para armazenar o primeiro cliente da fila, em seguida
	 armazenamos em i o conteudo do primeiro cliente, setamos o ponteiro do primeiro auxiliar á NULL (fazemos isso para
	 definique que agora o segundo torna-se o primeiro da fila) e finalmente destruimos a struct do primeiro cliente com
	 o free(aux1) alem de retornarmos o conteudo deste.

	 */
	
}

int esta_vazia_fila(Fila* f){

	if(f->ultimo== NULL) return 1;
	else 	return 0;

	//função para verificar se a fila esta vazia, se sim retorna 1, senao retorna 0
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
