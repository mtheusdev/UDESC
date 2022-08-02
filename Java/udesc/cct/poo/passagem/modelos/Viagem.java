package udesc.cct.poo.passagem.modelos;
import java.util.ArrayList;

public class Viagem{
    private ArrayList<Parada> itinerario;
    ArrayList<Assento> assentos;

    public Viagem(){
        this.itinerario = new  ArrayList<Parada>();
        this.assentos = new ArrayList<Assento>();
    }
    public void addAssento(Assento a){
        this.assentos.add(a);
    }
    public void addParada(Parada p){
        this.itinerario.add(p);
    }

    public ArrayList<Parada> getItinerario(){
        return this.itinerario;
    }
    public ArrayList<Assento> getAssentos(){
        return this.assentos;
    }
    public ArrayList<Assento> getAssentosLivres(){
        ArrayList<Assento> livres = new ArrayList<Assento>();
        for(int i =0;i<this.assentos.size();i++){
            Assento a = this.assentos.get(i);
            boolean desocupado = a.estaDesocupado();
            if( desocupado ){
                livres.add(a);
            }
        }
        return livres;
    }

    public boolean passaPor(String local){
        for(int i =0;i<this.itinerario.size();i++){
            Parada p = this.itinerario.get(i);
            if( local.equals(p.getNome()) ){
                return true;
            }
        }
        return false;
    }
    
    public Parada getParadaPorNome(String nome){
        for(int i=0;i<this.itinerario.size();i++){
            Parada p = this.itinerario.get(i);
            String paradaNome = p.getNome();
            if(paradaNome.equals(nome)){
                return p;
            }
        }
        return null;
    }
}
