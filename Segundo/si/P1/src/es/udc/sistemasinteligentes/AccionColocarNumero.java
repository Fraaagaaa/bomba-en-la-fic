package es.udc.sistemasinteligentes;

import java.util.HashSet;
import java.util.Set;

public class AccionColocarNumero extends Accion {
    private final int fila;
    private final int col;
    private final int valor;

    public AccionColocarNumero(int fila, int col, int valor) {
        this.fila = fila;
        this.col = col;
        this.valor = valor;
    }

    @Override
    public String toString() {
        return String.format("Colocar %d en (%d, %d)", valor, fila, col);
    }

    @Override
    public boolean esAplicable(Estado es) {
        EstadoCuadradoMagico estado = (EstadoCuadradoMagico) es;
        // La acción es aplicable si la casilla está vacía (0)
        return estado.getTablero()[fila][col] == 0;
    }

    @Override
    public Estado aplicaA(Estado es) {
        EstadoCuadradoMagico estado = (EstadoCuadradoMagico) es;
        int n = estado.getTablero().length;

        // Clonamos el tablero para mantener la inmutabilidad
        int[][] nuevoTablero = new int[n][n];
        for (int i = 0; i < n; i++) {
            nuevoTablero[i] = estado.getTablero()[i].clone();
        }

        // Aplicamos el cambio
        nuevoTablero[fila][col] = valor;

        // Actualizamos el conjunto de números disponibles
        Set<Integer> nuevosRestantes = new HashSet<>(estado.getNumerosRestantes());
        nuevosRestantes.remove(valor);

        return new EstadoCuadradoMagico(nuevoTablero, nuevosRestantes);
    }
}