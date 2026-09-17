package es.udc.paproject.backend.model.exceptions;

public class TicketsAlreadyRetrievedException extends RuntimeException {
    public TicketsAlreadyRetrievedException(String message) {
        super(message);
    }
}
