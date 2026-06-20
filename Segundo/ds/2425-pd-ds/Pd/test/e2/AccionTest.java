package e2;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AccionTest {

    private AccionBase accion;

    @BeforeEach
    void setUp() {
        accion = new AccionBase("AAPL", 150, 155, 145, 5000);
    }

    @Test
    void testMostrarDatosDetallados() {

        AccionBase accionNula = new AccionBase(null, 150, 155, 145, 5000);
        AccionBase accionMax = new AccionBase("AQJWNJWED", 150, 155, 145, 5000);
        assertThrows(IllegalArgumentException.class, () -> accionNula.nomeAccion());
        assertThrows(IllegalArgumentException.class, () -> accionMax.nomeAccion());

        Cliente clienteDetallado = new Cliente("Cliente Detallado", new MostrarDatosDetallados());

        // Gardamos a saida estándar na variable saida
        java.io.ByteArrayOutputStream saida = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(saida));
        
        // O cliente mostra os datos
        clienteDetallado.mostrarDatos(accion);

        String resultadoEsperado = "Símbolo: AAPL, Feche: 150, Máximo: 155, Mínimo: 145, Volume: 5000\n";
        assertEquals(resultadoEsperado, saida.toString());
    }

    @Test
    void testMostrarDatosSencillos() {
        Cliente clienteSencillo = new Cliente("Cliente Sencillo", new MostrarDatosSencillos());

        // Collemos a saida estándar
        java.io.ByteArrayOutputStream saida = new java.io.ByteArrayOutputStream();
        System.setOut(new java.io.PrintStream(saida));

        // O cliente mostra os datos
        clienteSencillo.mostrarDatos(accion);

        String resultadoEsperado = "Feche: 150\n";
        assertEquals(resultadoEsperado, saida.toString());
    }

    @Test
    void testActualizarDatosAccion() {

        // Cambio os datos da acción principal
        accion = new AccionBase("AAPL", 160, 165, 150, 5200);

        // Verificamos que os datos se actualizaron correctamente
        assertEquals(160, accion.feche());
        assertEquals(165, accion.maximo());
        assertEquals(150, accion.minimo());
        assertEquals(5200, accion.volume());
    }
}
