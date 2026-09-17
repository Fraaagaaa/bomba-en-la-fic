## Ejemplo de actualización
``` Java
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public final class InsertExample {
	public static void main (String[] args)
		
		try (Connection connection = ConnectionManager.getConnection())
		{
			
			// Create data for some movies
			String[] movieIdentifiers = new String[]
			{
				"movie-1", "movie-2", "movie-3"
			};
			
			String[] titles = new String[]
			{
				"movie-1 title", "movie-2 title", "movie-3 title"
			};
			// Create "preparedStatement"
			String queryString = "INSERT INTO TutMovie " + "(movieId, title, runtime) VALUES (?, ?, ?)";
			PreparedStatement preparedStatement = connection.prepareStatement(queryString);
			
			for (int i = 0; i < movieIdentifiers.length; i++)
			{
				preparedStatement.setString(1, movieIdentifiers[i])
				preparedStatement.setString(2, titles[i])
				preparedStatement.setShort(3, runtimes[i])
				
				int insertedRows = preparedStatement.executeUpdate();
				
				if(insertedRows != 1)
					throw new SQLException(movieIdentifiers[i] + ": problems when inserting!!!!!");
			}
		}
		catch(Exception e)
		{
			e.printStackTrace(System.err);
		}
	}
```
## Ejemplo de búsqueda
``` Java
package es.udc.ws.jdbctutorial;

import java.sql.Connection
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public final class SelectExample
{
	public static void main (String[] args)
	{
		try (Connection connection = ConnectionManager.getConnection())
		{
			// Create "preparedStatement"
			String queryString = "SELECT movieId, title, runtime FROM TutMovie";
			PreparedStatement preparedStatement = connection.preparedStatement(queryString);
			
			// Execute query
			ResultSet resultSet = preparedStatement.executeQuery();
			
			// Iterate over matched rows
			while(resultSet.next())
			{
				String movieIdentifier = resultSet.getString(1);
				String title = resultSet.getString(2);
				String runtime = resultSet.getShort(3);
				System.out.println("movieIdentifer = " + movieIdentifer + " | title = " + title + " | runtime = " + runtime);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace(System.err)
		}
	}
}
```
## ConnectionManager
``` Java
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectionManager
{
	private final static String DRIVER_URL = "jdbc:mysql://localhost/ws?...";
	private final static String USER = "ws";
	private final static String PASSWORKD = "ws";
	
	private ConnectionManager()
	{
		public final static Connection getConnection()
			throws SQLException
			{
				return DriverManager.getConnection(DRIVER_URL, USER, PASSWORD);
			}
	}
}
```
