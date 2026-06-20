package es.udc.paproject.backend.model.exceptions;

public class IncorrectDateException extends RuntimeException {
    public IncorrectDateException(String message) {
        super(message);
    }
}
