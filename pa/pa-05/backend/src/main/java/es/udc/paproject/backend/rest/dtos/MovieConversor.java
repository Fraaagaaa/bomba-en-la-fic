package es.udc.paproject.backend.rest.dtos;

import es.udc.paproject.backend.model.entities.Movie;
import es.udc.paproject.backend.model.entities.MovieListingEntry;

import java.util.List;
import java.util.stream.Collectors;

public class MovieConversor {

    private MovieConversor() {}

    public static MovieDto toMovieDto(Movie movie) {
        return new MovieDto(
            movie.getId(),
            movie.getTitle(),
            movie.getSummary(),
            movie.getDuration()
        );
    }

    public static MovieListingEntryDto toMovieListingEntryDto(MovieListingEntry entry) {

        MovieDto movieDto = toMovieDto(entry.getMovie());


        List<SessionDto> sessionDtos = entry.getSessions().stream()
                .map(SessionConversor::toSessionDto)
                .collect(Collectors.toList());

        return new MovieListingEntryDto(movieDto, sessionDtos);
    }
}
