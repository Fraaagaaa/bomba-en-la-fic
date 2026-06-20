package es.udc.paproject.backend.test.model.services;

import es.udc.paproject.backend.model.entities.*;
import es.udc.paproject.backend.model.exceptions.*;
import es.udc.paproject.backend.model.services.*;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.transaction.annotation.Transactional;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest
@ActiveProfiles("test")
@Transactional
public class PurchaseServiceTest
{
    private final LocalDateTime HOY = LocalDateTime.now().withNano(0);
    private final LocalDateTime MANANA = LocalDateTime.now().withNano(0).plusDays(1);
    private final LocalDateTime AYER = LocalDateTime.now().withNano(0).minusDays(1);


    @Autowired
    private PurchaseService purchaseService;

    @Autowired
    private UserDao userDao;

    @Autowired
    private MovieDao movieDao;

    @Autowired
    private SaloonDao saloonDao;

    @Autowired
    private SessionDao sessionDao;

    @Autowired
    private PurchaseDao purchaseDao;

    private User createUser(String userName) {
        User user = new User(userName, "password", "firstName", "lastName", userName + "@" + userName + ".com");
        user.setRole(User.RoleType.USER);
        return userDao.save(user);
    }

    private Session createSession(LocalDateTime startTime) {
        Movie movie = new Movie("Pelicula Test", "Resumen test", 120);
        movieDao.save(movie);

        Saloon saloon = new Saloon("Sala 1", 50);
        saloonDao.save(saloon);

        Session session = new Session(new BigDecimal("10.00"), startTime, saloon, movie, 50);
        return sessionDao.save(session);
    }

    private Purchase createPurchase(User user, Session session, LocalDateTime date, String creditCard, boolean recogidas) {
        Purchase purchase = new Purchase(2, date, creditCard, recogidas, session, user);
        return purchaseDao.save(purchase);
    }

//Test Funcionalidad 5
    @Test
    public void testViewPurchasesHistorySuccess() {
        User user = createUser("user");
        Session session = createSession(MANANA);

        Purchase compraAyer = createPurchase(user, session, AYER, "1234567890123456", false);
        Purchase compraHoy = createPurchase(user, session, HOY, "1234567890123456", false);

        Block<Purchase> result = purchaseService.viewPurchasesHistory(user.getId(), 0, 10);

        assertEquals(2, result.getItems().size());
        assertFalse(result.getExistMoreItems());

        assertEquals(compraHoy.getId(), result.getItems().get(0).getId());
        assertEquals(compraAyer.getId(), result.getItems().get(1).getId());
    }


//Tests funcionalidad 6
    @Test
    public void testDeliverTicketsSuccess() throws Exception {
        User user = createUser("user");
        Session session = createSession(MANANA);
        String tarjeta = "1234567890123456";
        Purchase purchase = createPurchase(user, session, HOY, tarjeta, false);

        purchaseService.deliverTickets(tarjeta, purchase.getId());

        Purchase updatedPurchase = purchaseDao.findById(purchase.getId()).get();
        assertTrue(updatedPurchase.isRecogidas());
    }

    @Test
    public void testDeliverTicketsThrowsCreditCardDoesNotMatch() {
        User user = createUser("user");
        Session session = createSession(MANANA);
        Purchase purchase = createPurchase(user, session, HOY, "1234567890123456", false);

        assertThrows(CredircardDoesNotMatch.class, () ->
                purchaseService.deliverTickets("9999999999999999", purchase.getId())
        );
    }

    @Test
    public void testDeliverTicketsThrowsSessionAlreadyStarted() {
        User user = createUser("user");
        Session session = createSession(AYER);
        String tarjeta = "1234567890123456";
        Purchase purchase = createPurchase(user, session, AYER.minusHours(1), tarjeta, false);

        assertThrows(SessionAlreadyStartedException.class, () ->
                purchaseService.deliverTickets(tarjeta, purchase.getId())
        );
    }

    @Test
    public void testDeliverTicketsThrowsTicketsAlreadyRetrieved() {
        User user = createUser("user");
        Session session = createSession(MANANA);
        String tarjeta = "1234567890123456";
        Purchase purchase = createPurchase(user, session, HOY, tarjeta, true);

        assertThrows(TicketsAlreadyRetrievedException.class, () ->
                purchaseService.deliverTickets(tarjeta, purchase.getId())
        );
    }
}