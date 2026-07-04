package es.udc.paproject.backend.rest.controllers;

import java.time.LocalDate;
import java.util.List;
import java.util.stream.Collectors;

import es.udc.paproject.backend.model.entities.Session;
import es.udc.paproject.backend.model.services.SessionService;
import es.udc.paproject.backend.rest.dtos.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.web.bind.annotation.*;

import es.udc.paproject.backend.model.entities.Movie;
import es.udc.paproject.backend.model.entities.MovieListingEntry;
import es.udc.paproject.backend.model.exceptions.IncorrectDateException;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import es.udc.paproject.backend.model.services.MovieService;

@RestController
@RequestMapping("/catalog")
public class MovieController {

    @Autowired
    private MovieService movieService;

    @Autowired
    private SessionService sessionService;

    @GetMapping("/movies")
    public List<MovieListingEntryDto> viewMovieListing(
            @RequestParam @DateTimeFormat(iso = DateTimeFormat.ISO.DATE) LocalDate date)
            throws IncorrectDateException {

        List<MovieListingEntry> entries = movieService.viewMovieListing(date);

        return entries.stream()
                .map(MovieConversor::toMovieListingEntryDto)
                .collect(Collectors.toList());
    }

    @GetMapping("/movies/{id}")
    public MovieDto viewMovieDetails(@PathVariable Long id)
            throws InstanceNotFoundException {

        Movie movie = movieService.viewMovieDetails(id);

        return MovieConversor.toMovieDto(movie);
    }

    @GetMapping("/sessions/{id}")
    public SessionDto viewSessionDetails(@PathVariable Long id)
            throws InstanceNotFoundException {

        Session session = sessionService.viewSessionDetails(id);

        return SessionConversor.toSessionDto(session);
    }
}