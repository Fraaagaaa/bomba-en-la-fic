package es.udc.sistemasinteligentes.ejemplo;

import es.udc.sistemasinteligentes.*;

import java.util.ArrayList;

public class Estrategia4 implements EstrategiaBusqueda {

    public Estrategia4() {
    }

    @Override
    public Nodo[] soluciona(ProblemaBusqueda p) throws Exception
    {
        ArrayList<Estado> explorados = new ArrayList<Estado>();
        Nodo nodoActual = new Nodo(p.getEstadoInicial(), null, null);
        explorados.add(nodoActual.estado);

        int i = 1;
        Estado sc;
        boolean modificado;
        Accion[] accionesDisponibles;

//        System.out.println((i++) + " - Empezando búsqueda en " + nodoActual.estado);

        while (!p.esMeta(nodoActual.estado))
        {
//            System.out.println((i++) + " - " + nodoActual.estado + " no es meta");
            accionesDisponibles = p.acciones(nodoActual.estado);
            modificado = false;
            for (Accion acc: accionesDisponibles)
            {
                sc = p.result(nodoActual.estado, acc);
//                System.out.println((i++) + " - RESULT(" + nodoActual.estado + ","+ acc + ")=" + sc);

                if (!explorados.contains(sc))
                {
                    nodoActual = new Nodo(sc, nodoActual, acc);
//                    System.out.println((i++) + " - " + sc + " NO explorado");
                    explorados.add(sc);
                    modificado = true;
//                    System.out.println((i++) + " - Estado actual cambiado a " + nodoActual.estado);
                    break;
                }
//                else
//                    System.out.println((i++) + " - " + sc + " ya explorado");
            }
            if (!modificado) throw new Exception("No se ha podido encontrar una solución");
        }
//        System.out.println((i++) + " - FIN - " + nodoActual.estado);
        return reconstruye_sol(nodoActual);
    }

    public Nodo[] reconstruye_sol(Nodo n)
    {
        ArrayList<Nodo> solucion = new ArrayList<>();
        Nodo a = n;
        int i = 0;
        while(a != null)
        {
            solucion.add(a);
            a = a.padre;
            i++;
        }
        return solucion.toArray(new Nodo[0]);
    }
}