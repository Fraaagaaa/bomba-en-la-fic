package e1;

public interface Sujeto
{
    void addObservador(ObservadorInterfaz observer);
    void removeObservador(ObservadorInterfaz observer);
    void notifyObservador(String message);
}