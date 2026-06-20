package es.udc.sistemasinteligentes;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class ProblemaCuadradoMagico extends ProblemaBusqueda {
    private final int n;
    private final int constanteMagica;

    public ProblemaCuadradoMagico(int n) {
        // Invocamos al constructor padre con el estado inicial
        super(crearEstadoInicial(n));
        this.n = n;
        this.constanteMagica = n * (n * n + 1) / 2;
    }

    private static Estado crearEstadoInicial(int n) {
        int[][] tableroInicial = new int[n][n];
        Set<Integer> disponibles = new HashSet<>();
        for (int i = 1; i <= n * n; i++) {
            disponibles.add(i);
        }
        return new EstadoCuadradoMagico(tableroInicial, disponibles);
    }

    @Override
    public boolean esMeta(Estado es) {
        EstadoCuadradoMagico estado = (EstadoCuadradoMagico) es;
        int[][] t = estado.getTablero();

        if (!estado.getNumerosRestantes().isEmpty()) return false;

        for (int i = 0; i < n; i++) {
            int sumaFila = 0;
            int sumaCol = 0;
            for (int j = 0; j < n; j++) {
                sumaFila += t[i][j];
                sumaCol += t[j][i];
            }
            if (sumaFila != constanteMagica || sumaCol != constanteMagica) return false;
        }

        int d1 = 0, d2 = 0;
        for (int i = 0; i < n; i++)
        {
            d1 += t[i][i];
            d2 += t[i][n - 1 - i];
        }

        return d1 == constanteMagica && d2 == constanteMagica;
    }
    @Override
    public Accion[] acciones(Estado es)
    {
        EstadoCuadradoMagico estado = (EstadoCuadradoMagico) es;
        int[][] tablero = estado.getTablero();
        List<Accion> listaAcciones = new ArrayList<>();

        int filaDestino = -1;
        int colDestino = -1;

        buscarCasilla:
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (tablero[i][j] == 0) {
                    filaDestino = i;
                    colDestino = j;
                    break buscarCasilla;
                }
            }
        }

        if (filaDestino == -1) {
            return new Accion[0];
        }
        for (Integer valor : estado.getNumerosRestantes()) {
            listaAcciones.add(new AccionColocarNumero(filaDestino, colDestino, valor));
        }

        return listaAcciones.toArray(new Accion[0]);
    }
}