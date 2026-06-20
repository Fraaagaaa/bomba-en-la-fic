package es.udc.ws.app.restservice.json;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.JsonNodeType;
import com.fasterxml.jackson.databind.node.ObjectNode;
import es.udc.ws.app.model.encuesta.Encuesta;
import es.udc.ws.app.restservice.dto.RestEncuestaDto;
import es.udc.ws.util.json.ObjectMapperFactory;
import es.udc.ws.util.json.exceptions.ParsingException;

import java.io.InputStream;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class JsonToRestEncuestaDtoConversor
{
    public static ObjectNode toObjectNode(RestEncuestaDto encuesta)
    {
        ObjectNode encuestaObject = JsonNodeFactory.instance.objectNode();

        encuestaObject.put("encuestaId", encuesta.getId()).
                put("pregunta", encuesta.getPregunta()).
                put("fechaFin", encuesta.getFechaFin().toString()).
                put("respuestasTotales", encuesta.getRespuestasTotales()).
                put("respuestasPositivas", encuesta.getRespuestasPositivas()).
                put("cancelada", encuesta.isCancelada());

        return encuestaObject;
    }

    public static ArrayNode toArrayNode(List<RestEncuestaDto> encuestas)
    {

        ArrayNode encuestaNode = JsonNodeFactory.instance.arrayNode();
        for (int i = 0; i < encuestas.size(); i++)
        {
            RestEncuestaDto encuestaDto = encuestas.get(i);
            ObjectNode encuestaObject = toObjectNode(encuestaDto);
            encuestaNode.add(encuestaObject);
        }

        return encuestaNode;
    }

    public static RestEncuestaDto toRestEncuestaDto(InputStream jsonEncuesta) throws ParsingException
    {
        try
        {
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            JsonNode rootNode = objectMapper.readTree(jsonEncuesta);

            if (rootNode.getNodeType() != JsonNodeType.OBJECT)
                throw new ParsingException("Unrecognized JSON (object expected)");
            else
            {
                ObjectNode encuestaObject = (ObjectNode) rootNode;

                long encuestaId = encuestaObject.path("encuestaId").asLong(0);

                if (!encuestaObject.has("pregunta"))
                    throw new ParsingException("Falta el campo 'pregunta'");

                String pregunta = encuestaObject.get("pregunta").textValue().trim();

                if (!encuestaObject.has("fechaFin"))
                    throw new ParsingException("Falta el campo 'fechaFin'");

                String fecha = encuestaObject.get("fechaFin").textValue().trim();

                boolean cancelada = encuestaObject.path("cancelada").asBoolean(false);

                int respuestasPositivas = encuestaObject.path("respuestasPositivas").asInt(0);
                int respuestasTotales = encuestaObject.path("respuestasTotales").asInt(0);

                return new RestEncuestaDto(encuestaId, pregunta, LocalDateTime.parse(fecha), cancelada, respuestasPositivas, respuestasTotales);
            }
        }
        catch (ParsingException ex)
        {
            throw ex;
        }
        catch (Exception e)
        {
            throw new ParsingException(e);
        }
    }
}
