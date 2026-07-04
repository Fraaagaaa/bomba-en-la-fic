package es.udc.paproject.backend.rest.dtos;

import java.math.BigDecimal;
import java.time.LocalDateTime;

public class PurchaseDto
{
    private Long id;
    private Integer ticketAmmount;
    private LocalDateTime purchaseDate;
    private boolean recogidas;
    private Long sessionId;
    private Long userId;
    private String movieTitle;
    private LocalDateTime sessionDate;
    private BigDecimal totalPrice;

    public PurchaseDto() {}

    public PurchaseDto(Long id, Integer ticketAmmount, LocalDateTime purchaseDate,
                       boolean recogidas, Long sessionId, Long userId) {
        this.id = id;
        this.ticketAmmount = ticketAmmount;
        this.purchaseDate = purchaseDate;
        this.recogidas = recogidas;
        this.sessionId = sessionId;
        this.userId = userId;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Integer getTicketAmmount() {
        return ticketAmmount;
    }

    public void setTicketAmmount(Integer ticketAmmount) {
        this.ticketAmmount = ticketAmmount;
    }

    public LocalDateTime getPurchaseDate() {
        return purchaseDate;
    }

    public void setPurchaseDate(LocalDateTime purchaseDate) {
        this.purchaseDate = purchaseDate;
    }

    public boolean isRecogidas() {
        return recogidas;
    }

    public void setRecogidas(boolean recogidas) {
        this.recogidas = recogidas;
    }

    public Long getSessionId() {
        return sessionId;
    }

    public void setSessionId(Long sessionId) {
        this.sessionId = sessionId;
    }

    public Long getUserId() {
        return userId;
    }

    public void setUserId(Long userId) {
        this.userId = userId;
    }

    public String getMovieTitle() {
        return movieTitle;
    }

    public void setMovieTitle(String movieTitle) {
        this.movieTitle = movieTitle;
    }

    public LocalDateTime getSessionDate() {
        return sessionDate;
    }

    public void setSessionDate(LocalDateTime sessionDate) {
        this.sessionDate = sessionDate;
    }

    public BigDecimal getTotalPrice() {
        return totalPrice;
    }

    public void setTotalPrice(BigDecimal totalPrice) {
        this.totalPrice = totalPrice;
    }
}