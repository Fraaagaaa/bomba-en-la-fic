package es.udc.paproject.backend.rest.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import es.udc.paproject.backend.model.entities.Purchase;
import es.udc.paproject.backend.model.exceptions.*;
import es.udc.paproject.backend.model.services.Block;
import es.udc.paproject.backend.model.services.PurchaseService;
import es.udc.paproject.backend.rest.dtos.BlockDto;
import es.udc.paproject.backend.rest.dtos.*;

import static es.udc.paproject.backend.rest.dtos.PurchaseConversor.*;

@RestController
@RequestMapping("/shopping")
public class PurchaseController {

    @Autowired
    private PurchaseService purchaseService;

    @PostMapping("/buy")
    @ResponseStatus(HttpStatus.CREATED)
    public PurchaseDto buy(
            @RequestAttribute Long userId,
            @Validated @RequestBody PurchaseParamsDto params)
            throws InstanceNotFoundException, SessionAlreadyStartedException, AllTicketsSoldException {

        Purchase purchase = purchaseService.purchase(
                params.getSessionId(),
                userId,
                params.getQuantity(),
                params.getCreditCard());


        return toPurchaseDto(purchase);
    }


    @GetMapping("/purchases")
    public BlockDto<PurchaseDto> findPurchases(
            @RequestAttribute Long userId,
            @RequestParam(defaultValue = "0") int page) {

        Block<Purchase> purchaseBlock = purchaseService.viewPurchasesHistory(userId, page, 2);

        return toPurchaseBlockDto(purchaseBlock);
    }

    @PostMapping("/purchases/{id}/deliver")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    public void deliverTickets(
            @PathVariable("id") Long purchaseId,
            @Validated @RequestBody DeliverTicketsParamsDto params)
            throws InstanceNotFoundException, SessionAlreadyStartedException,
            TicketsAlreadyRetrievedException, CredircardDoesNotMatch {

        purchaseService.deliverTickets(params.getCreditCard(), purchaseId);
    }
}