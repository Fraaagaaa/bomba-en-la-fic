package es.udc.ws.app.restservice.servlets;

import es.udc.ws.app.model.encuesta.Encuesta;
import es.udc.ws.app.model.encuestaservice.EncuestaServiceFactory;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaCanceladaException;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaFinalizadaException;
import es.udc.ws.app.restservice.dto.EncuestaToRestEncuestaDtoConversor;
import es.udc.ws.app.restservice.dto.RestEncuestaDto;
import es.udc.ws.app.restservice.json.AppExceptionToJsonConversor;
import es.udc.ws.app.restservice.json.JsonToRestEncuestaDtoConversor;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.util.servlet.RestHttpServletTemplate;
import es.udc.ws.util.servlet.ServletUtils;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class EncuestaServlet extends RestHttpServletTemplate
{
    @Override
    protected void processPost(HttpServletRequest req, HttpServletResponse resp) throws IOException, InputValidationException
    {
        // FUNC-1 Añadir encuesta
        // http://xxx/ws-app-service/encuestas
        // 201 CREATED 400 BAD REQUEST

        // FUNC-5 Cancelar encuesta
        // http://xxx/ws-app-service/encuestas/{id}/cancel
        // 204 NO CONTENT 404 NOT FOUND 403 FORBIDDEN

        String pathInfo = req.getPathInfo();

        if (pathInfo != null && pathInfo.length() > 1)
        {
            String[] segments = pathInfo.substring(1).split("/");

            if (segments.length == 2 && "cancel".equalsIgnoreCase(segments[1]))
            {   // FUNC 5 | Cancelar encuesta
                try
                {
                    long encuestaId = Long.parseLong(segments[0]);
                    EncuestaServiceFactory.getService().cancelarEncuesta(encuestaId);
                    // 204 NO CONTENT
                    ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_NO_CONTENT, null, null);

                }
                catch (InstanceNotFoundException e)
                {
                    // 404 NOT FOUND
                    ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_NOT_FOUND, null, null);
                }
                catch (EncuestaFinalizadaException e)
                {
                    // 403 FORBIDDEN por finalizada
                    ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_FORBIDDEN, AppExceptionToJsonConversor.toEncuestaFinalizadaException(e), null);
                }
                catch (EncuestaCanceladaException e)
                {
                    // 403 FORBIDDEN por cancelada
                    ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_FORBIDDEN, AppExceptionToJsonConversor.toEncuestaCanceladaException(e), null);
                }
            }
            else
            {
                ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_NOT_FOUND, null, null);
            }

        }
        else
        {
            // FUNC-1 Añadir encuesta
            RestEncuestaDto encuestaDto = JsonToRestEncuestaDtoConversor.toRestEncuestaDto(req.getInputStream());
            Encuesta encuesta = EncuestaToRestEncuestaDtoConversor.toEncuesta(encuestaDto);

            encuesta = EncuestaServiceFactory.getService().crearEncuesta(encuesta);

            encuestaDto = EncuestaToRestEncuestaDtoConversor.toRestEncuestaDto(encuesta);

            String encuestaURL = ServletUtils.normalizePath(req.getRequestURL().toString()) + "/" + encuesta.getId();
            Map<String, String> headers = new HashMap<>(1);
            headers.put("Location", encuestaURL);

            ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_CREATED, JsonToRestEncuestaDtoConversor.toObjectNode(encuestaDto), headers);
        }
    }

    @Override
    protected void processGet(HttpServletRequest req, HttpServletResponse resp) throws IOException, InputValidationException, InstanceNotFoundException
    {
        // FUNC-2 Buscar encuesta por palabra clave
        // http://xxx/ws-app-service/encuestas?keyword=
        // 200 OK

        // FUNC-3 Buscar encuesta por Id
        // http://xxx/ws-app-service/encuestas/%7Bid%7D
        // 200 OK 404 NotFound

        String pathInfo = req.getPathInfo();

        if (pathInfo != null && pathInfo.length() > 1)
        {
            // FUNC 3 | Obtener por ID
            String idStr = pathInfo.substring(1);
            try
            {
                long encuestaId = Long.parseLong(idStr);

                Encuesta encuesta = EncuestaServiceFactory.getService().obtenerInformacion(encuestaId);

                RestEncuestaDto encuestaDto = EncuestaToRestEncuestaDtoConversor.toRestEncuestaDto(encuesta);
                // 200 OK
                ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_OK, JsonToRestEncuestaDtoConversor.toObjectNode(encuestaDto), null);

            }
            catch (InstanceNotFoundException e)
            {
                // 404 Not Found
                ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_NOT_FOUND, null, null);
            }

        }
        else
        {
            // FUNC 2 | Obtener por keyword
            String keyWord = req.getParameter("keyword");
            List<Encuesta> encuestas = EncuestaServiceFactory.getService().obtenerEncuestas(keyWord, false);

            List<RestEncuestaDto> encuestaDtos = EncuestaToRestEncuestaDtoConversor.toRestEncuestaDtos(encuestas);
            // 200 OK
            ServletUtils.writeServiceResponse(resp, HttpServletResponse.SC_OK, JsonToRestEncuestaDtoConversor.toArrayNode(encuestaDtos), null);
        }
    }

}
