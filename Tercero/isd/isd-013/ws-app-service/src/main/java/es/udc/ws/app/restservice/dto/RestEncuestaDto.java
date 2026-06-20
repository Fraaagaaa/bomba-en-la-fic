package es.udc.ws.app.restservice.dto;

import java.time.LocalDateTime;

public class RestEncuestaDto {

    private long encuestaId;
    private String pregunta;
    private LocalDateTime fechaFin;
    private boolean cancelada;
    private int respuestasPositivas;
    private int respuestasTotales;

    public RestEncuestaDto() {
    }

    public RestEncuestaDto(Long encuestaId, String pregunta, LocalDateTime fechaFin, boolean cancelada, int respuestasPositivas, int respuestasTotales)
    {
        this.encuestaId = encuestaId;
        this.pregunta = pregunta;
        this.fechaFin = fechaFin;
        this.cancelada = cancelada;
        this.respuestasPositivas = respuestasPositivas;
        this.respuestasTotales = respuestasTotales;
    }

    public long getId() {
        return encuestaId;
    }

    public void setId(long encuestaId) {
        this.encuestaId = encuestaId;
    }

    public String getPregunta() {
        return pregunta;
    }

    public void setPregunta(String pregunta) {
        this.pregunta = pregunta;
    }

    public LocalDateTime getFechaFin() {
        return fechaFin;
    }

    public void setFechaFin(LocalDateTime fechaFin) {
        this.fechaFin = fechaFin;
    }

    public boolean isCancelada() {
        return cancelada;
    }

    public void setCancelada(boolean cancelada) {
        this.cancelada = cancelada;
    }

    public int getRespuestasPositivas() {
        return respuestasPositivas;
    }

    public void setRespuestasPositivas(int respuestasPositivas) {
        this.respuestasPositivas = respuestasPositivas;
    }

    public int getRespuestasTotales() {
        return respuestasTotales;
    }

    public void setRespuestasTotales(int respuestasTotales) {
        this.respuestasTotales = respuestasTotales;
    }

    @Override
    public String toString() {
        return "RestEncuestaDto{" +
                "encuestaId=" + encuestaId +
                ", pregunta='" + pregunta + '\'' +
                ", fechaFin='" + fechaFin + '\'' +
                ", cancelada=" + cancelada +
                ", respuestasPositivas=" + respuestasPositivas +
                ", respuestasTotales=" + respuestasTotales +
                '}';
    }
}
