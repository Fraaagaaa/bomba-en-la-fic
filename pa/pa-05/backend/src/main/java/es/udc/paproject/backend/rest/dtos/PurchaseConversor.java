package es.udc.paproject.backend.rest.dtos;

import java.math.BigDecimal;
import java.time.ZoneOffset;
import java.util.List;
import java.util.stream.Collectors;

import es.udc.paproject.backend.model.entities.Purchase;
import es.udc.paproject.backend.model.services.Block;
import es.udc.paproject.backend.rest.dtos.BlockDto;

public class PurchaseConversor {

    private PurchaseConversor() {}

    public static PurchaseDto toPurchaseDto(Purchase purchase) {
        PurchaseDto purchaseDto = new PurchaseDto(
                purchase.getId(),
                purchase.getTicketAmmount(),
                purchase.getPurchaseDate(),
                purchase.isRecogidas(),
                purchase.getSession().getId(),
                purchase.getUser().getId()
        );

        purchaseDto.setMovieTitle(purchase.getSession().getMovie().getTitle());
        purchaseDto.setSessionDate(purchase.getSession().getSessionStartTime());
        purchaseDto.setTotalPrice(purchase.getSession().getPrice().multiply(new BigDecimal(purchase.getTicketAmmount())));

        return purchaseDto;
    }

    public static BlockDto<PurchaseDto> toPurchaseBlockDto(Block<Purchase> block) {
        List<PurchaseDto> items = block.getItems().stream()
                .map(PurchaseConversor::toPurchaseDto)
                .collect(Collectors.toList());

        return new BlockDto<>(items, block.getExistMoreItems());
    }
}