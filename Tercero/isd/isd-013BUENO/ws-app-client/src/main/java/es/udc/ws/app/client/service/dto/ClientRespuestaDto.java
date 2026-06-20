package es.udc.ws.app.client.service.dto;

import java.time.LocalDateTime;

public class ClientRespuestaDto {
    private long encuestaId;
    private long respuestaId;
    private String email;
    private boolean positiva;
    private String encuestaUrl;

    public ClientRespuestaDto() {}

    public ClientRespuestaDto(long encuestaId, long respuestaId, String email, boolean positiva, LocalDateTime fechaRespuesta) {
        this.encuestaId = encuestaId;
        this.respuestaId = respuestaId;
        this.email = email;
        this.positiva = positiva;
        this.fechaRespuesta = fechaRespuesta;
    }

    public ClientRespuestaDto(long encuestaId, long respuestaId, String email, boolean positiva)
    {
        this.encuestaId = encuestaId;
        this.respuestaId = respuestaId;
        this.email = email;
        this.positiva = positiva;
    }

    public long getEncuestaId() {
        return encuestaId;
    }

    public void setEncuestaId(long encuestaId) {
        this.encuestaId = encuestaId;
    }

    public long getRespuestaId() {
        return respuestaId;
    }

    public void setRespuestaId(long respuestaId) {
        this.respuestaId = respuestaId;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean isPositiva() {
        return positiva;
    }

    public void setPositiva(boolean positiva) {
        this.positiva = positiva;
    }

    public LocalDateTime getFechaRespuesta() {
        return fechaRespuesta;
    }

    public void setFechaRespuesta(LocalDateTime fechaRespuesta) {
        this.fechaRespuesta = fechaRespuesta;
    }

    private LocalDateTime fechaRespuesta;

    @Override
    public String toString() {
        return "ClientRespuestaDto{" +
                "encuestaId=" + encuestaId +
                ", respuestaId=" + respuestaId +
                ", email='" + email + '\'' +
                ", positiva=" + positiva +
                ", fechaRespuesta=" + fechaRespuesta +
                '}';
    }
}
