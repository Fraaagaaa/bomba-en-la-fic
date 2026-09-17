package es.udc.sistemasinteligentes.ejemplo;

import es.udc.sistemasinteligentes.*;

public class Main {

    public static void main(String[] args) throws Exception
    {
        ProblemaAspiradora.EstadoAspiradora estadoInicial = new ProblemaAspiradora.EstadoAspiradora(ProblemaAspiradora.EstadoAspiradora.PosicionRobot.IZQ,
                ProblemaAspiradora.EstadoAspiradora.PosicionBasura.AMBAS);
        ProblemaBusqueda aspiradora = new ProblemaAspiradora(estadoInicial);

        EstrategiaBusqueda buscador = new Estrategia4();
        Nodo[] solucion = buscador.soluciona(aspiradora);

        for (int i = solucion.length - 1; i >= 0; i--)
            if (solucion[i] != null)
                System.out.println(solucion[i].estado);


        buscador = new EstrategiaBusquedaGrafo();
        solucion = buscador.soluciona(aspiradora);

        for (int i = solucion.length - 1; i >= 0; i--)
            if (solucion[i] != null)
                System.out.println(solucion[i].estado);


        ProblemaBusqueda problema = new ProblemaCuadradoMagico(3);
        BuscadorProfundidad buscador2 = new BuscadorProfundidad();

        System.out.println("Buscando solución...");
        Estado resultado = buscador2.solucion(problema);

        if (resultado != null) {
            System.out.println("¡Cuadrado Mágico encontrado!");
            System.out.println(resultado.toString());
        } else {
            System.out.println("No se encontró solución.");
        }
    }

}
