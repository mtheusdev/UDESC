
typedef struct fila{
	struct n* ultimo;
} Fila;

Fila* criar_fila();

void colocar_fila(Fila* f, int i);

int retirar_fila(Fila* f);

int esta_vazia_fila(Fila* f);

void destruir_fila(Fila* f);
