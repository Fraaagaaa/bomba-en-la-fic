package es.udc.ws.app.restservice.json;

import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.ObjectNode;
import es.udc.ws.app.restservice.dto.RestRespuestaDto;

import java.util.List;

public class JsonToRestRespuestaDtoConversor {

    public static ObjectNode toObjectNode(RestRespuestaDto respuesta) {

        ObjectNode respuestaNode= JsonNodeFactory.instance.objectNode();

        if (respuesta.getRespuestaId() != null) {
            respuestaNode.put("respuestaId", respuesta.getRespuestaId());
        }
        respuestaNode.put("encuestaId", respuesta.getEncuestaId()).
                put("email", respuesta.getEmail()).
                put("voto", respuesta.isPositiva());

        return respuestaNode;
    }

    public static ArrayNode toArrayNode(List<RestRespuestaDto> respuestas)
    {

        ArrayNode encuestaNode = JsonNodeFactory.instance.arrayNode();
        for (int i = 0; i < respuestas.size(); i++)
        {
            RestRespuestaDto respuestaDto = respuestas.get(i);
            ObjectNode encuestaObject = toObjectNode(respuestaDto);
            encuestaNode.add(encuestaObject);
        }

        return encuestaNode;
    }
}
