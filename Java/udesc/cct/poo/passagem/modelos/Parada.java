package udesc.cct.poo.passagem.modelos;
public class Parada{
    private Local local;
    private int hora;
    private int minuto;

    public Parada(Local local, int hora, int minuto){
        this.local = local;
        this.hora = hora;
        this.minuto = minuto;
    }

    public String getInfo(){
        String info = this.local.getNome() + " " + this.hora + ":"+this.minuto;
        return info;
    }

    public String getNome(){
        return this.local.getNome();
    }
}
