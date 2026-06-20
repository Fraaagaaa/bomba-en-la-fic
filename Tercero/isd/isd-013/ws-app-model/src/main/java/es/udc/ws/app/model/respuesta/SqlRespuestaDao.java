package es.udc.ws.app.model.respuesta;

import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.sql.Connection;
import java.util.List;

public interface SqlRespuestaDao
{
    Respuesta create(Connection connection, Respuesta respuesta);

    Respuesta find(Connection conection, long encuestaId) throws InstanceNotFoundException;

    List<Respuesta> findByEncuesta(Connection connection, long encuestaId, boolean soloPositivas) throws InstanceNotFoundException;

    Respuesta findByEmail(Connection connection, long encuestaId, String email);

    void update(Connection conection, Respuesta respuesta) throws InstanceNotFoundException;

    void remove(Connection conection, long encuestaId) throws InstanceNotFoundException;
}
