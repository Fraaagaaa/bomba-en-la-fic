package es.udc.ws.app.restservice.servlets;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import es.udc.ws.app.model.encuestaservice.EncuestaServiceFactory;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaCanceladaException;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaFinalizadaException;
import es.udc.ws.app.model.respuesta.Respuesta;
import es.udc.ws.app.restservice.dto.RespuestaToRestRespuestaDtoConversor;
import es.udc.ws.app.restservice.dto.RestRespuestaDto;
import es.udc.ws.app.restservice.json.AppExceptionToJsonConversor;
import es.udc.ws.app.restservice.json.JsonToRestRespuestaDtoConversor;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.util.servlet.RestHttpServletTemplate;
import es.udc.ws.util.servlet.ServletUtils;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class RespuestaServlet extends RestHttpServletTemplate
{
    @Override
    protected void processPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, InputValidationException, InstanceNotFoundException
    {
        // FUNC-4 Responder encuesta
        // http://xxx/ws-app-service/respuestas
        // 201 CREATED | 404 NOT FOUND | 403 FORBIDDEN | 400 BAD REQUEST
        ServletUtils.checkEmptyPath(req);
        long encuestaId = ServletUtils.getMandatoryParameterAsLong(req, "encuestaId");
        String email = ServletUtils.getMandatoryParameter(req, "email");
        boolean voto = Boolean.parseBoolean(ServletUtils.getMandatoryParameter(req, "voto"));

        Respuesta respuesta = null;
        try
        {
            respuesta = EncuestaServiceFactory.getService().responder(encuestaId, email, voto);
        }
        catch (EncuestaFinalizadaException | EncuestaCanceladaException e)
        {
            throw new RuntimeException(e);
        }

        RestRespuestaDto respuestaDto = RespuestaToRestRespuestaDtoConversor.toRestRespuestaDto(respuesta);
        String respuestaURL = ServletUtils.normalizePath(req.getRequestURL().toString()) + "/" + respuesta.getRespuestaId();
        Map<String, String> headers = new HashMap<>(1);
        headers.put("Location", respuestaURL);
        ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_CREATED, JsonToRestRespuestaDtoConversor.toObjectNode(respuestaDto), headers);
    }

    @Override
    protected void processGet(HttpServletRequest req, HttpServletResponse resp) throws IOException, InputValidationException, InstanceNotFoundException
    {
        // FUNC-6 Obtener respuestas
        // http://xxx/ws-app-service/respuestas?encuestaId={id}?soloPositivas={soloPositivas}
        // 200 OK | 404 NOT FOUND
        boolean soloPositivas = false;
        String encuestaIdStr = req.getParameter("encuestaId");

        if(req.getParameter("soloPositivas") != null)
            soloPositivas = Boolean.parseBoolean(req.getParameter("soloPositivas"));

        if (encuestaIdStr == null || encuestaIdStr.isEmpty())
        {
            ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_BAD_REQUEST, null, null);
            return;
        }

        try
        {
            long encuestaId = Long.parseLong(encuestaIdStr);
            List<Respuesta> respuestas = EncuestaServiceFactory.getService().obtenerRespuestas(encuestaId, soloPositivas);
            List<RestRespuestaDto> respuestaDtos = RespuestaToRestRespuestaDtoConversor.toRestRespuestaDtos(respuestas);

            // 200 OK
            ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_OK, JsonToRestRespuestaDtoConversor.toArrayNode(respuestaDtos), null);
        }
        catch (InstanceNotFoundException e)
        {
            // 404 NOT FOUND
            ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_NOT_FOUND, null, null);
        }
    }
}