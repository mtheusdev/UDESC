package MYC;

import javax.jws.WebService;

@WebService(endpointInterface = "MYC.WSCortesServer")
public class WSCortesServerImpl implements WSCortesServer {

	public String getCorte(String name) {
		return "Corte " + name + " efetuado!";
	}

}
