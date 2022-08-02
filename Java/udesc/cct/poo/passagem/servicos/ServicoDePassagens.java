package udesc.cct.poo.passagem.servicos;

import java.util.ArrayList;
import udesc.cct.poo.passagem.modelos.Passagem;

public class ServicoDePassagens {
	private ArrayList<Passagem> passagens;
	
	public ServicoDePassagens() {
		this.passagens = new ArrayList<Passagem>();
	}
	
	public void addPassagem(Passagem p) {
		this.passagens.add(p);
	}
	public ArrayList<Passagem> getTodasAsPassagens(){
        return this.passagens;
    }
}
