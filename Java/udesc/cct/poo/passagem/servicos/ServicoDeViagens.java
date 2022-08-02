package udesc.cct.poo.passagem.servicos;

import java.util.ArrayList;

import udesc.cct.poo.passagem.modelos.Local;
import udesc.cct.poo.passagem.modelos.Viagem;
import udesc.cct.poo.passagem.repositorios.RepositorioDeViagens;

public class ServicoDeViagens{
    private RepositorioDeViagens repositorioDeViagens;

    public ServicoDeViagens(){
        this.repositorioDeViagens = new RepositorioDeViagens();
    }

    public ArrayList<Viagem> getTodosAsViagens(){
        return this.repositorioDeViagens.getTodasAsViagens();
    }

    public ArrayList<Viagem> getTodasAsViagensPorOrigemDestino(Local origem, Local destino){
        return this.repositorioDeViagens.getViagensPorOrigemDestino(origem.getNome(), destino.getNome());
    }
}
