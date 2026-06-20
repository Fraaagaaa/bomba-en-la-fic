package e1;

import java.util.ArrayList;
import java.util.List;

public class CrearFlota extends FlotaBase
{
    protected final String nombreFlota;
    protected final List<ObservadorInterfaz> observers = new ArrayList<>();

    public CrearFlota(String nombreFlota, int fondos)
    {
        super(nombreFlota, fondos);
        this.nombreFlota = nombreFlota;
    }

    @Override
    public String toString()
    {
        return nombreFlota;
    }

    @Override
    public void addObservador(ObservadorInterfaz observer)
    {
        observers.add(observer);
    }

    @Override
    public void removeObservador(ObservadorInterfaz observer)
    {
        observers.remove(observer);
    }

    @Override
    public void notifyObservador(String message)
    {
        for (ObservadorInterfaz observer : observers)
            observer.update(message);
    }
}