package es.udc.sistemasinteligentes;

import java.util.Arrays;
import java.util.Collections;
import java.util.Set;

public class EstadoCuadradoMagico extends Estado {
    private final int[][] tablero;
    private final Set<Integer> numerosRestantes;

    public EstadoCuadradoMagico(int[][] tablero, Set<Integer> numerosRestantes) {
        this.tablero = tablero;
        // Mantenemos los números restantes para facilitar la generación de sucesores
        this.numerosRestantes = Collections.unmodifiableSet(numerosRestantes);
    }

    public int[][] getTablero() {
        return tablero;
    }

    public Set<Integer> getNumerosRestantes() {
        return numerosRestantes;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("\n");
        for (int[] fila : tablero) {
            sb.append(Arrays.toString(fila)).append("\n");
        }
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof EstadoCuadradoMagico that)) return false;
        return Arrays.deepEquals(tablero, that.tablero);
    }

    @Override
    public int hashCode() {
        return Arrays.deepHashCode(tablero);
    }
}