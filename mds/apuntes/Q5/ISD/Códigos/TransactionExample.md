Mismo ejemplo que `es.udc.ws.jdbctutorial.InsertExample`, pero ahora la inserción de películas se realiza en una única transacción.
``` Java
public final class TransactionExample
{
	public static void main (String[] args)
	{
		try (Connection connection = ConnectionManager.getCOnnection())
		{
			try
			{
				// Prepare connection.
				connection.setAutoCommit(false);
				<< Insertar Películas.>>
				
				// Commit.
				connection.commit();
				
				System.out.println("Movies inserted");
			}
			catch (Exception e)
			{
				connection.rollback();
				throw e;
			}
		}
		catch (Exception e)
		{
			e.printStackTrace(System.err);
		}
	}
}