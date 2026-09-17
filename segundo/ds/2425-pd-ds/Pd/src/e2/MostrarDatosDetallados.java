package e2;

public class MostrarDatosDetallados implements MostrarDatos {
    @Override
    public void mostrarDatos(AccionBase accion) {
        System.out.println("Símbolo: " + accion.nomeAccion()
                + ", Feche: " + accion.feche()
                + ", Máximo: " + accion.maximo()
                + ", Mínimo: " + accion.minimo()
                + ", Volume: " + accion.volume());
    }
}
