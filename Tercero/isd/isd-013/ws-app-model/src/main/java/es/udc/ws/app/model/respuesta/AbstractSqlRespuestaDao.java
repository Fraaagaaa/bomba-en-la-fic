package es.udc.ws.app.model.respuesta;

import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


public abstract class AbstractSqlRespuestaDao implements SqlRespuestaDao
{
    public AbstractSqlRespuestaDao() {}

    @Override
    public Respuesta find(Connection connection, long respuestaId) throws InstanceNotFoundException
    {
        String queryString = "SELECT respuestaId, encuestaId, email, positiva, fechaRespuesta FROM Respuesta WHERE respuestaId = ?";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            int i = 1;
            preparedStatement.setLong(i++, respuestaId);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (!resultSet.next()) throw new InstanceNotFoundException(respuestaId, Respuesta.class.getName());

            i = 1;
            long id = resultSet.getLong(i++);
            long encuestaId = resultSet.getLong(i++);
            String email = resultSet.getString(i++);
            boolean positiva = resultSet.getBoolean(i++);
            LocalDateTime fechaRespuesta = resultSet.getTimestamp(i++).toLocalDateTime();


            return new Respuesta(id, encuestaId, email, positiva, fechaRespuesta);
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<Respuesta> findByEncuesta(Connection connection, long encuestaId, boolean soloPositivas) throws InstanceNotFoundException
    {
        String queryString = "SELECT respuestaId, encuestaId, email, positiva, fechaRespuesta FROM Respuesta WHERE encuestaId= ?";

        queryString += " ORDER BY email";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            preparedStatement.setLong(1, encuestaId);
            ResultSet resultSet = preparedStatement.executeQuery();

            List<Respuesta> respuestas = new ArrayList<Respuesta>();

            while (resultSet.next())
            {
                int i = 1;
                long id = resultSet.getLong(i++);
                long encuesta_Id= resultSet.getLong(i++);
                String email = resultSet.getString(i++);
                boolean positiva = resultSet.getBoolean(i++);
                LocalDateTime fechaRespuesta = resultSet.getTimestamp(i++).toLocalDateTime();

                if(soloPositivas && !positiva) continue;

                respuestas.add(new Respuesta(id, encuesta_Id, email, positiva, fechaRespuesta));
            }
            // puede devolver listas vacías no es un problema
            return respuestas;
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void update(Connection connection, Respuesta respuesta) throws InstanceNotFoundException
    {
        String queryString = "UPDATE Respuesta SET email = ?, positiva = ?, fechaRespuesta = ? WHERE  respuestaId = ?";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            int i = 1;
            LocalDateTime now = LocalDateTime.now().withNano(0);
            preparedStatement.setString(i++, respuesta.getEmail());
            preparedStatement.setBoolean(i++, respuesta.isPositiva());
            preparedStatement.setTimestamp(i++, Timestamp.valueOf(now));
            preparedStatement.setLong(i++, respuesta.getRespuestaId());

            int updatedRows = preparedStatement.executeUpdate();

            if (updatedRows == 0)
                throw new InstanceNotFoundException(respuesta.getEncuestaId(), Respuesta.class.getName());
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void remove(Connection connection, long respuestaId) throws InstanceNotFoundException
    {
        String queryString = "DELETE FROM Respuesta WHERE respuestaId = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            int i = 1;
            preparedStatement.setLong(i++, respuestaId);

            int removedRows = preparedStatement.executeUpdate();

            if (removedRows == 0)
                throw new InstanceNotFoundException(respuestaId, Respuesta.class.getName());

        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }

public Respuesta findByEmail(Connection connection, long encuestaId, String email)
{
    String queryString = "SELECT respuestaId, email, positiva, fechaRespuesta FROM Respuesta WHERE encuestaId = ? AND email = ?";

    try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
    {
        preparedStatement.setLong(1, encuestaId);
        preparedStatement.setString(2, email);
        
        ResultSet resultSet = preparedStatement.executeQuery();
        
        if (!resultSet.next())
        {
           return null;
        }

        long respuestaId = resultSet.getLong("respuestaId");
        String email2 = resultSet.getString("email");
        boolean positiva = resultSet.getBoolean("positiva");
        LocalDateTime fechaRespuesta = resultSet.getTimestamp("fechaRespuesta").toLocalDateTime();

        return new Respuesta(respuestaId, encuestaId, email2, positiva, fechaRespuesta);
    }
    catch (SQLException e)
    {
        throw new RuntimeException(e);
    }
}

    public List<Respuesta> findPositivasByEncuesta(Connection connection, long id) throws InstanceNotFoundException
    {
        String queryString = "SELECT respuestaId, encuestaId, email, positiva, fechaRespuesta FROM Respuesta WHERE encuestaId = ? AND positiva = TRUE";

        try (PreparedStatement preparedStatement = connection.prepareStatement(queryString))
        {
            preparedStatement.setLong(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();

            List<Respuesta> respuestas = new ArrayList<>();

            while (resultSet.next())
            {
                int i = 1;
                long respuestaId = resultSet.getLong(i++);
                long encuestaId = resultSet.getLong(i++);
                String email = resultSet.getString(i++);
                boolean positiva = resultSet.getBoolean(i++);
                LocalDateTime fechaRespuesta = resultSet.getTimestamp(i++).toLocalDateTime();

                respuestas.add(new Respuesta(respuestaId, encuestaId, email, positiva, fechaRespuesta));
            }

            return respuestas;
        }
        catch (SQLException e)
        {
            throw new RuntimeException(e);
        }
    }
}
