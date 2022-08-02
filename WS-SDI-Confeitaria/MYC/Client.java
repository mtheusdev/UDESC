package MYC;

import java.net.URL;
import java.net.InetAddress;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import javax.xml.ws.Endpoint;
import java.util.*;
import java.io.*;


public class Client {

  public static void main(String[] args) {
    int totalPandelosClient = 0;
    int totalCoberturasClient = 0;
    int totalRecheiosClient = 0;
    int totalCortesClient = 0;
    int totalRecepcaoClient = 0;
    Boolean clientfinalizado = false;
    Boolean flagUser = false;

    try {

      String host = (args.length < 1) ? "localhost" : args[0];
      if (args.length < 2) {
        System.out.println("ERROR: java MYC.Client <host_server> <name>");
        System.exit(1);
      }

      // ##### WS Recepcao  #####
      URL url1 = new URL("http://"+host+":4732/WSRecepcao?wsdl");
      QName qname1 = new QName("http://MYC/","WSRecepcaoServerImplService");
      Service recepcao = Service.create(url1, qname1);
      WSRecepcaoServer srecepcao = recepcao.getPort(WSRecepcaoServer.class);
      String name1 = args[1];
      InetAddress addr = InetAddress.getLocalHost();
      String hostname = addr.getHostName();

      Scanner sc = new Scanner(System.in);
			while(true){
				if (!sc.hasNextLine()) {
					break;
				}
				String newline = sc.nextLine();
				BufferedReader inFromUser
				= new BufferedReader(new InputStreamReader(System.in));
				String[] word = newline.split(" ");

				switch (word[0]) {
					case "****":
            if (word[2].equals(name1)) {
              flagUser = true;
            }else {
              flagUser = false;
            }
            break;
          case "WS-Pandelo":
            if (flagUser) {
              srecepcao.api_getPandelo(word[2]);
              totalPandelosClient++;
            }
            break;
          case "WS-Recheio":
            if (flagUser) {
              srecepcao.api_getRecheio(word[2]);
              totalRecheiosClient++;
            }
            break;
          case "WS-Cortes":
            if (flagUser) {
              srecepcao.api_getCorte(word[2]);
              totalCortesClient++;
            }
            break;
          case "WS-Cobertura":
            if (flagUser) {
              srecepcao.api_getCobertura(word[2]);
              totalCoberturasClient++;
            }
            break;
					default:
						// System.out.println("Ignorado: ("+word[0]+")");
				}
			}
			sc.close();


      srecepcao.endClient();

      // TALVEZ AQUI DE RUIM, (IF PANDELO = 0 NAO PRINTAR SEILA, verificar no BOCA)
      System.out.println("##  Cliente ("+hostname+") "+name1+"  ##");
      System.out.println("Status: Pronto");
      System.out.println("WS-Pandelo: " + totalPandelosClient);
      System.out.println("WS-Cobertura: " + totalCoberturasClient);
      System.out.println("WS-Recheio: " + totalRecheiosClient);
      System.out.println("WS-Cortes:" + totalCortesClient);
      System.out.println("###########");

    } catch (Exception e) {
      e.printStackTrace();
    }

  }

}
