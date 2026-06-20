package es.udc.ws.app.restservice.dto;

import es.udc.ws.app.model.respuesta.Respuesta;
import es.udc.ws.app.model.respuesta.Respuesta;

import java.util.ArrayList;
import java.util.List;

public class RespuestaToRestRespuestaDtoConversor
{

    public static RestRespuestaDto toRestRespuestaDto(Respuesta respuesta)
    {
        return new RestRespuestaDto(respuesta.getRespuestaId(), respuesta.getEncuestaId(), respuesta.getEmail(), respuesta.isPositiva());
    }

    public static List<RestRespuestaDto> toRestRespuestaDtos(List<Respuesta> respuestas)
    {
        List<RestRespuestaDto> respuestaDtos = new ArrayList<>(respuestas.size());

        for (Respuesta respuesta : respuestas)
            respuestaDtos.add(toRestRespuestaDto(respuesta));

        return respuestaDtos;
    }

    public static Respuesta toRespuesta(RestRespuestaDto dto)
    {
        return new Respuesta(dto.getEncuestaId(), dto.getEmail(), dto.isPositiva());
    }
}