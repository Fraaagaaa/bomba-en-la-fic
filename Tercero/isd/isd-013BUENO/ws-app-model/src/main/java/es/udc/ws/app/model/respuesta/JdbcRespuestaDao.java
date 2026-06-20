package es.udc.ws.app.model.respuesta;

import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.sql.*;
import java.util.List;

public class JdbcRespuestaDao extends AbstractSqlRespuestaDao
{
    @Override
    public Respuesta create(Connection connection, Respuesta respuesta)
    {
        String queryString = "INSERT INTO Respuesta(encuestaId, email, positiva, fechaRespuesta) VALUES (?, ?, ?, ?)";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString, Statement.RETURN_GENERATED_KEYS))
        {
            int i = 1;

            preparedStatement.setLong(i++, respuesta.getEncuestaId());
            preparedStatement.setString(i++, respuesta.getEmail());
            preparedStatement.setBoolean(i++, respuesta.isPositiva());
            preparedStatement.setTimestamp(i++, Timestamp.valueOf(respuesta.getFechaRespuesta()));

            preparedStatement.executeUpdate();

            ResultSet resultSet = preparedStatement.getGeneratedKeys();

            if (!resultSet.next()) throw new SQLException("JDBC driver did not return generated key.");

            long generatedId = resultSet.getLong(1);
            respuesta.setRespuestaId(generatedId);

            return respuesta;
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }
}