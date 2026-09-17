package es.udc.paproject.backend.model.exceptions;

public class SessionAlreadyStartedException extends RuntimeException
{

    private final Long sessionId;

    public SessionAlreadyStartedException(String message, Long sessionId)
    {
        super(message);
        this.sessionId = sessionId;
    }

    public Long getSessionId() {
        return sessionId;
    }
}
