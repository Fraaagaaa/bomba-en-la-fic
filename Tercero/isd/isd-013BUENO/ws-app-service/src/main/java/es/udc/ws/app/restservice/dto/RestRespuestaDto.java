package es.udc.ws.app.restservice.dto;

public class RestRespuestaDto {

    private long respuestaId;
    private long encuestaId;
    private String email;
    private boolean positiva;
    // No exponemos fechaRespuesta en la capa Servicios

    public RestRespuestaDto() {
    }

    public RestRespuestaDto(long respuestaId, long encuestaId, String email, boolean positiva) {
        this.respuestaId = respuestaId;
        this.encuestaId = encuestaId;
        this.email = email;
        this.positiva = positiva;
    }

    public Long getRespuestaId() { return respuestaId; }

    public void setRespuestaId(Long respuestaId) { this.respuestaId = respuestaId; }

    public Long getEncuestaId() { return encuestaId; }

    public void setEncuestaId(Long encuestaId) { this.encuestaId = encuestaId;}

    public String getEmail() { return email; }

    public void setEmail(String email) { this.email = email; }

    public boolean isPositiva() { return positiva; }

    public void setPositiva(boolean positiva) { this.positiva = positiva; }
}
