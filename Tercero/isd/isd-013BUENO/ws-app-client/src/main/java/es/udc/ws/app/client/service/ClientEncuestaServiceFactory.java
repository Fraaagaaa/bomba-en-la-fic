package es.udc.ws.app.client.service;

import es.udc.ws.util.configuration.ConfigurationParametersManager;

import java.lang.reflect.InvocationTargetException;

public class ClientEncuestaServiceFactory
{
    private final static String CLASS_NAME_PARAMETER = "ClientAppServiceFactory.className";

    private static Class<ClientEncuestaService> serviceClass = null;

    private ClientEncuestaServiceFactory() {}

    @SuppressWarnings("unchecked")
    private synchronized static Class<ClientEncuestaService> getServiceClass()
    {
        if (serviceClass == null)
        {
            try
            {
                String serviceClassName = ConfigurationParametersManager.getParameter(CLASS_NAME_PARAMETER);
                serviceClass = (Class<ClientEncuestaService>) Class.forName(serviceClassName);
            }
            catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        }
        return serviceClass;
    }

    public static ClientEncuestaService getService()
    {
        try
        {
            return (ClientEncuestaService) getServiceClass().getDeclaredConstructor().newInstance();
        }
        catch (InstantiationException | IllegalAccessException | NoSuchMethodException | InvocationTargetException e)
        {
            throw new RuntimeException(e);
        }
    }
}
