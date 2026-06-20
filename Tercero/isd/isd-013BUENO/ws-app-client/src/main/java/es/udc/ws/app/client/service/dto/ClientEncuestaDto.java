package es.udc.ws.app.client.service.dto;

import java.time.LocalDateTime;

public class ClientEncuestaDto
{
    private long encuestaId;
    private String pregunta;
    private LocalDateTime fechaCreacion;
    private LocalDateTime fechaFin;
    private boolean cancelada;
    private int respuestasPositivas;
    private int respuestasTotales;

    public ClientEncuestaDto() {}


    public ClientEncuestaDto(String pregunta, LocalDateTime fecha)
    {
        this.encuestaId = -1;
        this.pregunta = pregunta;
        this.fechaCreacion = LocalDateTime.now().withNano(0);
        this.fechaFin = fecha.withNano(0);
        this.cancelada = false;
        this.respuestasPositivas = 0;
        this.respuestasTotales = 0;
    }

    public ClientEncuestaDto(long encuestaId, String pregunta, LocalDateTime fechaCreacion, LocalDateTime fechaFin, boolean cancelada, int respuestasPositivas, int respuestasTotales) {
        this.encuestaId = encuestaId;
        this.pregunta = pregunta;
        this.fechaCreacion = fechaCreacion;
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

    public LocalDateTime getFechaCreacion() {
        return fechaCreacion;
    }

    public void setFechaCreacion(LocalDateTime fechaCreacion) {
        this.fechaCreacion = fechaCreacion;
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

    public int getRepuestasPositivas() {
        return respuestasPositivas;
    }

    public void setRepuestasPositivas(int respuestasPositivas) {
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
        return "ClientEncuestaDto{" +
                "encuestaId=" + encuestaId +
                ", pregunta='" + pregunta + '\'' +
                ", fechaCreacion=" + fechaCreacion +
                ", fechaFin=" + fechaFin +
                ", cancelada=" + cancelada +
                ", respuestasPositivas=" + respuestasPositivas +
                ", respuestasTotales=" + respuestasTotales +
                '}';
    }
}
