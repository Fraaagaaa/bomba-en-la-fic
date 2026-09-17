package es.udc.paproject.backend.rest.dtos;

import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

public class DeliverTicketsParamsDto {
    private String creditCard;

    @NotNull
    @Size(min=16, max=16)
    public String getCreditCard() { return creditCard; }
    public void setCreditCard(String creditCard) { this.creditCard = creditCard; }
}
