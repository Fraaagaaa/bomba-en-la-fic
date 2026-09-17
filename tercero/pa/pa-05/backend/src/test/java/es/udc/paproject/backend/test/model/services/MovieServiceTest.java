package es.udc.paproject.backend.test.model.services;

import es.udc.paproject.backend.model.entities.Movie;
import es.udc.paproject.backend.model.entities.MovieListingEntry;
import es.udc.paproject.backend.model.exceptions.IncorrectDateException;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import es.udc.paproject.backend.model.services.MovieService;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDate;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
@ActiveProfiles("test")
@Transactional

public class MovieServiceTest
{
    @Autowired
    private MovieService movieService;

    @Autowired
    private MovieDao movieDao;

    @Test
    void testViewMovieDetailsOk() throws InstanceNotFoundException
    {
        Movie movie = new Movie("Torrente, presidente", "Un resumen cualquiera", 120);
        movieDao.save(movie);

        movieDao.save(movie);

        Movie result = movieService.viewMovieDetails(movie.getId());

        assertEquals(movie.getId(), result.getId());
        assertEquals("Torrente, presidente", result.getTitle());
    }

    @Test
    void testViewMovieDetailsNotFound()
    {
        Long nonExistingId = -1L;

        assertThrows(InstanceNotFoundException.class, () ->
                movieService.viewMovieDetails(nonExistingId)
        );
    }

    @Test
    void testViewMovieListingIncorrectDate()
    {
        LocalDate pastDate = LocalDate.now().minusDays(1);

        assertThrows(IncorrectDateException.class, () ->
                movieService.viewMovieListing(pastDate)
        );
    }

    @Test
    void testViewMovieListingOk() throws IncorrectDateException
    {
        Movie movie = new Movie("Dune", "Resumen de Dune", 150);
        movieDao.save(movie);

        movieDao.save(movie);

        LocalDate date = LocalDate.now();

        List<MovieListingEntry> listing = movieService.viewMovieListing(date);

        assertNotNull(listing);
    }
}