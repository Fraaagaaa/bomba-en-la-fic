package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.Movie;
import es.udc.paproject.backend.model.entities.MovieListingEntry;
import es.udc.paproject.backend.model.exceptions.IncorrectDateException;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;

import java.time.LocalDate;
import java.util.List;

public interface MovieService
{
    // 1: Visualizar cartelera
    List<MovieListingEntry> viewMovieListing(LocalDate date) throws IncorrectDateException;

    // 2: Visualizar información detallada de la película
    Movie viewMovieDetails(Long MovieId) throws InstanceNotFoundException;
}