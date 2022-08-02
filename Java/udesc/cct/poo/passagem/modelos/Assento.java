package udesc.cct.poo.passagem.modelos;
public class Assento{
    public static int LEITO = 0;
    public static int SEMILEITO = 1;
    public static int CONVENCIONAL = 2;

    private int tipo;
    private int numero;
    private boolean reservado;

    public Assento(int tipo, int numero){
        this.reservado = false;
        this.tipo = tipo;
        this.numero = numero;
    }

    public int getTipo(){
        return this.tipo;
    }

    public int getNumero(){
        return this.numero;
    }

    public boolean estaDesocupado(){
        return !this.reservado;
    }
    public void reservar(){
        this.reservado = true;
    }
}
