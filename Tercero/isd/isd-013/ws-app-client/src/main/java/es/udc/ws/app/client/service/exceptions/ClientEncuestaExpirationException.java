package es.udc.ws.app.client.service.exceptions;

import java.time.LocalDateTime;

public class ClientEncuestaExpirationException extends Exception{
    private long respuestaId;
    private LocalDateTime expirationDate;

    public ClientEncuestaExpirationException(long respuestaId, LocalDateTime expirationDate) {

        super("Respuesta con id=\"" + respuestaId + "\" ha expirado (fecha de expiración = \"" + expirationDate + "\"");
        this.respuestaId = respuestaId;
        this.expirationDate = expirationDate;
    }

    public long getRespuestaId() {
        return respuestaId;
    }
    public void setRespuestaId(long respuestaId) { this.respuestaId = respuestaId; }

    public LocalDateTime getExpirationDate() {return expirationDate;}

    public void setExpirationDate(LocalDateTime expirationDate) {this.expirationDate = expirationDate;}
}
