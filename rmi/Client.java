/** HelloClient.java **/
import java.io.*;
import java.util.*;
import java.rmi.registry.*;
import java.net.InetAddress;

public class Client {

  public static void main(String[] args) {
    String host = (args.length < 1) ? null : args[0];
    Scanner sc = new Scanner(System.in);
  
    try {
      // Obtém uma referência para o registro do RMI
      Registry registry = LocateRegistry.getRegistry(host,6600);

      // Obtém a stub do servidor
      BolsaGeometrica stub= (BolsaGeometrica) registry.lookup("myRMIBG");

      InetAddress addr = InetAddress.getLocalHost();
      String hostname = addr.getHostName();

      int linha_cliente = (2 * Integer.parseInt(args[1])) + 8;
      String sCurrentLine = sc.nextLine();

      for(int i = 0; i < linha_cliente; i++){
        sCurrentLine = sc.nextLine();
      }

      BufferedReader inFromUser
      = new BufferedReader(new InputStreamReader(System.in));
      String[] word = sCurrentLine.split(" ");
      String peca_cliente = new String(word[2]);

      sCurrentLine = sc.nextLine();
      word = sCurrentLine.split(" ");
      int qtd_peca_cliente = Integer.parseInt(word[2]);

      for(int j = 0; j < qtd_peca_cliente; j++){
        stub.consumirPeca(peca_cliente);
      }

      System.out.println("##  Cliente ("+hostname+") "+args[1]+"  ##");
      System.out.println("Status: atendido por "+args[0]);
      System.out.println("pCli: " + peca_cliente);
      System.out.println("###########");

      sc.close();
      stub.endClient();
    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }
}
