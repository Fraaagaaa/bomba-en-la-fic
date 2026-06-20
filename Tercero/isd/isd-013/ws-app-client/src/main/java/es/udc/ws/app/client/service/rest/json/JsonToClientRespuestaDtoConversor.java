package es.udc.ws.app.client.service.rest.json;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ArrayNode;
import com.fasterxml.jackson.databind.node.JsonNodeType;
import com.fasterxml.jackson.databind.node.ObjectNode;
import es.udc.ws.app.client.service.dto.ClientRespuestaDto;
import es.udc.ws.util.json.ObjectMapperFactory;
import es.udc.ws.util.json.exceptions.ParsingException;

import java.io.InputStream;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class JsonToClientRespuestaDtoConversor
{
    public static ClientRespuestaDto toClientRespuestaDto(InputStream jsonRespuesta) throws ParsingException
    {
        try
        {
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            JsonNode rootNode = objectMapper.readTree(jsonRespuesta);
            if (rootNode.getNodeType() != JsonNodeType.OBJECT)
            {
                throw new ParsingException("Unrecognized JSON (object expected)");
            }
            else
            {
                ObjectNode encuestaObject = (ObjectNode) rootNode;

                JsonNode respuestaIdNode = encuestaObject.get("respuestaId");


                long respuestaId = (respuestaIdNode != null) ? respuestaIdNode.longValue() : -1;
                long encuestaId = encuestaObject.get("encuestaId").longValue();
                String email = encuestaObject.get("email").textValue().trim();
                boolean voto = encuestaObject.get("voto").booleanValue();

                return new ClientRespuestaDto(encuestaId, respuestaId, email, voto);
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
    public static List<ClientRespuestaDto> toClientRespuestaDtos(InputStream jsonRespuestas)
            throws ParsingException {

        try {
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            JsonNode rootNode = objectMapper.readTree(jsonRespuestas);

            if (rootNode.getNodeType() != JsonNodeType.ARRAY) {
                throw new ParsingException("Unrecognized JSON (array expected)");
            }

            ArrayNode array = (ArrayNode) rootNode;
            List<ClientRespuestaDto> respuestas = new ArrayList<>(array.size());

            for (JsonNode node : array) {
                if (node.getNodeType() != JsonNodeType.OBJECT) {
                    throw new ParsingException("Unrecognized JSON (object expected inside array)");
                }

                ObjectNode respuestaObject = (ObjectNode) node;

                long respuestaId = respuestaObject.get("respuestaId").longValue();
                long encuestaId = respuestaObject.get("encuestaId").longValue();
                String email = respuestaObject.get("email").textValue().trim();
                boolean voto = respuestaObject.get("voto").booleanValue();

                respuestas.add(
                        new ClientRespuestaDto(encuestaId, respuestaId, email, voto)
                );
            }

            return respuestas;

        } catch (ParsingException ex) {
            throw ex;
        } catch (Exception e) {
            throw new ParsingException(e);
        }
    }
}
