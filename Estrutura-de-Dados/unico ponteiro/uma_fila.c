#include <stdlib.h>
#include <stdio.h>

#include "clientes.h"

#include "mercado.h"
#include "fila.h"

#define NUMERO_DE_CAIXAS 5

int main(void){
	printf("mercado\n");
	int tempo = 0;

	Caixa* caixas[NUMERO_DE_CAIXAS];
	Fila* fila = criar_fila();
// criando um ponteiro do tipo fila...
	for(int i =0;i<NUMERO_DE_CLIENTES;i++){
		colocar_fila(fila, clientes[i]);
	}
// loop que enfileira os clientes por ordem de chegada..
	for(int i =0;i<NUMERO_DE_CAIXAS;i++){
		caixas[i] = criar_caixa();
	}
// loop que cria 5 caixas..
	int temGenteEmUmCaixa = 0;

	for(int i =0;i<NUMERO_DE_CAIXAS;i++){
		if(esta_livre_caixa(caixas[i]) == 0){
			temGenteEmUmCaixa = 1;
			break;
		}
	}
// loop for que roda 5 vezes com uma condiçao que verifica se um determinado caixa esta vazio, se sim, atribui o inteiro 1 na variavel temGenteEmUmCaixa.

	while(esta_vazia_fila(fila) == 0 || temGenteEmUmCaixa == 1){
		temGenteEmUmCaixa = 0;
// A seguir o programa entra no loop while que irá rodar enquanto a a fila conter clientes ou até todos os caixas ficarem vazios.


		for(int i =0;i<NUMERO_DE_CAIXAS;i++){
			if(esta_livre_caixa(caixas[i]) == 1){
				printf("caixa %i livre\n",i+1);

				if(esta_vazia_fila(fila) == 0){
					int x = retirar_fila(fila);

					printf("um cliente com %i itens foi chamado\n",x);

					iniciar_atendimento_caixa(&caixas[i], x);
					printf("caixa %i iniciou atendimento\n\n",i+1);
				}
			}else{

				processar_item_caixa(&caixas[i]);
			}
		}
// O programa segue e chega no for que roda 5 vezes ( NUMERO_DE_CAIXAS), segue e entra na condição que verifica se determinado caixa esta vazio ou contem um cliente
//caso esteja vazio, o programa printa que tal caixa esta vazio, apos isso entra em outra verificação, na qual se a fila conter algum cliente, este sera enviado a tal caixa vazio e a struct desse cliente sera retirada da fila.

		for(int i =0;i<NUMERO_DE_CAIXAS;i++){
			if(esta_livre_caixa(caixas[i]) == 0){
				temGenteEmUmCaixa = 1;
				break;
			}
		}
// Este loop sera executado 5 vezes novamente e entrara na condição de que se o caixa NAO estiver livre, seta-se 1 na variavel temGenteEmUmCaixa.
		tempo++;
		// soma em 1 no contador de tempo.
		printf("temGenteEmUmCaixa %i\n",temGenteEmUmCaixa);
		printf("fila vazia %i\n",esta_vazia_fila(fila));
		printf("tempo atendendo: %i\n",tempo);
		printf("--------------------\n\n");
	}
	printf("TEMPO: %i\n",tempo);

	return 0;
}
