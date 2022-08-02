/** HelloWorld.java **/
import java.rmi.*;

public interface BolsaGeometrica extends Remote {
   public void endClient() throws RemoteException;
   public void consumirPeca(String peca) throws RemoteException;
}
