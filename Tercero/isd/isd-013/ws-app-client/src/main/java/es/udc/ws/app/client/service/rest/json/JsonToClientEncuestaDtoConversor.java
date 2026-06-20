package es.udc.ws.app.client.service.rest.json;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.JsonNodeType;
import com.fasterxml.jackson.databind.node.ObjectNode;
import es.udc.ws.app.client.service.dto.ClientEncuestaDto;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.util.json.ObjectMapperFactory;
import es.udc.ws.util.json.exceptions.ParsingException;

import java.io.IOException;
import java.io.InputStream;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class JsonToClientEncuestaDtoConversor
{
    public static ObjectNode toObjectNode(ClientEncuestaDto encuesta) throws IOException
    {
        ObjectNode encuestaObject = JsonNodeFactory.instance.objectNode();

        if (encuesta.getId() != 0)
            encuestaObject.put("encuestaId", encuesta.getId());

        encuestaObject.put("pregunta", encuesta.getPregunta());
        if (encuesta.getFechaFin() != null)
            encuestaObject.put("fechaFin", encuesta.getFechaFin().toString());

        encuestaObject.put("respuestasTotales", encuesta.getRespuestasTotales() + encuesta.getRespuestasTotales()).
                put("respuestasPositivas", encuesta.getRepuestasPositivas()).
                put("cancelada", encuesta.isCancelada());

        return encuestaObject;
    }

    public static ClientEncuestaDto toClientEncuestaDto(InputStream jsonEncuesta) throws ParsingException
    {
        try
        {
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            JsonNode rootNode = objectMapper.readTree(jsonEncuesta);
            if (rootNode.getNodeType() != JsonNodeType.OBJECT)
            {
                throw new ParsingException("Unrecognized JSON (object expected)");
            }
            else
            {
                return toClientEncuestaDto(rootNode);
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

    public static List<ClientEncuestaDto> toClientEncuestaDtos(InputStream jsonEncuestas) throws ParsingException
    {
        try
        {
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            JsonNode rootNode = objectMapper.readTree(jsonEncuestas);
            if (rootNode.getNodeType() != JsonNodeType.ARRAY)
            {
                throw new ParsingException("Unrecognized JSON (array expected)");
            }
            else
            {
                ArrayNode encuestasArray = (ArrayNode) rootNode;
                List<ClientEncuestaDto> encuestaDtos = new ArrayList<>(encuestasArray.size());
                for (JsonNode encuestaNode : encuestasArray)
                    encuestaDtos.add(toClientEncuestaDto(encuestaNode));
                return encuestaDtos;
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

    private static ClientEncuestaDto toClientEncuestaDto(JsonNode encuestaNode) throws ParsingException
    {
        if (encuestaNode.getNodeType() != JsonNodeType.OBJECT)
        {
            throw new ParsingException("Unrecognized JSON (object expected)");
        }
        else
        {
            ObjectNode encuestaObject = (ObjectNode) encuestaNode;

            JsonNode encuestaIdNode = encuestaObject.get("encuestaId");
            long encuestaId = (encuestaIdNode != null) ? encuestaIdNode.longValue() : -1;

            String pregunta = encuestaObject.get("pregunta").textValue().trim();
            LocalDateTime fechaFin = LocalDateTime.parse(encuestaObject.get("fechaFin").textValue());
            LocalDateTime fechaComienzo = LocalDateTime.now().withNano(0);
            boolean cancelada = encuestaObject.get("cancelada").booleanValue();
            int respuestasPositivas = encuestaObject.get("respuestasPositivas").intValue();
            int respuestasTotales = encuestaObject.get("respuestasTotales").intValue();
            return new ClientEncuestaDto(encuestaId, pregunta, fechaComienzo, fechaFin, cancelada, respuestasPositivas, respuestasTotales);
        }
    }
}
