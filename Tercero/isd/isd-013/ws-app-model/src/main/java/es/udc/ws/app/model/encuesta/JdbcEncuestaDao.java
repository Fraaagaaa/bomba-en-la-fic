package es.udc.ws.app.model.encuesta;

import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class JdbcEncuestaDao extends AbstractSqlEncuestaDao
{
    @Override
    public Encuesta create(Connection connection, Encuesta encuesta)
    {
        final String sql = "INSERT INTO Encuesta(encuestaId, pregunta, fechaCreacion, fechaFin, cancelada, respuestasPositivas, respuestasNegativas) VALUES (?, ?, ?, ?, ?, ?, ?)";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS))
        {
            int i = 1;

            preparedStatement.setLong(i++, encuesta.getId());
            preparedStatement.setString(i++, encuesta.getPregunta());
            preparedStatement.setTimestamp(i++, Timestamp.valueOf(encuesta.getFechaCreacion()));
            preparedStatement.setTimestamp(i++, Timestamp.valueOf(encuesta.getFechaFin()));
            preparedStatement.setBoolean(i++, encuesta.isCancelada());
            preparedStatement.setInt(i++, encuesta.getRepuestasPositivas());
            preparedStatement.setInt(i++, encuesta.getRespuestasNegativas());

            preparedStatement.executeUpdate();
            try (ResultSet resultSet = preparedStatement.getGeneratedKeys())
            {
                if (resultSet.next())
                {
                    encuesta.setId(resultSet.getLong(1));
                    return encuesta;
                }
                throw new SQLException("Error: no se devolvió el ID generado.");
            }
        }
        catch (SQLException e)
        {
            throw new RuntimeException("Error al crear la encuesta: " + e.getMessage(), e);
        }
    }

    @Override
    public Encuesta find(Connection connection, long id) throws InstanceNotFoundException
    {
        String queryString = "SELECT encuestaId, pregunta, fechaCreacion, fechaFin, cancelada, respuestasPositivas, respuestasNegativas FROM Encuesta WHERE encuestaId = ?";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            int i = 1;
            preparedStatement.setLong(i++, id);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (!resultSet.next())
                throw new InstanceNotFoundException(id, Encuesta.class.getName());

            i = 1;
            long EncuestaId = resultSet.getLong(i++);
            String pregunta = resultSet.getString(i++);
            LocalDateTime creationDate = resultSet.getTimestamp(i++).toLocalDateTime();
            LocalDateTime endDate = resultSet.getTimestamp(i++).toLocalDateTime();
            boolean cancelada = resultSet.getBoolean(i++);
            int positivas = resultSet.getInt(i++);
            int negativas = resultSet.getInt(i++);

            return new Encuesta(EncuestaId, pregunta, creationDate, endDate, cancelada, positivas, negativas);

        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }
}