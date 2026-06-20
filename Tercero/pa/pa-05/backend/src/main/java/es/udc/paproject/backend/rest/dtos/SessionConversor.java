package es.udc.paproject.backend.rest.dtos;

import es.udc.paproject.backend.model.entities.Session;

public class SessionConversor {

    private SessionConversor() {}

    public static SessionDto toSessionDto(Session session) {
        return new SessionDto(
                session.getId(),
                session.getMovie().getId(),
                session.getMovie().getTitle(),
                session.getMovie().getDuration(),
                session.getPrice(),
                session.getSessionStartTime(),
                session.getSaloon().getName(),
                session.getAsientosLibres()
        );
    }
}