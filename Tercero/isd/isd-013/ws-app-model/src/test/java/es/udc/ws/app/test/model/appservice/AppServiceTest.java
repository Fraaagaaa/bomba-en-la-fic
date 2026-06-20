package es.udc.ws.app.test.model.appservice;

import es.udc.ws.app.model.encuesta.Encuesta;
import es.udc.ws.app.model.encuesta.SqlEncuestaDao;
import es.udc.ws.app.model.encuesta.SqlEncuestaDaoFactory;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaCanceladaException;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaFinalizadaException;
import es.udc.ws.app.model.respuesta.Respuesta;
import es.udc.ws.app.model.respuesta.SqlRespuestaDao;
import es.udc.ws.app.model.respuesta.SqlRespuestaDaoFactory;
import es.udc.ws.app.model.encuestaservice.EncuestaService;
import es.udc.ws.app.model.encuestaservice.EncuestaServiceFactory;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.util.sql.DataSourceLocator;
import es.udc.ws.util.sql.SimpleDataSource;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.List;

import static es.udc.ws.app.model.util.ModelConstants.APP_DATA_SOURCE;
import static org.junit.jupiter.api.Assertions.*;

public class AppServiceTest
{
    private static EncuestaService encuestaService = null;
    private static SqlEncuestaDao encuestaDao = null;
    private static SqlRespuestaDao respuestaDao = null;

    private final long ID_INEXISTENTE = -1;
    private final String EMAIL_PRUEBA = "user@test.com";

    @BeforeAll
    public static void init()
    {
        DataSource dataSource = new SimpleDataSource();
        DataSourceLocator.addDataSource(APP_DATA_SOURCE, dataSource);
        encuestaService = EncuestaServiceFactory.getService();
        encuestaDao = SqlEncuestaDaoFactory.getDao();
        respuestaDao = SqlRespuestaDaoFactory.getDao();
    }

    private Encuesta creadorDeEncuestas(String pregunta, LocalDateTime fechaFin) throws InputValidationException
    {
        Encuesta encuesta = new Encuesta(pregunta, fechaFin);
        return encuestaService.crearEncuesta(encuesta);
    }

    private Encuesta creadorDeEncuestasExpiradas(String pregunta)
    {
        Encuesta encuesta = new Encuesta(pregunta, LocalDateTime.now().withNano(0).minusDays(1));

        try (Connection connection = DataSourceLocator.getDataSource(APP_DATA_SOURCE).getConnection())
        {
            connection.setAutoCommit(false);
            try
            {
                Encuesta encuestaCreada = encuestaDao.create(connection, encuesta);
                connection.commit();
                return encuestaCreada;
            }
            catch (Exception e)
            {
                connection.rollback();
                throw new RuntimeException(e);
            }
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    private void eliminadorDeEncuestas(Encuesta encuesta)
    {
        if (encuesta == null)
            return;

        try (Connection connection = DataSourceLocator.getDataSource(APP_DATA_SOURCE).getConnection())
        {
            connection.setAutoCommit(false);
            try
            {
                encuestaDao.remove(connection, encuesta.getId());
                connection.commit();
            }
            catch (InstanceNotFoundException e)
            {
                connection.commit();
            }
            catch (Exception e)
            {
                connection.rollback();
                throw new RuntimeException(e);
            }
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Test
    public void testCrearEncuestaBasico() throws InputValidationException
    {
        Encuesta encuestaCreada = null;
        try
        {
            String pregunta = "Pregunta ejemplo";
            LocalDateTime fechaFin = LocalDateTime.now().withNano(0).plusDays(10);

            encuestaCreada = creadorDeEncuestas(pregunta, fechaFin);

            Encuesta encuestaDeBD = encuestaService.obtenerInformacion(encuestaCreada.getId());

            assertEquals(encuestaCreada, encuestaDeBD);

            assertNotNull(encuestaDeBD.getId());
            assertEquals(pregunta, encuestaDeBD.getPregunta());
            assertEquals(fechaFin, encuestaDeBD.getFechaFin());
            assertEquals(0, encuestaDeBD.getRepuestasPositivas());
            assertEquals(0, encuestaDeBD.getRespuestasNegativas());
            assertFalse(encuestaDeBD.isCancelada());
            assertNotNull(encuestaDeBD.getFechaCreacion());

        }
        catch (InstanceNotFoundException e)
        {
            fail("No se encontró la encuesta que se acaba de crear.");
        }
        finally
        {
            eliminadorDeEncuestas(encuestaCreada);
        }
    }

    @Test
    public void testCrearEncuestaFechaExpirada()
    {
        LocalDateTime fechaPasada = LocalDateTime.now().withNano(0).minusDays(1);
        Encuesta encuesta = new Encuesta("expirada", fechaPasada);

        assertThrows(InputValidationException.class, () -> {encuestaService.crearEncuesta(encuesta);});
    }

    @Test
    public void testBuscarEncuestaPorId() throws InputValidationException
    {
        Encuesta encuestaCreada = null;
        try
        {
            encuestaCreada = creadorDeEncuestas("busquedaPorId", LocalDateTime.now().withNano(0).plusDays(5));

            Encuesta encuestaEncontrada = encuestaService.obtenerInformacion(encuestaCreada.getId());
            assertEquals(encuestaCreada, encuestaEncontrada);

            assertThrows(InstanceNotFoundException.class, () -> {encuestaService.obtenerInformacion(ID_INEXISTENTE);});
        }
        catch (InstanceNotFoundException e)
        {
            fail("No se encontró la encuesta que se acaba de crear.");
        }
        finally
        {
            eliminadorDeEncuestas(encuestaCreada);
        }
    }

    @Test
    public void testBuscarEncuestas() throws InputValidationException
    {
        Encuesta e1 = null;
        Encuesta e2 = null;
        Encuesta e3 = null;

        try
        {
            e1 = creadorDeEncuestas("Nicki Nicole?", LocalDateTime.now().withNano(0).plusDays(1));
            e2 = creadorDeEncuestas("Sabe quien es Chrissy Costanza?", LocalDateTime.now().withNano(0).plusDays(2));
            e3 = creadorDeEncuestas("Ha leido la pregunta anterior sobre Chrissy?", LocalDateTime.now().withNano(0).plusDays(3));

            List<Encuesta> encontradas = encuestaService.obtenerEncuestas("Chrissy", true);

            assertEquals(2, encontradas.size());
            assertFalse(encontradas.contains(e1));
            assertTrue(encontradas.contains(e2));
            assertTrue(encontradas.contains(e3));
        } finally
        {
            eliminadorDeEncuestas(e1);
            eliminadorDeEncuestas(e2);
            eliminadorDeEncuestas(e3);
        }
    }

    @Test
    public void testResponderEncuesta()
    {
        Encuesta encuesta = null;
        try
        {
            encuesta = creadorDeEncuestas("Test Responder", LocalDateTime.now().withNano(0).plusDays(1));

            Respuesta respuesta = encuestaService.responder(encuesta.getId(), EMAIL_PRUEBA, true);

            assertNotNull(respuesta.getRespuestaId());
            assertEquals(encuesta.getId(), respuesta.getEncuestaId());
            assertEquals(EMAIL_PRUEBA, respuesta.getEmail());
            assertTrue(respuesta.isPositiva());

            Encuesta encuestaActualizada = encuestaService.obtenerInformacion(encuesta.getId());
            assertEquals(1, encuestaActualizada.getRepuestasPositivas());
            assertEquals(0, encuestaActualizada.getRespuestasNegativas());

            assertThrows(InstanceNotFoundException.class, () -> { encuestaService.responder(ID_INEXISTENTE, EMAIL_PRUEBA, true); });

        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(encuesta);
        }
    }

    @Test
    public void testCambiarRespuestaEncuesta()
    {
        Encuesta encuesta = null;
        try
        {
            encuesta = creadorDeEncuestas("Test Cambio Respuesta", LocalDateTime.now().withNano(0).plusDays(1));
            final long encuestaId = encuesta.getId();

            Respuesta respuestaInicial = encuestaService.responder(encuestaId, EMAIL_PRUEBA, true);
            assertTrue(respuestaInicial.isPositiva());

            Respuesta respuestaFinal = encuestaService.responder(encuestaId, EMAIL_PRUEBA, false);
            assertFalse(respuestaFinal.isPositiva());

            assertEquals(respuestaInicial.getRespuestaId(), respuestaFinal.getRespuestaId());


        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada al intentar cambiar la respuesta: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(encuesta);
        }
    }

    @Test
    public void testEncuestaExpirada()
    {
        Encuesta encuestaExpirada = null;
        try
        {
            encuestaExpirada = creadorDeEncuestasExpiradas("Encuesta Expirada");
            final long encuestaId = encuestaExpirada.getId();
            assertThrows(EncuestaFinalizadaException.class, () -> {encuestaService.responder(encuestaId, EMAIL_PRUEBA, true);});
        }
        finally
        {
            eliminadorDeEncuestas(encuestaExpirada);
        }
    }

    @Test
    public void testObtenerResultadosEncuesta()
    {
        Encuesta encuesta = null;
        try
        {
            encuesta = creadorDeEncuestas("Test Obtener Resultados", LocalDateTime.now().withNano(0).plusDays(1));

            Respuesta r1 = encuestaService.responder(encuesta.getId(), "user1@test.com", true);
            Respuesta r2 = encuestaService.responder(encuesta.getId(), "user2@test.com", false);
            Respuesta r3 = encuestaService.responder(encuesta.getId(), "user3@test.com", true);

            List<Respuesta> positivas = encuestaService.obtenerRespuestas(encuesta.getId(), true);
            assertEquals(2, positivas.size());
            assertTrue(positivas.contains(r1));
            assertFalse(positivas.contains(r2));
            assertTrue(positivas.contains(r3));

            List<Respuesta> todas = encuestaService.obtenerRespuestas(encuesta.getId(), false);
            assertEquals(3, todas.size());
            assertTrue(todas.contains(r1));
            assertTrue(todas.contains(r2));
            assertTrue(todas.contains(r3));

            assertThrows(InstanceNotFoundException.class, () -> {
                encuestaService.obtenerRespuestas(ID_INEXISTENTE, false);
            });

        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(encuesta);
        }
    }

    @Test
    public void testBuscarEncuestasNoIncluyeCanceladasNiExpiradas()
    {
        Encuesta activa = null;
        Encuesta cancelada = null;
        Encuesta expirada = null;

        try
        {
            activa = creadorDeEncuestas("Encuesta Activa", LocalDateTime.now().withNano(0).plusDays(2));
            cancelada = creadorDeEncuestas("Encuesta Cancelada", LocalDateTime.now().withNano(0).plusDays(2));
            expirada = creadorDeEncuestasExpiradas("Encuesta Expirada"); // Creada con fecha de ayer

            encuestaService.cancelarEncuesta(cancelada.getId());

            List<Encuesta> encontradas = encuestaService.obtenerEncuestas("", false);

            assertEquals(2, encontradas.size());
            assertTrue(encontradas.contains(activa));
            assertFalse(encontradas.contains(cancelada));
            assertFalse(encontradas.contains(expirada));

        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(activa);
            eliminadorDeEncuestas(cancelada);
            eliminadorDeEncuestas(expirada);
        }
    }

    @Test
    public void testEncuestaCancelada()
    {
        Encuesta encuesta = null;
        try
        {
            encuesta = creadorDeEncuestas("Encuesta para cancelar", LocalDateTime.now().withNano(0).plusDays(2));

            encuestaService.cancelarEncuesta(encuesta.getId());
            final long encuestaId = encuesta.getId();

            assertThrows(EncuestaCanceladaException.class, () -> {
                encuestaService.responder(encuestaId, EMAIL_PRUEBA, true);
            });
        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(encuesta);
        }
    }

    @Test
    public void testContarVotosEncuesta()
    {
        Encuesta encuesta = null;
        try
        {
            encuesta = creadorDeEncuestas("test contar votos", LocalDateTime.now().withNano(0).plusDays(1));

            encuestaService.responder(encuesta.getId(), "miguel", true);
            encuestaService.responder(encuesta.getId(), "pedro", true);
            encuestaService.responder(encuesta.getId(), "Rabbit", false);
            encuestaService.responder(encuesta.getId(), "Eminem", true);
            encuestaService.responder(encuesta.getId(), "8mile", false);

            List<Respuesta> todasLasRespuestas = encuestaService.obtenerRespuestas(encuesta.getId(), false);

            long respuestasPositivas = todasLasRespuestas.stream().filter(Respuesta::isPositiva).count();
            long respuestasNegativas = todasLasRespuestas.stream().filter(r -> !r.isPositiva()).count();

            assertEquals(3, respuestasPositivas);
            assertEquals(2, respuestasNegativas);

        }
        catch (Exception e)
        {
            fail("Se produjo una excepción inesperada: " + e.getMessage());
        }
        finally
        {
            eliminadorDeEncuestas(encuesta);
        }
    }

    @Test
    public void testCancelarDosVeces() {
        Encuesta e = null;
        try {
            e = creadorDeEncuestas("Cancelar dos veces", LocalDateTime.now().withNano(0).plusDays(1));
            long id = e.getId();

            Encuesta cancelada = encuestaService.cancelarEncuesta(id);
            assertTrue(cancelada.isCancelada(), "La encuesta debe quedar cancelada");


            Encuesta leida = encuestaService.obtenerInformacion(id);
            assertTrue(leida.isCancelada(), "Debe mantenerse cancelada en BD");


            assertThrows(EncuestaCanceladaException.class, () -> encuestaService.cancelarEncuesta(id));

        } catch (Exception ex) {
            fail("Se produjo una excepción inesperada: " + ex.getMessage());
        } finally {
            eliminadorDeEncuestas(e);
        }
    }

    @Test
    public void testCancelarFinalizada() {
        Encuesta e = null;
        try {
            e = creadorDeEncuestasExpiradas("Cancelar finalizada");
            final long id = e.getId();

            assertThrows(EncuestaFinalizadaException.class, () -> encuestaService.cancelarEncuesta(id));

        } catch (Exception ex) {
            fail("Se produjo una excepción inesperada: " + ex.getMessage());
        } finally {
            eliminadorDeEncuestas(e);
        }
    }

    @Test
    public void testObtenerRespuestasVacia() {
        Encuesta e = null;
        try {
            e = creadorDeEncuestas("Sin respuestas aún", LocalDateTime.now().withNano(0).plusDays(1));
            List<Respuesta> vacia = encuestaService.obtenerRespuestas(e.getId(), false);
            assertTrue(vacia.isEmpty(), "Debe devolver lista vacía si nadie respondió");

        } catch (Exception ex) {
            fail("Se produjo una excepción inesperada: " + ex.getMessage());
        } finally {
            eliminadorDeEncuestas(e);
        }
    }

    @Test
    public void testObtenerRespuestasTrasCancelarYFinalizar() {
        Encuesta e = null;
        try {
            e = creadorDeEncuestas("Persistencia de respuestas", LocalDateTime.now().withNano(0).plusDays(1));
            long id = e.getId();

            encuestaService.responder(id, "u1@test.com", true);
            encuestaService.responder(id, "u2@test.com", false);


            encuestaService.cancelarEncuesta(id);
            List<Respuesta> trasCancelar = encuestaService.obtenerRespuestas(id, false);
            assertEquals(2, trasCancelar.size(), "Cancelada: lectura debe seguir funcionando");


            try (Connection c = DataSourceLocator.getDataSource(APP_DATA_SOURCE).getConnection();
                 var ps = c.prepareStatement("UPDATE Encuesta SET fechaFin = NOW() - INTERVAL 1 SECOND WHERE encuestaId = ?")) {
                ps.setLong(1, id);
                ps.executeUpdate();
            }

            List<Respuesta> trasFinalizar = encuestaService.obtenerRespuestas(id, false);
            assertEquals(2, trasFinalizar.size(), "Finalizada: lectura debe seguir funcionando");

        } catch (Exception ex) {
            fail("Se produjo una excepción inesperada: " + ex.getMessage());
        } finally {
            eliminadorDeEncuestas(e);
        }
    }
}