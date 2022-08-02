
typedef struct caixa
{
	int ocupado;
	int total_itens;
	int atual_itens;
} Caixa;

Caixa* criar_caixa();

void iniciar_atendimento_caixa(Caixa** c, int quantidade);

int esta_livre_caixa(Caixa* c);

void processar_item_caixa(Caixa** c);

