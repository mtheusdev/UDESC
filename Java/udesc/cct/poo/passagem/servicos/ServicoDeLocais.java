package udesc.cct.poo.passagem.servicos;
import java.util.ArrayList;

import udesc.cct.poo.passagem.modelos.Local;
import udesc.cct.poo.passagem.repositorios.RepositorioDeLocais;

public class ServicoDeLocais{
    private RepositorioDeLocais repositorioDeLocais;

    public ServicoDeLocais(){
        this.repositorioDeLocais = new RepositorioDeLocais();
    }

    public ArrayList<Local> getTodosOsLocais(){
        return this.repositorioDeLocais.getTodosOsLocais();
    }
}
