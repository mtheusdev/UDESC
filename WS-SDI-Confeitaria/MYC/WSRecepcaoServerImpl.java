package MYC;

import javax.jws.WebService;
import javax.xml.ws.Endpoint;
import java.util.*;
import java.io.*;

import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;

@WebService(endpointInterface = "MYC.WSRecepcaoServer")
public class WSRecepcaoServerImpl implements WSRecepcaoServer {

  private static int NClientes = 0;
  private static int totalClients = 0;
  private static int totalPandelos = 0;
  private static int totalCoberturas = 0;
  private static int totalRecheios = 0;
  private static int totalCortes = 0;
  private static int totalRecepcao = 0;
  private static String Host;

  private static URL urlpandelo;
  private static Service pandelo;
  private static WSPandeloServer spandelo;
  private static QName qnamepandelo;

  private static URL urlcortes;
  private static Service cortes;
  private static WSCortesServer scortes;
  private static QName qnamecortes;

  private static URL urlcoberturas;
  private static Service coberturas;
  private static WSCoberturasServer scoberturas;
  private static QName qnamecoberturas;

  private static URL urlrecheios;
  private static Service recheios;
  private static WSRecheiosServer srecheios;
  private static QName qnamerecheios;

  public void setEndpoints(String host) throws Exception {

    try {
      Host = host;

      urlpandelo = new URL("http://"+host+":4733/WSPandelo?wsdl");
      qnamepandelo = new QName("http://MYC/","WSPandeloServerImplService");
      pandelo = Service.create(urlpandelo, qnamepandelo);
      spandelo = pandelo.getPort(WSPandeloServer.class);

      urlcortes = new URL("http://"+host+":4734/WSCortes?wsdl");
      qnamecortes = new QName("http://MYC/","WSCortesServerImplService");
      cortes = Service.create(urlcortes, qnamecortes);
      scortes = cortes.getPort(WSCortesServer.class);

      urlrecheios = new URL("http://"+host+":4735/WSRecheios?wsdl");
      qnamerecheios = new QName("http://MYC/","WSRecheiosServerImplService");
      recheios = Service.create(urlrecheios, qnamerecheios);
      srecheios = recheios.getPort(WSRecheiosServer.class);

      urlcoberturas = new URL("http://"+host+":4736/WSCoberturas?wsdl");
      qnamecoberturas = new QName("http://MYC/","WSCoberturasServerImplService");
      coberturas = Service.create(urlcoberturas, qnamecoberturas);
      scoberturas = coberturas.getPort(WSCoberturasServer.class);

    } catch (Exception e) {
			e.printStackTrace();
		}
  }

  public void endClient() throws Exception {
    NClientes--;
  }

  public int getNroClient() throws Exception {
    return(NClientes);
  }

  public static void setNroClient(int nclients) throws Exception {
    NClientes = nclients;
    totalClients = nclients;
  }

  public void api_getPandelo(String name) throws Exception {
    try {
      spandelo.getPandelo(name);
      totalPandelos ++;
      totalRecepcao ++;
    } catch (Exception e) {
			e.printStackTrace();
		}
  }

  public void api_getCorte(String name) throws Exception {
    try {
      scortes.getCorte(name);
      totalCortes ++;
      totalRecepcao ++;
    } catch (Exception e) {
			e.printStackTrace();
		}
  }

  public void api_getCobertura(String name) throws Exception {
    try {
      scoberturas.getCobertura(name);
      totalCoberturas ++;
      totalRecepcao ++;
    } catch (Exception e) {
			e.printStackTrace();
		}
  }

  public void api_getRecheio(String name) throws Exception {
    try {
      srecheios.getRecheio(name);
      totalRecheios ++;
      totalRecepcao ++;
    } catch (Exception e) {
			e.printStackTrace();
		}
  }

  public void teste() throws Exception {
    System.out.println("TESTE");
  }

  public void testConnectionEndpoints() throws Exception {
    spandelo.getPandelo("teste pandelo");
  }

  public void printReport() throws Exception {
    System.out.println("##  Servidor  ##");
    System.out.println("Status: finalizado");
    System.out.println("Nro_clientes_atendidos: "+totalClients);
    System.out.println("WS-Pandelo ("+Host+"): "+totalPandelos);
    System.out.println("WS-Cobertura ("+Host+"): "+totalCoberturas);
    System.out.println("WS-Recheio ("+Host+"): "+totalRecheios);
    System.out.println("WS-Cortes ("+Host+"): "+totalCortes);
    System.out.println("WS-Recepcao ("+Host+"): "+totalRecepcao);
    System.out.println("###########");
	}

  public void setServer(Integer nclients) {
    //System.out.println("["+nclients+"]");
    try {
      setNroClient(nclients);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

}
