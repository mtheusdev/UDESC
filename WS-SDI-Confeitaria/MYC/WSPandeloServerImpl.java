package MYC;

import javax.jws.WebService;

@WebService(endpointInterface = "MYC.WSPandeloServer")
public class WSPandeloServerImpl implements WSPandeloServer {

	public String getPandelo(String name) {
		return "Pandelo de " + name + " entregue!";
	}

}
