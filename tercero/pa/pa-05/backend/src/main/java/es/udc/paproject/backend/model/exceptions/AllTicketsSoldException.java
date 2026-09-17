package es.udc.paproject.backend.model.exceptions;

import es.udc.paproject.backend.model.entities.Session;

public class AllTicketsSoldException extends Exception
{
    private final Long sessionId;

    public AllTicketsSoldException(String message, Long sessionId)
    {
        super(message);
        this.sessionId = sessionId;
    }

    public Long getSessionId() {
        return sessionId;
    }
}
