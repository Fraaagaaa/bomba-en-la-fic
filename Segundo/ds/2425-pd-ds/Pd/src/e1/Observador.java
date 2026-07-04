package e1;

public class Observador implements ObservadorInterfaz
{
    @Override
    public void update(String message)
    {
        System.out.println("NOTIFICACIÓN: " + message);
    }
}