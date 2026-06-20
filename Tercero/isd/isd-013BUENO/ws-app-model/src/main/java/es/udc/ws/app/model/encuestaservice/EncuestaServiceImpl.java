package es.udc.ws.app.model.encuestaservice;

import es.udc.ws.app.model.encuesta.Encuesta;
import es.udc.ws.app.model.encuesta.SqlEncuestaDao;
import es.udc.ws.app.model.encuesta.SqlEncuestaDaoFactory;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaCanceladaException;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaFinalizadaException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.app.model.respuesta.Respuesta;
import es.udc.ws.app.model.respuesta.SqlRespuestaDao;
import es.udc.ws.app.model.respuesta.SqlRespuestaDaoFactory;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.sql.DataSourceLocator;
import es.udc.ws.util.validation.PropertyValidator;

import java.time.LocalDateTime;

import javax.sql.DataSource;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;
import java.util.Random;

import static es.udc.ws.app.model.util.ModelConstants.APP_DATA_SOURCE;

public class EncuestaServiceImpl implements EncuestaService
{
    private final DataSource dataSource;
    private SqlEncuestaDao encuestaDao = null;
    private SqlRespuestaDao respuestaDao = null;

    public EncuestaServiceImpl()
    {
        dataSource = DataSourceLocator.getDataSource(APP_DATA_SOURCE);
        encuestaDao = SqlEncuestaDaoFactory.getDao();
        respuestaDao = SqlRespuestaDaoFactory.getDao();
    }

    @Override
    public Encuesta crearEncuesta(Encuesta encuesta) throws InputValidationException
    {

        PropertyValidator.validateMandatoryString("pregunta", encuesta.getPregunta());
        if (encuesta.getFechaFin() == null || !encuesta.getFechaFin().isAfter(LocalDateTime.now())) {
            throw new InputValidationException("La fecha de finalización debe ser futura y no nula.");
        }

        encuesta.setFechaCreacion(LocalDateTime.now());
        encuesta.setCancelada(false);

        encuesta.setRepuestasPositivas(0);
        encuesta.setRespuestasNegativas(0);


        try (Connection connection = dataSource.getConnection())
        {
            try
            {
                connection.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
                connection.setAutoCommit(false);

                Encuesta encuestaCreada = encuestaDao.create(connection, encuesta);
                encuesta.setId(encuestaCreada.getId());
                connection.commit();

            } catch (SQLException e) {
                connection.rollback();
                throw new RuntimeException(e);
            } catch (RuntimeException | Error e) {
                connection.rollback();
                throw e;
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return encuesta;
    }


    @Override
    public List<Encuesta> obtenerEncuestas(String keyword, boolean incluirPasadas)
    {
        try (Connection connection = dataSource.getConnection())
        {
            return encuestaDao.findByKeyword(connection, keyword, incluirPasadas);
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Encuesta obtenerInformacion(long encuestaId) throws InstanceNotFoundException
    {
        /*
        Devuelve:
        - fecha de creación
        - Empleados que respondieron afirmativamente
        - Empleados que respondieron negativamente
        - Si la encuesta ha sido cancelada
        */
        try(Connection connection = dataSource.getConnection())
        {
            Encuesta encuesta = encuestaDao.find(connection, encuestaId);
            return encuesta;
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }


    @Override
    public Respuesta responder(long encuestaId, String email, boolean voto) throws InstanceNotFoundException, EncuestaFinalizadaException, InputValidationException, EncuestaCanceladaException
    {
        LocalDateTime horaRespuesta = LocalDateTime.now().withNano(0);
        Respuesta respuesta =  null;
        Encuesta encuesta = null;

        try(Connection connection = dataSource.getConnection())
        {
            try
            {
                connection.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
                connection.setAutoCommit(false);

                respuesta = respuestaDao.findByEmail(connection, encuestaId, email);

                encuesta = encuestaDao.find(connection, encuestaId);

                if (encuesta.getFechaFin().isBefore(horaRespuesta))
                {
                    connection.rollback();
                    throw new EncuestaFinalizadaException(encuestaId, encuesta.getFechaFin());
                }
                if (encuesta.isCancelada())
                {
                    connection.rollback();
                    throw new EncuestaCanceladaException(encuestaId);
                }

                if(respuesta == null)
                {
                    respuesta = new Respuesta(encuestaId, email, voto);
                    respuestaDao.create(connection, respuesta);
                    if(voto)
                        encuesta.setRepuestasPositivas(encuesta.getRepuestasPositivas() + 1);
                    else
                        encuesta.setRespuestasNegativas(encuesta.getRespuestasNegativas() + 1);

                    encuestaDao.update(connection, encuesta);

                    connection.commit();
                    return respuesta;
                }
                else
                {
                    if(voto)
                    {
                        encuesta.setRepuestasPositivas(encuesta.getRepuestasPositivas() + 1);
                        encuesta.setRespuestasNegativas(encuesta.getRespuestasNegativas() - 1);
                    }
                    else
                    {
                        encuesta.setRespuestasNegativas(encuesta.getRespuestasNegativas() + 1);
                        encuesta.setRepuestasPositivas(encuesta.getRepuestasPositivas() - 1);
                    }

                    respuesta.setFechaRespuesta(horaRespuesta);
                    respuesta.setPositiva(voto);

                    respuestaDao.update(connection, respuesta);
                    encuestaDao.update(connection, encuesta);
                    connection.commit();
                    return respuesta;
                }
            }
            catch (InstanceNotFoundException e)
            {
                connection.rollback();
                throw e;
            }
            catch (SQLException e)
            {
                connection.rollback();
                throw new RuntimeException(e);
            }
            catch (RuntimeException e)
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

    @Override
    public Encuesta cancelarEncuesta(long encuestaId) throws InstanceNotFoundException, EncuestaFinalizadaException, EncuestaCanceladaException {

        try (Connection connection = dataSource.getConnection()) {
            try {
                connection.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
                connection.setAutoCommit(false);

                Encuesta e = encuestaDao.find(connection, encuestaId);


                if (e == null) {               
                    connection.commit();
                    throw new InstanceNotFoundException(encuestaId, Encuesta.class.getName());
                }
                if (e.isCancelada()) {
                    connection.commit();
                    throw new EncuestaCanceladaException(encuestaId);
                }
                LocalDateTime now = LocalDateTime.now().withNano(0);
                if (!e.getFechaFin().isAfter(now)) {
                    connection.commit();
                    throw new EncuestaFinalizadaException(encuestaId, e.getFechaFin());
                }

                e.setCancelada(true);
                encuestaDao.update(connection, e);

                connection.commit();
                return e;

            } catch (InstanceNotFoundException | EncuestaCanceladaException |EncuestaFinalizadaException ex) {
                connection.commit();
                throw ex;
            } catch (SQLException ex) {
                connection.rollback();
                throw new RuntimeException(ex);
            } catch (RuntimeException | Error ex) {
                connection.rollback();
                throw ex;
            }finally {
                try {
                    connection.setAutoCommit(true);
                } catch (SQLException ignore) {}
            }

        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        }
    }

    @Override
    public List<Respuesta> obtenerRespuestas(long encuestaId, boolean soloPositivas) throws InstanceNotFoundException {
        try (Connection connection = dataSource.getConnection())
        {
            encuestaDao.find(connection, encuestaId);

            return respuestaDao.findByEncuesta(connection, encuestaId, soloPositivas);

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}