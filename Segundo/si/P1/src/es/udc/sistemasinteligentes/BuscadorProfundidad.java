package es.udc.sistemasinteligentes;

import java.util.*;

public class BuscadorProfundidad {

    public Estado solucion(ProblemaBusqueda problema) {
        // La frontera guarda los estados pendientes de explorar (Pila para DFS)
        Stack<Estado> frontera = new Stack<>();
        // El conjunto de explorados evita repetir estados
        Set<Estado> explorados = new HashSet<>();

        frontera.push(problema.getEstadoInicial());

        while (!frontera.isEmpty()) {
            Estado estadoActual = frontera.pop();

            // Si es la meta, terminamos
            if (problema.esMeta(estadoActual)) {
                return estadoActual;
            }

            explorados.add(estadoActual);

            // Generamos sucesores
            Accion[] accionesDisponibles = problema.acciones(estadoActual);
            for (Accion acc : accionesDisponibles) {
                Estado siguiente = problema.result(estadoActual, acc);

                if (!explorados.contains(siguiente) && !frontera.contains(siguiente)) {
                    frontera.push(siguiente);
                }
            }
        }
        return null; // No hay solución
    }
}