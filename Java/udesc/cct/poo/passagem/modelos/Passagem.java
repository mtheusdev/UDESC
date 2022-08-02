package udesc.cct.poo.passagem.modelos;

public class Passagem{
    private Passageiro passageiro;
    private Viagem viagem;
    private Local origem;
    private Local destino;

    public Passagem(Viagem viagem, Local origem, Local destino){
        this.viagem = viagem;
        this.origem = origem;
        this.destino = destino;
    }
}
