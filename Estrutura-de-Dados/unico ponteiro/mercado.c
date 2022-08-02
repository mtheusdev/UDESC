#include <stdlib.h>
#include <stdio.h>

#include "mercado.h"

Caixa* criar_caixa(){
	Caixa* c = malloc(sizeof(Caixa));
	c->ocupado = 0;
	c->total_itens = 0;
	c->atual_itens = 0;
	return c;
}
// funcao que cria um caixa, primeiramente a funcao aloca um ponteiro do tipo struct caixa, seta todos os itens da struct como 0 e retorna o ponteiro

void iniciar_atendimento_caixa(Caixa** c, int quantidade){
	(*c)->ocupado = 1;
	(*c)->total_itens = quantidade;
}
// essa funcao, recebe um caixa, seta-o como ocupado e atribui a varivel total itens o valor que foi enviado a funcao.
int esta_livre_caixa(Caixa* c){
	if(c->ocupado == 0) return 1;
	else return 0;
}
//essa funcao verifica se o caixa esta livre, se sim, retorna 1, senao retorna 0.

void processar_item_caixa(Caixa** c){
	(*c)->atual_itens++;
	if((*c)->atual_itens ==
	(*c)->total_itens){
		(*c)->ocupado = 0;
		(*c)->total_itens = 0;
		(*c)->atual_itens = 0;
	}
}
// essa funcao inicia somando em uma inidade na variavel atual_itens, apos isso verifica se a quantidade de intens atuais é igual ao total de itens, caso for igual, a funcao seta todos os itens da struct como 0.
