package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.*;
import es.udc.paproject.backend.model.exceptions.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Slice;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.Optional;

@Service
@Transactional
public class PurchaseServiceImpl implements PurchaseService
{
    @Autowired
    private UserDao userDao;

    @Autowired
    private PurchaseDao purchaseDao;

    @Autowired
    private SessionDao sessionDao;

    @Override
    public Purchase purchase(Long sessionId, Long userId, int amount, String creditCardNumber) throws AllTicketsSoldException, SessionAlreadyStartedException, InstanceNotFoundException
    {
        Optional<Session> optSession = sessionDao.findById(sessionId);
        Optional<User> optUser = userDao.findById(userId);

        if(optUser.isEmpty())
            throw new InstanceNotFoundException("No se ha encontrado al usuario", sessionId);

        if(optSession.isEmpty())
            throw new InstanceNotFoundException("No se ha encontrado la session", sessionId);

        User user = optUser.get();
        Session session = optSession.get();

        if(session.getSessionStartTime().withNano(0).isBefore(LocalDateTime.now().withNano(0)))
            throw new SessionAlreadyStartedException("Ya ha empezado la session", sessionId);

        if(session.getAsientosLibres() < amount)
            throw new AllTicketsSoldException("Quedan menos asientos libres de los que se intenta comprar", sessionId);

        session.setAsientosLibres(session.getAsientosLibres() - amount);
        Purchase purchase = new Purchase(amount, LocalDateTime.now(), creditCardNumber, false, session, user);
        return purchaseDao.save(purchase);
    }

    @Override
    public Block<Purchase> viewPurchasesHistory(Long userId, int page, int size) {

        PageRequest pageRequest = PageRequest.of(page, size);
        Slice<Purchase> slice = purchaseDao.findByUserIdOrderByPurchaseDateDesc(userId, pageRequest);
        return new Block<>(slice.getContent(), slice.hasNext());
    }

    @Transactional
    @Override
    public void deliverTickets(String creditCardNumber, Long purchaseId) throws SessionAlreadyStartedException, TicketsAlreadyRetrievedException, CredircardDoesNotMatch, InstanceNotFoundException {
        Optional<Purchase> purchaseOptional = purchaseDao.findById(purchaseId);
        if (!purchaseOptional.isPresent()) {
            throw new InstanceNotFoundException("project.entities.purchase", purchaseId);
        }

        Purchase purchase = purchaseOptional.get();
        if (!purchase.getCreditCard().equals(creditCardNumber)) {
            throw new CredircardDoesNotMatch("El número de tarjeta no coincide con el de la compra.");
        }


        if (purchase.isRecogidas()) {
            throw new TicketsAlreadyRetrievedException("Las entradas de esta compra ya fueron entregadas.");
        }

        LocalDateTime now = LocalDateTime.now();
        if (purchase.getSession().getSessionStartTime().isBefore(now)) {
            throw new SessionAlreadyStartedException("Session",purchase.getSession().getId());
        }

        purchase.setRecogidas(true);
    }
}
