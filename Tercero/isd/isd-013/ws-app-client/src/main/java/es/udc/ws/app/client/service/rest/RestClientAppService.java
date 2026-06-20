package es.udc.ws.app.client.service.rest;

import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.databind.ObjectMapper;
import es.udc.ws.app.client.service.ClientEncuestaService;
import es.udc.ws.app.client.service.dto.ClientEncuestaDto;
import es.udc.ws.app.client.service.dto.ClientRespuestaDto;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaCanceladaException;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaExpirationException;
import es.udc.ws.app.client.service.rest.json.JsonToClientEncuestaDtoConversor;
import es.udc.ws.app.client.service.rest.json.JsonToClientExceptionConversor;
import es.udc.ws.app.client.service.rest.json.JsonToClientRespuestaDtoConversor;
import es.udc.ws.util.configuration.ConfigurationParametersManager;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import es.udc.ws.util.json.ObjectMapperFactory;
import org.apache.hc.client5.http.fluent.Form;
import org.apache.hc.client5.http.fluent.Request;
import org.apache.hc.core5.http.ClassicHttpResponse;
import org.apache.hc.core5.http.HttpStatus;
import org.apache.hc.core5.http.ContentType;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URLEncoder;
import java.util.List;

public class RestClientAppService implements ClientEncuestaService
{
    private static final String ENDPOINT_ADDRESS_PARAMETER = "RestClientAppService.endpointAddress";

    private String endpointAddress;


    @Override
    public ClientEncuestaDto crearEncuesta(ClientEncuestaDto encuesta) throws InputValidationException
    {
        try
        {
            ClassicHttpResponse response = (ClassicHttpResponse) Request.post(getEndpointAddress() + "encuestas").
                    bodyStream(toInputStream(encuesta), ContentType.create("application/json")).
                    execute().returnResponse();

            validateStatusCode(HttpStatus.SC_CREATED, response);

            return JsonToClientEncuestaDtoConversor.toClientEncuestaDto(response.getEntity().getContent());

        }
        catch (InputValidationException e)
        {
            throw e;
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<ClientEncuestaDto> buscarEncuestaPorPalabraClave(String keyword)
    {
        try
        {
            ClassicHttpResponse response = (ClassicHttpResponse) Request.get(getEndpointAddress() + "encuestas?keyword="
                    + URLEncoder.encode(keyword, "UTF-8")).execute().returnResponse();

            validateStatusCode(HttpStatus.SC_OK, response);

            return JsonToClientEncuestaDtoConversor.toClientEncuestaDtos(response.getEntity().getContent());
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public ClientEncuestaDto buscarEncuestaPorId(long encuestaId) throws InstanceNotFoundException, ClientEncuestaExpirationException
    {
        try
        {
            ClassicHttpResponse response = (ClassicHttpResponse) Request.get(getEndpointAddress() + "encuestas/" + encuestaId).execute().returnResponse();

            validateStatusCode(HttpStatus.SC_OK, response);
            return JsonToClientEncuestaDtoConversor.toClientEncuestaDto(response.getEntity().getContent());
        }
        catch (InstanceNotFoundException | ClientEncuestaExpirationException e)
        {
            throw e;
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }
    @Override
    public ClientRespuestaDto responderEncuesta(long encuestaId, String email, boolean voto) throws InstanceNotFoundException, InputValidationException, ClientEncuestaExpirationException
    {
        try
        {
            ClassicHttpResponse response = (ClassicHttpResponse) Request.post(getEndpointAddress() + "respuestas").
                    bodyForm(
                            Form.form().
                                    add("encuestaId", Long.toString(encuestaId)).
                                    add("email", email).
                                    add("voto", Boolean.toString(voto)).build()).
                    execute().returnResponse();

            validateStatusCode(HttpStatus.SC_CREATED, response);

            return JsonToClientRespuestaDtoConversor.toClientRespuestaDto(response.getEntity().getContent());
        }
        catch (InstanceNotFoundException | InputValidationException | ClientEncuestaCanceladaException | ClientEncuestaExpirationException e)
        {
            throw e;
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }

    @Override
    public void cancelarEncuesta(long encuestaId)
            throws ClientEncuestaCanceladaException, InstanceNotFoundException {

        try {
            ClassicHttpResponse response = (ClassicHttpResponse) Request.post(
                            getEndpointAddress() + "encuestas/" + encuestaId + "/cancel")
                    .execute().returnResponse();

            validateStatusCode(HttpStatus.SC_NO_CONTENT, response);

        } catch (InstanceNotFoundException | ClientEncuestaCanceladaException e) {
            throw e;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public List<ClientRespuestaDto> buscarRespuestasEncuesta(long encuestaId, boolean soloPositivas) throws InstanceNotFoundException, InputValidationException
    {
        try
        {
            // http://localhost:9090/ws-app-service/respuestas?encuestaId=1&soloPositivas=true
            ClassicHttpResponse response;

            if(soloPositivas)
            {
                response = (ClassicHttpResponse) Request.get(getEndpointAddress() + "respuestas?encuestaId=" + encuestaId + "&soloPositivas=true").execute().returnResponse();
                validateStatusCode(HttpStatus.SC_OK, response);
                return JsonToClientRespuestaDtoConversor.toClientRespuestaDtos(response.getEntity().getContent());
            }
            response = (ClassicHttpResponse) Request.get(getEndpointAddress() + "respuestas?encuestaId=" + encuestaId + "&soloPositivas=false").execute().returnResponse();
            validateStatusCode(HttpStatus.SC_OK, response);
            return JsonToClientRespuestaDtoConversor.toClientRespuestaDtos(response.getEntity().getContent());

        }
        catch (InstanceNotFoundException | InputValidationException e)
        {
            throw e;
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }


    //Comunes

    private synchronized String getEndpointAddress() {
        if (endpointAddress == null) {
            endpointAddress = ConfigurationParametersManager
                    .getParameter(ENDPOINT_ADDRESS_PARAMETER);
        }
        return endpointAddress;
    }

    private InputStream toInputStream(ClientEncuestaDto encuesta) {
        try {

            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            ObjectMapper objectMapper = ObjectMapperFactory.instance();
            objectMapper.writer(new DefaultPrettyPrinter()).writeValue(outputStream,
                    JsonToClientEncuestaDtoConversor.toObjectNode(encuesta));

            return new ByteArrayInputStream(outputStream.toByteArray());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void validateStatusCode(int successCode, ClassicHttpResponse response)
            throws Exception {
        try {
            int statusCode = response.getCode();

            // Éxito
            if (statusCode == successCode) {
                return;
            }

            // Errores mapeados a nuestras excepciones de cliente
            switch (statusCode) {
                case HttpStatus.SC_NOT_FOUND -> throw JsonToClientExceptionConversor.fromNotFoundErrorCode(
                        response.getEntity().getContent());
                case HttpStatus.SC_BAD_REQUEST -> throw JsonToClientExceptionConversor.fromBadRequestErrorCode(
                        response.getEntity().getContent());
                case HttpStatus.SC_FORBIDDEN -> throw JsonToClientExceptionConversor.fromForbiddenErrorCode(
                        response.getEntity().getContent());
                case HttpStatus.SC_GONE -> throw JsonToClientExceptionConversor.fromGoneErrorCode(
                        response.getEntity().getContent());
                default -> throw new RuntimeException("HTTP error; status code = " + statusCode);
            }
        }catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
