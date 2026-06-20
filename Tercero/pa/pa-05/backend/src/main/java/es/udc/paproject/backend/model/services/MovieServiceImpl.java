package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.*;
import es.udc.paproject.backend.model.exceptions.IncorrectDateException;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;

@Service
@Transactional(readOnly = true)
public class MovieServiceImpl implements MovieService
{
    @Autowired
    private MovieDao movieDao;

    @Autowired
    private SessionDao sessionDao;

    @Override
    public List<MovieListingEntry> viewMovieListing(LocalDate date) throws IncorrectDateException {

        if (date.isBefore(LocalDate.now())) {
            throw new IncorrectDateException("La fecha solicitada (" + date + ") no puede ser una fecha pasada.");
        }

        if (date.isAfter(LocalDate.now().plusDays(7))) {
            throw new IncorrectDateException("La cartelera solo se puede consultar para los próximos 7 días.");
        }

        List<Session> sessions = sessionDao.findByDate(date);

        Map<Movie, List<Session>> grouped = new HashMap<>();
        for (Session s : sessions) {
            grouped.computeIfAbsent(s.getMovie(), k -> new ArrayList<>()).add(s);
        }
        List<MovieListingEntry> result = new ArrayList<>();
        for (Map.Entry<Movie, List<Session>> entry : grouped.entrySet())
        {
            List<Session> sortedSessions = entry.getValue();
            sortedSessions.sort(Comparator.comparing(Session::getSessionStartTime));
            
            result.add(new MovieListingEntry(entry.getKey(), sortedSessions));
        }

        result.sort(Comparator.comparing(entry -> entry.getMovie().getTitle()));

        return result;
    }

    @Override
    public Movie viewMovieDetails(Long MovieId) throws InstanceNotFoundException
    {
        Optional<Movie> optMovie = movieDao.findById(MovieId);
        if(optMovie.isEmpty())
            throw new InstanceNotFoundException("No se ha encontrado la película", MovieId);
        return optMovie.get();
    }
}