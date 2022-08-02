package MYC;

import javax.jws.WebService;

@WebService(endpointInterface = "MYC.WSCoberturasServer")
public class WSCoberturasServerImpl implements WSCoberturasServer {

	public String getCobertura(String name) {
		return "Cobertura de " + name + " entregue!";
	}

}
