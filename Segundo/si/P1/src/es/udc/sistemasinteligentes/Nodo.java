package es.udc.sistemasinteligentes;

public class Nodo {
    public Estado estado;
    public Nodo padre;
    public Accion accion;

    public Nodo (Estado estado, Nodo padre, Accion accion) {
        this.estado = estado;
        this.padre = padre;
        this.accion = accion;
    }
}
