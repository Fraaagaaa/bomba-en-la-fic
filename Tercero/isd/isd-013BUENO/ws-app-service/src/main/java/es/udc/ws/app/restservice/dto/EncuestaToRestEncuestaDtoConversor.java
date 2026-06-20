package es.udc.ws.app.restservice.dto;

import es.udc.ws.app.model.encuesta.Encuesta;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class EncuestaToRestEncuestaDtoConversor {

    public static List<RestEncuestaDto> toRestEncuestaDtos(List<Encuesta> encuestas) {
        List<RestEncuestaDto> encuestaDtos = new ArrayList<>(encuestas.size());
        for (Encuesta encuesta : encuestas) {
            encuestaDtos.add(toRestEncuestaDto(encuesta));
        }
        return encuestaDtos;
    }

    public static RestEncuestaDto toRestEncuestaDto(Encuesta encuesta)
    {
        return new RestEncuestaDto(encuesta.getId(), encuesta.getPregunta(), encuesta.getFechaFin(), encuesta.isCancelada(), encuesta.getRepuestasPositivas(), encuesta.getRespuestasNegativas() + encuesta.getRepuestasPositivas());
    }

    public static Encuesta toEncuesta(RestEncuestaDto dto)
    {
        return new Encuesta(dto.getPregunta(), dto.getFechaFin());
    }
}
