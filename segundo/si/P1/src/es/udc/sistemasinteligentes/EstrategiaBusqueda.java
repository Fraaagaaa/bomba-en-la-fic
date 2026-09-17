package es.udc.sistemasinteligentes;

import java.lang.reflect.Array;

public interface EstrategiaBusqueda {
    /**
     * Soluciona el problema de búsqueda, obteniendo un estado meta o arrojando una Excepcion si no encuentra una
     * @param p Problema a solucionar
     * @return Estado meta obtenido
     */
    public abstract Nodo[] soluciona(ProblemaBusqueda p) throws Exception;
}