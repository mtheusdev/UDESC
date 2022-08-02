/** HelloServer.java **/

import java.io.*;
import java.rmi.*;
import java.net.*;
import java.util.*;
import java.rmi.server.*;
import java.rmi.registry.*;
import java.util.concurrent.TimeUnit;

public class BGServer implements BolsaGeometrica {
  public BGServer() {}

    private static int NClientes;
    private static int NPecas;
    private static int NEntregues;
    private static int NEsteiras;
    private static int NPrateleiras;
    private static int NPrimeiraPrat;
    private static int NDemaisPrateleiras;
    private static String[] pecas;
    private static ArrayList <String> pecas_entregues = new ArrayList <String>();
    private static ArrayList <String> estoque_final = new ArrayList <String>();
    private static ArrayList <ArrayList> matriz_esteiras = new ArrayList <ArrayList>();
    private static ArrayList <ArrayList> matriz_prateleiras = new ArrayList <ArrayList>();
    private static Registry registry;
    private static BolsaGeometrica stub;

    public static void setNroClient(int nclients) throws Exception {
      NClientes = nclients;
    }

    public static int getNroClient() throws Exception {
      return(NClientes);
    }

    public static void setNroPecas(int nPecas) throws Exception {
      NPecas = nPecas;
    }

    public static int getNroPecas() throws Exception {
      return(NPecas);
    }

    public static void setNroEsteiras(int nEsteiras) throws Exception {
      NEsteiras = nEsteiras;
    }

    public static int getNroEsteiras() throws Exception {
      return(NEsteiras);
    }

    public static void setNroPrateleiras(int nPrateleiras) throws Exception {
      NPrateleiras = nPrateleiras;
    }

    public static void setNroPrimeiraPrat(int valor) throws Exception {
      NPrimeiraPrat = valor;
    }

    public static void setNroDemaisPrateleiras(int valor) throws Exception {
      NDemaisPrateleiras = valor;
    }

    public static int getNroPrateleiras() throws Exception {
      return(NPrateleiras);
    }

    public static int getNroDemaisPrateleiras() throws Exception {
      return(NDemaisPrateleiras);
    }

    public static int getNroPrimeiraPrat() throws Exception {
      return(NPrimeiraPrat);
    }

    public static void setPecas(String[] lpecas) throws Exception {
      pecas = lpecas;
    }

    public static String getPeca(int posicao) throws Exception {
      return(pecas[posicao+1]);
    }
    
    public static void ordenarEPrintarMatrizEstoqueFinal() throws Exception {
      int aux_pecas = getNroPrimeiraPrat();
  
        for(int k = 0; k < getNroPrateleiras(); k ++){
          if(k != 0){
            aux_pecas = getNroDemaisPrateleiras();
          }
          for(int n = 0; n < aux_pecas; n++) { // Percorrendo pecas da prateleira
            if (!matriz_prateleiras.get(k).get(n).equals('!')) {
              estoque_final.add(matriz_prateleiras.get(k).get(n).toString());
            }
          }
        }

      Collections.sort(estoque_final);
      System.out.print("estoque:");
      for(int i = 0; i < estoque_final.size(); i++){
        System.out.print(" "+estoque_final.get(i));
      }
      System.out.println();
    }

    public static void ordenarEPrintarMatrizEntregas() throws Exception {
      Collections.sort(pecas_entregues);
      System.out.print("entregas:");
      for(int i = 0; i < pecas_entregues.size(); i++){
        System.out.print(" "+pecas_entregues.get(i));
      }
      System.out.println();
    }


    public static void setMatEsteiras(String[] prateleiras) throws Exception {
      int cont = 2;

      for(int i = 0; i < getNroEsteiras(); i ++){
        matriz_esteiras.add( new ArrayList<String>() );
      }

      for(int i = 0; i < getNroEsteiras(); i ++){
        String[] pt = prateleiras[cont].split("E");

        for(int j = 0; j < 2; j++) {
          String[] pt2 = pt[j].split("(?!^)");
          matriz_esteiras.get(i).add(pt2[1]);
        }
        cont++;
      }
    }

    public static void setMatPrateleiras(String[] prateleiras) throws Exception {
      int _npecas = getNroPecas();
      int _nprateleiras = getNroPrateleiras();
      int resto = _npecas % _nprateleiras;
      int pecas_primeira_prat = ((_npecas - resto) / _nprateleiras) + resto;
      int pecas_demais_prat = (_npecas - resto) / _nprateleiras;
      int aux_pecas = pecas_primeira_prat;
      int cont = 1;

      setNroPrimeiraPrat(pecas_primeira_prat);
      setNroDemaisPrateleiras(pecas_demais_prat);


      for(int i = 0; i < _nprateleiras; i ++){
        matriz_prateleiras.add( new ArrayList<String>() );
      }

      for(int i = 0; i < _nprateleiras; i ++){
        if(i != 0){
          aux_pecas = pecas_demais_prat;
        }
        for(int j = 0; j < aux_pecas; j++) {
          matriz_prateleiras.get(i).add(getPeca(cont));
          cont++;
        }
      }
    }

    public static void setServer () throws Exception {
      Scanner sc = new Scanner(System.in);
      while(true){
        if (!sc.hasNextLine()) {
          break;
        }
        String sCurrentLine = sc.nextLine();
        BufferedReader inFromUser
        = new BufferedReader(new InputStreamReader(System.in));
        String[] word = sCurrentLine.split(" ");
        switch (word[0]) {
          case "NClientes":
            setNroClient(Integer.parseInt(word[2]));
            break;
          case "NPecas":
            setNroPecas(Integer.parseInt(word[2]));
            break;
          case "NEsteira":
            setNroEsteiras(Integer.parseInt(word[2]));
            break;
          case "NPrateleira":
            setNroPrateleiras(Integer.parseInt(word[2]));
            break;
          case "pecas":
            setPecas(word);
            break;
          case "esteiras":
            setMatEsteiras(word);
            break;
          case "prateleiras":
            setMatPrateleiras(word);
            break;
          default:
          //System.out.println("Ignorado: ("+word[0]+")");
        }
      }
      sc.close();
    }

    public static void stopServer() {
      try {
        registry.unbind("myRMIBG");
        UnicastRemoteObject.unexportObject(registry,true);
      } catch (NoSuchObjectException e) {
        e.printStackTrace();
      } catch (NotBoundException e) {
        // e.printStackTrace();
      } catch (RemoteException ex) {
      }

    }

    static void printReport() {
      System.out.println("##  Servidor  ##");
      System.out.println("Status: finalizado");
      try{
        ordenarEPrintarMatrizEstoqueFinal();
      }catch (Exception e) {
        e.printStackTrace();
      }
      try{
        ordenarEPrintarMatrizEntregas();
      }catch (Exception e) {
        e.printStackTrace();
      }
    }

    public static void main(String[] args) {
      try {

        //System.out.println("Configurando servidor ...");
        setServer();
        // Instancia o objeto servidor e a sua stub
        BGServer server = new BGServer();
        //BolsaGeometrica stub = (BolsaGeometrica) UnicastRemoteObject.exportObject(server, 0);
        stub = (BolsaGeometrica) UnicastRemoteObject.exportObject(server, 0);
        // Registra a stub no RMI Registry para que ela seja obtAida pelos clientes
        registry = LocateRegistry.createRegistry(6600);
        //Registry registry = LocateRegistry.createRegistry(6600);
        //Registry registry = LocateRegistry.getRegistry(9999);
        registry.bind("myRMIBG", stub);

        //System.out.println("Servidor pronto:\n\t\tNroClientes:"+getNroClient()+"\n\t\tPecas:"+getNroPecas()+"\n");
      } catch (Exception ex) {
        ex.printStackTrace();
      }

      Boolean flag = true;
      while (flag) { // Pooling aguardando clientes

        try {
          TimeUnit.SECONDS.sleep(1);
          if (getNroClient() <= 0) {
            flag = false;
            printReport();
            stopServer();
            // ...
          }
        } catch (Exception ex) {
          ex.printStackTrace();
        }
      }
      System.exit(0);

    }
    // Métodos disponíveis via RMI
    public void consumirPeca(String peca) throws RemoteException {
      try {
        // System.out.println("Consegui entrar no server pelo cliente " + peca);
        int aux_pecas = getNroPrimeiraPrat();
        int cont = 0;

        for(int k = 0; k < getNroPrateleiras(); k ++){
          if(k != 0){
            aux_pecas = getNroDemaisPrateleiras();
          }
          for(int n = 0; n < aux_pecas; n++) { // Percorrendo pecas da prateleira
            if (matriz_prateleiras.get(k).get(n).equals(peca)) {
              matriz_prateleiras.get(k).set(n, '!');
              pecas_entregues.add(peca);
              cont ++;
              break;
            }
          }
          if (cont != 0) break;
        }
      } catch (Exception e) {
        e.printStackTrace();
      }
      
    }

    public void endClient() throws RemoteException {
      try {
        setNroClient(getNroClient()-1);
        //System.out.println("Clientes ativos = "+this.getNroClient());
        if (this.getNroClient()==0) {
          this.stopServer();
        }
      } catch (Exception e) {
        e.printStackTrace();
      }
    }

  }
