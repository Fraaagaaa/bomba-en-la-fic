package es.udc.paproject.backend.model.entities;

import jakarta.persistence.*;
import java.time.LocalDateTime;

@Entity
public class Purchase {
    private Long id;
    private Integer ticketAmmount;
    private LocalDateTime purchaseDate;
    private String creditCard;
    private boolean recogidas;
    private Session session;
    private User user;

    public Purchase() {}

    public Purchase(Integer ticketAmmount, LocalDateTime purchaseDate, String creditCard, boolean recogidas, Session session, User user) {
        this.ticketAmmount = ticketAmmount;
        this.purchaseDate = purchaseDate;
        this.creditCard = creditCard;
        this.recogidas = recogidas;
        this.session = session;
        this.user = user;
    }

    public Purchase(Long id, Integer ticketAmmount, LocalDateTime purchaseDate, String creditCard, boolean recogidas, Session session, User user) {
        this.id = id;
        this.ticketAmmount = ticketAmmount;
        this.purchaseDate = purchaseDate;
        this.creditCard = creditCard;
        this.recogidas = recogidas;
        this.session = session;
        this.user = user;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
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

    public String getCreditCard() {
        return creditCard;
    }

    public void setCreditCard(String creditCard) {
        this.creditCard = creditCard;
    }

    public boolean isRecogidas() {
        return recogidas;
    }

    public void setRecogidas(boolean recogidas) {
        this.recogidas = recogidas;
    }

    @ManyToOne(optional = false, fetch = FetchType.LAZY)
    @JoinColumn(name = "session_id")
    public Session getSession() {
        return session;
    }

    public void setSession(Session session) {
        this.session = session;
    }

    @ManyToOne(optional = false, fetch = FetchType.LAZY)
    @JoinColumn(name = "userId")
    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }
}