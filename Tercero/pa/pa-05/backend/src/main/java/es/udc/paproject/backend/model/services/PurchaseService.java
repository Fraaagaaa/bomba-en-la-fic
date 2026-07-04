package es.udc.paproject.backend.model.services;

import es.udc.paproject.backend.model.entities.Purchase;
import es.udc.paproject.backend.model.exceptions.*;

public interface PurchaseService
{
    // 4: Comprar entradas
    Purchase purchase(Long sessionId, Long userId, int amount, String creditCardNumber) throws AllTicketsSoldException, SessionAlreadyStartedException, InstanceNotFoundException;

    // 5: Visualizar histórico de compras
    Block<Purchase> viewPurchasesHistory(Long userId, int page, int size);
    // Block es como una lista, pero devuelve un booleano de si hay más elementos (para lo de página 1 de x)

    // 6: Entregar entradas de una compra
    void deliverTickets(String creditCardNumber, Long purchaseId) throws SessionAlreadyStartedException, TicketsAlreadyRetrievedException, CredircardDoesNotMatch, InstanceNotFoundException;
}
