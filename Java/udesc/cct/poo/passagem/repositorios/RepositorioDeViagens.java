package udesc.cct.poo.passagem.repositorios;

import java.util.ArrayList;

import udesc.cct.poo.passagem.modelos.Assento;
import udesc.cct.poo.passagem.modelos.Local;
import udesc.cct.poo.passagem.modelos.Parada;
import udesc.cct.poo.passagem.modelos.Viagem;

public class RepositorioDeViagens{
    private ArrayList<Viagem> viagens;

    public RepositorioDeViagens(){
        this.viagens = new ArrayList<Viagem>();

        Viagem v = this.criarViagemConvencional();
        Local l1 = new Local("Joinville","SCa");
        Parada x1 = new Parada(l1,10,10);
        v.addParada(x1);

        Local l2 = new Local("Garuva","SC");
        Parada x2 = new Parada(l2,10,40);
        v.addParada(x2);

        Local l3 = new Local("Curitiba","PR");
        Parada x3 = new Parada(l3,12,20);
        v.addParada(x3);

        this.viagens.add(v);

        Viagem v2 = this.criarViagemConvencional();
        Parada x6 = new Parada(l1,11,10);
        v2.addParada(x6);

        Parada x4 = new Parada(l2,11,40);
        v2.addParada(x4);

        Parada x5 = new Parada(l3,13,20);
        v2.addParada(x5);

        this.viagens.add(v2);

    }
    public ArrayList<Viagem> getTodasAsViagens(){
        return this.viagens;
    }

    public ArrayList<Viagem> getViagensPorOrigemDestino(String origem, String destino){
        ArrayList<Viagem> selecionadas = new ArrayList<Viagem>();

        for(int i = 0;i<this.viagens.size();i++){
            Viagem viagem = this.viagens.get(i);
            boolean passaPelaOrigem = viagem.passaPor(origem);
            boolean passaPeloDestino = viagem.passaPor(destino);
            if(passaPelaOrigem && passaPeloDestino){
                selecionadas.add(viagem);
            }
        }
        return selecionadas;
    }
    private Viagem criarViagemConvencional(){
    	Viagem v = new Viagem();
    	 for(int i =0;i<42;i++){
             Assento a = new Assento(Assento.CONVENCIONAL, i+1);
             v.addAssento(a);
         }

    	return v;
    }    
}
