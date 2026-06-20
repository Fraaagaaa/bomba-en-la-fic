package es.udc.ws.app.model.encuestaservice.exceptions;

import java.time.LocalDateTime;

public class EncuestaFinalizadaException extends Exception {
    private final long encuestaId;
    private final LocalDateTime fechaFin;

    public EncuestaFinalizadaException(long encuestaId, LocalDateTime fechaFin) {
        super("La encuesta " + encuestaId + " ya ha finalizado.");
        this.encuestaId = encuestaId;
        this.fechaFin = fechaFin;
    }

    public long getEncuestaId() {
        return encuestaId;
    }

    public LocalDateTime getFechaFin() {
        return fechaFin;
    }
}
