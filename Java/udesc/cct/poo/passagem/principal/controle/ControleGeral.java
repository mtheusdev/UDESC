package udesc.cct.poo.passagem.controle;
import java.util.Scanner;
import java.util.ArrayList;

import udesc.cct.poo.passagem.modelos.Local;
import udesc.cct.poo.passagem.servicos.ServicoDeLocais;
import udesc.cct.poo.passagem.servicos.ServicoDePassagens;
import udesc.cct.poo.passagem.servicos.ServicoDeViagens;

public class ControleGeral{
	public final static int FILTRAR_POR_ESTADO= 3;
	public final static int LISTAR_LOCAIS= 2;
    public final static int MARCAR_PASSAGEM = 1;
    public final static int SAIR = 0;

    private Scanner scanner;

    private ServicoDeLocais servicoDeLocais;
    private ServicoDeViagens servicoDeViagens;
    private ServicoDePassagens servicoDePassagens;

    private ControleMarcarPassagem marcarPassagem;

    public ControleGeral(){
        this.scanner = new Scanner(System.in);
        this.servicoDeLocais = new ServicoDeLocais();
        this.servicoDeViagens = new ServicoDeViagens();
        this.servicoDePassagens = new ServicoDePassagens();

        this.marcarPassagem = new ControleMarcarPassagem(
        		this.scanner, 
        		this.servicoDeLocais, 
        		this.servicoDeViagens, 
        		this.servicoDePassagens);
    }

    public void iniciar(){
        int escolha = -1;
        String estado;
        while(escolha != ControleGeral.SAIR){
        	ArrayList<Local> local;
        	local = servicoDeLocais.getTodosOsLocais();
            System.out.println("Escolha algo:");
            System.out.println( ControleGeral.FILTRAR_POR_ESTADO +") Filtrar local por estado");
            System.out.println( ControleGeral.LISTAR_LOCAIS +") Listar locais atendidos");
            System.out.println( ControleGeral.MARCAR_PASSAGEM+") Marcar passagem");
            System.out.println( ControleGeral.SAIR+") Sair");
            
            escolha = this.scanner.nextInt();

            switch(escolha){
                case ControleGeral.MARCAR_PASSAGEM:
                    this.marcarPassagem.iniciar();
                break;
                case ControleGeral.LISTAR_LOCAIS:
                	this.marcarPassagem.listarLocais(local);
                break;
                case ControleGeral.FILTRAR_POR_ESTADO:
                	System.out.println("Digite a siga do estado desejado: Exemplo(SC)");
                	estado = this.scanner.next();
           
                	this.marcarPassagem.filtrarEstado(local, estado);
            }
        }
    }
}

