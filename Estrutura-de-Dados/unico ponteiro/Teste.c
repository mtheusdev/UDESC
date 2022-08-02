#include <stdlib.h>
#include <stdio.h>

#include "fila.h"

int main(void){
    Fila* teste = criar_fila();
    int i=0;
    for(;i<10;i++){
        colocar_fila(teste,i);
    }
    int x;
    while(esta_vazia_fila(teste) == 0){
        x = retirar_fila(teste);
        printf("%d\n",x);
    }
}
