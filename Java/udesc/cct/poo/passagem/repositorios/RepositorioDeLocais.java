package udesc.cct.poo.passagem.repositorios;
import java.util.ArrayList;

import udesc.cct.poo.passagem.helpers.LeitorDeArquivo;
import udesc.cct.poo.passagem.modelos.Local;

public class RepositorioDeLocais{
    private ArrayList<Local> locais = new ArrayList<Local>();

    public RepositorioDeLocais(){
        LeitorDeArquivo leitor = new LeitorDeArquivo("data/locais.csv");
        ArrayList<String> linhas= leitor.ler();

        for(int i =0;i<linhas.size()-1;i++){
        		String[] linhaSplit = linhas.get(i).split(";");
                String nome = linhaSplit[0];
                String estado = linhaSplit[1];
                Local l = new Local(nome,estado);
                locais.add(l);
             //   System.out.println(locais.get(i).estado);
        }
    }
    public ArrayList<Local> getTodosOsLocais(){
        return this.locais;
    }

    public Local getLocalPorNome(String nome){
        for(int i = 0;i<this.locais.size();i++){
            Local local = this.locais.get(i);
            String nomeDoLocal = local.getNome();
            if( nome.equals(nomeDoLocal) ){
                return local;
            }
        }
        return null;
    }
}
