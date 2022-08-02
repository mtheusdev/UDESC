package udesc.cct.poo.passagem.modelos;
public class Local{
    public String nome;
    public String estado;

    public Local(String nome, String estado){
        this.nome = nome;
        this.estado = estado;
    }

    public String getNome(){
        return this.nome;
    }
    public String getEstao(){
        return this.estado;
    }
}
