package MYC;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.xml.ws.Endpoint;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public interface WSRecepcaoServer {

	@WebMethod
	public void setServer(Integer nclients);
	//public static void setEndpoint(Endpoint myep);
	public int getNroClient() throws Exception;
	public void endClient() throws Exception;
	public void teste() throws Exception;
	public void testConnectionEndpoints() throws Exception;
	public void setEndpoints(String host) throws Exception;
	public void printReport() throws Exception;
	public void api_getPandelo(String name) throws Exception;
	public void api_getCorte(String name) throws Exception;
	public void api_getCobertura(String name) throws Exception;
	public void api_getRecheio(String name) throws Exception;
}
