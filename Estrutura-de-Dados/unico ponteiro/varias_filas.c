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
	Fila* filas[NUMERO_DE_CAIXAS];

// Criação de dois ponteiros, um para struct Caixa e um para Fila, cada um sendo um vetor de 5 structs, ou seja será criado 5 caixas distintos e 5 filas distintas.

	for(int i =0;i<NUMERO_DE_CAIXAS;i++){
		caixas[i] = criar_caixa();
		filas[i] = criar_fila();
	}
// loop que roda 5 vezes alocando todas as filas e todos os caixas.
	int i = 0;
	while(i<NUMERO_DE_CLIENTES){
		int j = 0;
		while(j<NUMERO_DE_CAIXAS && i<NUMERO_DE_CLIENTES){
			colocar_fila(filas[j], clientes[i]);
			j++;
			i++;
		}
	}
// Essa parte do programa colocará os clientes nas filas, distribuindo-os nas 5 filas criadas.
	int temGenteEmUmCaixa = 0;
	int temGenteEmUmaFila = 0;
// Seta as variaveis temGenteEmUmCaixa e temGenteEmUmaFila como 0 para dar inicio a execução.

	for(int i =0;i<NUMERO_DE_CAIXAS;i++){
		if(esta_livre_caixa(caixas[i]) == 0){
			temGenteEmUmCaixa = 1;
			break;
		}
	}

	for(int i =0;i<NUMERO_DE_CAIXAS;i++){
		if(esta_vazia_fila(filas[i]) == 0){
			temGenteEmUmaFila = 1;
			break;
		}
	}
// Os dois loops acima servem para verificar se tem gente em um determinado caixa ou em uma determinada fila, caso tenha, a variavel anteriormente setada como 0 é atrubuida o valor 1.
	while(temGenteEmUmCaixa == 1 || temGenteEmUmaFila == 1){
	 	temGenteEmUmCaixa = 0;
	 	temGenteEmUmaFila = 0;
// loop que verifica se há alguem no mercado verificando se tem alguem na fila ou alguem no caixa (em algum deles)

		for(int i =0;i<NUMERO_DE_CAIXAS;i++){
			if(esta_livre_caixa(caixas[i]) == 1){
				printf("caixa %i livre\n",i+1);

				if(esta_vazia_fila(filas[i]) == 0){
					int x = retirar_fila(filas[i]);

					printf("um cliente com %i itens foi chamado\n",x);

					iniciar_atendimento_caixa(&caixas[i], x);
					printf("caixa %i iniciou atendimento\n\n",i+1);
						// verifica os caixas, se algum estiver livre, este recebe um cliente que esta na fila, e a fila perde o primeiro cliente, utilizando a função retirar_fila.
				}
			}else{
				processar_item_caixa(&caixas[i]);
				//caso tal caixa ter um cliente, é chamada a função processar_item_caixa.
			}
		}

		for(int i =0;i<NUMERO_DE_CAIXAS;i++){
			if(esta_livre_caixa(caixas[i]) == 0){
				temGenteEmUmCaixa = 1;
				break;
			}
		}

		for(int i =0;i<NUMERO_DE_CAIXAS;i++){
			if(esta_vazia_fila(filas[i]) == 0){
				temGenteEmUmaFila = 1;
				break;
			}
		}
// Estes dois loops servem para mostrar se há um cliente em fila tal ou em caixa tal.
		tempo++;
		printf("temGenteEmUmCaixa %i\n",temGenteEmUmCaixa);
		printf("tempo atendendo: %i\n",tempo);
		printf("--------------------\n\n");
	}

	printf("TEMPO: %i\n",tempo);
	
	return 0;
}
