package MYC;

import java.net.URL;
import java.net.InetAddress;
import javax.xml.namespace.QName;
import java.util.concurrent.TimeUnit;
import javax.xml.ws.Service;
import javax.xml.ws.Endpoint;
import java.util.*;
import java.io.*;

public class ServerPublisher {
	static void readSetup (String host, WSRecepcaoServer srecepcao) {

		try {
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
					case "NClientes":
					      	srecepcao.setServer(Integer.parseInt(word[2]));
							srecepcao.setEndpoints(host); // Setando acesso aos endpoints na recepcao
					      	break;
					default:
						// System.out.println("Ignorado: ("+word[0]+")");
				}
			}
			sc.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {

		String host = args[0];

		System.out.println("* SERVER: Beginning to publish WS Servers ("+host+") *");

		// WS Recepcao
		Endpoint ep = Endpoint.create(new WSRecepcaoServerImpl());
		ep.publish("http://"+host+":4732/WSRecepcao");

		// WS Pandelo
		Endpoint ep_pan = Endpoint.create(new WSPandeloServerImpl());
		ep_pan.publish("http://"+host+":4733/WSPandelo");

		// WS Cortes
		Endpoint ep_cor = Endpoint.create(new WSCortesServerImpl());
		ep_cor.publish("http://"+host+":4734/WSCortes");

		// WS Recheios
		Endpoint ep_rec = Endpoint.create(new WSRecheiosServerImpl());
		ep_rec.publish("http://"+host+":4735/WSRecheios");

		// WS Coberturas
		Endpoint ep_cob = Endpoint.create(new WSCoberturasServerImpl());
		ep_cob.publish("http://"+host+":4736/WSCoberturas");


		System.out.println("* All done publishing. *");

		try {
			// ##### WS Recepcao  #####
			URL url1 = new URL("http://"+host+":4732/WSRecepcao?wsdl");
			QName qname1 = new QName("http://MYC/","WSRecepcaoServerImplService");
			Service recepcao = Service.create(url1, qname1);
			WSRecepcaoServer srecepcao = recepcao.getPort(WSRecepcaoServer.class);
			InetAddress addr = InetAddress.getLocalHost();
			String hostname = addr.getHostName();
			readSetup(host, srecepcao);
			Boolean flag = true;

			while (flag) { // Pooling aguardando clientes

        	TimeUnit.SECONDS.sleep(1);
				if (srecepcao.getNroClient() <= 0) {
					System.out.println("* Server End *");
					flag = false;
					srecepcao.printReport();
					ep.stop();
					ep_pan.stop();
					ep_cor.stop();
					ep_rec.stop();
					ep_cob.stop();
				}
			}


		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
