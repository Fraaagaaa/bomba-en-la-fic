package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.Session;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import es.udc.paproject.backend.model.exceptions.SessionAlreadyStartedException;

public interface SessionService
{
    // 3: Visualizar información detallada de una sesión
    Session viewSessionDetails(Long SessionId) throws InstanceNotFoundException, SessionAlreadyStartedException;
}
