package es.udc.paproject.backend.test.model.services;

import 	java.math.BigDecimal;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.transaction.annotation.Transactional;

import es.udc.paproject.backend.model.entities.Movie;
import es.udc.paproject.backend.model.entities.Saloon;
import es.udc.paproject.backend.model.entities.Session;
import es.udc.paproject.backend.model.entities.SessionDao;
import es.udc.paproject.backend.model.exceptions.InstanceNotFoundException;
import es.udc.paproject.backend.model.exceptions.SessionAlreadyStartedException;
import es.udc.paproject.backend.model.services.SessionService;

@SpringBootTest
@ActiveProfiles("test")
@Transactional
public class SessionServiceTest {

	private final LocalDateTime NOW = LocalDateTime.now().withNano(0);

	@Autowired
	private SessionService sessionService;

	@Autowired
	private SessionDao sessionDao;

	@Autowired
	private MovieDao movieDao;

	@Autowired
	private SaloonDao saloonDao;

	private Session createSession(LocalDateTime startTime) {
		Movie movie = new Movie("Pelicula Test", "Resumen test", 120);
		movieDao.save(movie);
		Saloon saloon = new Saloon("Sala 1", 50);
		saloonDao.save(saloon);

		Session session = new Session(new BigDecimal("10.00"), startTime, saloon, movie, 50);
		return sessionDao.save(session);
	}

	@Test
	public void testViewSessionDetailsOk() throws InstanceNotFoundException, SessionAlreadyStartedException {
		Session session = createSession(NOW.plusDays(1));

		Session result = sessionService.viewSessionDetails(session.getId());

		assertEquals(session.getId(), result.getId());
		assertEquals(session.getSessionStartTime(), result.getSessionStartTime());
		assertEquals(session.getPrice(), result.getPrice());
	}

	@Test
	public void testViewSessionDetailsNotFound() {
		Long nonExistingId = -1L;

		assertThrows(InstanceNotFoundException.class, () ->
				sessionService.viewSessionDetails(nonExistingId)
		);
	}

	@Test
	public void testViewSessionDetailsAlreadyStarted() {
		Session session = createSession(NOW.minusDays(1));

		assertThrows(SessionAlreadyStartedException.class, () ->
				sessionService.viewSessionDetails(session.getId())
		);
	}
}
