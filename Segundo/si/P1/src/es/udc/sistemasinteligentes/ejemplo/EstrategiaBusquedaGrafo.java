package es.udc.sistemasinteligentes.ejemplo;

import es.udc.sistemasinteligentes.*;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class EstrategiaBusquedaGrafo implements EstrategiaBusqueda
{
    @Override
    public Nodo[] soluciona(ProblemaBusqueda p) throws Exception
    {
        Nodo nodoActual = new Nodo(p.getEstadoInicial(), null, null);
        ArrayList<Estado> explorados = new ArrayList<>();

        Queue<Nodo> frontera = new LinkedList<>();
        frontera.add(nodoActual);

        Estado sc;
        Accion[] accionesDisponibles;

        System.out.println("\nBúsqueda grafo\n");

        while (!frontera.isEmpty())
        {
            // System.out.println(i++ + ". ");
            nodoActual = frontera.remove();
            explorados.add(nodoActual.estado);

            accionesDisponibles = p.acciones(nodoActual.estado);
            for(Accion accion : accionesDisponibles)
            {
                sc = p.result(nodoActual.estado, accion);

                // Añadimos los estados a la frontera
                if(!explorados.contains(sc))
                    frontera.add(new Nodo(sc, nodoActual, accion));

                // Si cualquiera de los estados es meta terminamos
                if(p.esMeta(sc))
                {
                    nodoActual = new Nodo(sc, nodoActual, accion);
                    return reconstruye_sol(nodoActual);
                }
            }
        }
        throw new Exception("No se ha podido encontrar una solución");
    }

    public Nodo[] reconstruye_sol(Nodo n)
    {
        ArrayList<Nodo> solucion = new ArrayList<>();
        Nodo a = n;
        while(a != null)
        {
            solucion.add(a);
            a = a.padre;
        }
        return solucion.toArray(new Nodo[0]);
    }
}