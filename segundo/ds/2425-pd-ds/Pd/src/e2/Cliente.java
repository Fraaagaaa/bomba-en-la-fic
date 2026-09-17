package e2;

public class Cliente implements MostrarDatos{

    private final String nombreCliente;
    private final MostrarDatos mostrarDatos;

    public Cliente(String nombreCliente, MostrarDatos mostrarDatos) {
        this.nombreCliente = nombreCliente;
        this.mostrarDatos = mostrarDatos;
    }

    @Override
    public void mostrarDatos(AccionBase accion) {
        mostrarDatos.mostrarDatos(accion);
    }
}
