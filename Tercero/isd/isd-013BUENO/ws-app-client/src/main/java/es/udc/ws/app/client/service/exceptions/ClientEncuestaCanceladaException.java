package es.udc.ws.app.client.service.exceptions;

import java.time.LocalDateTime;

public class ClientEncuestaCanceladaException extends RuntimeException
{
    private final long encuestaId;

    public long getEncuestaId() {
        return encuestaId;
    }

    public ClientEncuestaCanceladaException(long encuestaId)
    {
        super("Encuesta con id=\"" + encuestaId + "\" ha sido cancelada");
        this.encuestaId = encuestaId;
    }
}
