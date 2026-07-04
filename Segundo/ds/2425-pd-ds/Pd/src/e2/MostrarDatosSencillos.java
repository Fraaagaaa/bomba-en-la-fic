package e2;

public class MostrarDatosSencillos implements MostrarDatos {
    @Override
    public void mostrarDatos(AccionBase accion) {
        System.out.println("Feche: " + accion.feche());
    }
}
