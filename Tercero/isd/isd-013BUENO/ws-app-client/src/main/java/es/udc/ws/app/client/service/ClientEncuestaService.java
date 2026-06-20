package es.udc.ws.app.client.service;

import es.udc.ws.app.client.service.dto.ClientEncuestaDto;
import es.udc.ws.app.client.service.dto.ClientRespuestaDto;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaCanceladaException;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaExpirationException;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;
import java.util.List;

public interface ClientEncuestaService
{
    /* 1 */ public ClientEncuestaDto crearEncuesta(ClientEncuestaDto encuesta) throws InputValidationException;

    /* 2 */ public List<ClientEncuestaDto> buscarEncuestaPorPalabraClave(String keyword);

    /* 3 */ public ClientEncuestaDto buscarEncuestaPorId(long encuestaId) throws InstanceNotFoundException, ClientEncuestaExpirationException;

    /* 4 */ public ClientRespuestaDto responderEncuesta(long encuestaId, String email, boolean voto) throws InstanceNotFoundException, InputValidationException;

    /* 5 */ public void cancelarEncuesta(long encuestaId) throws ClientEncuestaCanceladaException, InstanceNotFoundException;

    /* 6 */  public List<ClientRespuestaDto> buscarRespuestasEncuesta(long encuestaId, boolean soloPositivas) throws InstanceNotFoundException, InputValidationException;
}