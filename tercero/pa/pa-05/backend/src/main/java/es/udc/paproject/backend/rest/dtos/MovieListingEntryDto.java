package es.udc.paproject.backend.rest.dtos;

import java.util.List;

public class MovieListingEntryDto {
    private MovieDto movie;
    private List<SessionDto> sessions;

    public MovieListingEntryDto(MovieDto movie, List<SessionDto> sessions) {
        this.movie = movie;
        this.sessions = sessions;
    }

    public MovieDto getMovie() { return movie; }
    public void setMovie(MovieDto movie) { this.movie = movie; }

    public List<SessionDto> getSessions() { return sessions; }
    public void setSessions(List<SessionDto> sessions) { this.sessions = sessions; }
}
