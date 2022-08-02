package MYC;

import javax.jws.WebService;

@WebService(endpointInterface = "MYC.WSRecheiosServer")
public class WSRecheiosServerImpl implements WSRecheiosServer {

	public String getRecheio(String name) {
		return "Recheio de " + name + " entregue!";
	}

}
