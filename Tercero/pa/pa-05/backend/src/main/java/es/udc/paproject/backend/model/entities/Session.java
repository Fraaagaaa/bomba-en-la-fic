package es.udc.paproject.backend.model.entities;

import jakarta.persistence.*;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import jakarta.persistence.Version;

@Entity
public class Session {
    private Long id;
    private BigDecimal price;
    private LocalDateTime sessionStartTime;
    private Saloon saloon;
    private Movie movie;
    private int asientosLibres;
    private Long version;

    public Session() {}

    public Session(BigDecimal price, LocalDateTime sessionStartTime, Saloon saloon, Movie movie, int asientosLibres) {
        this.price = price;
        this.sessionStartTime = sessionStartTime;
        this.saloon = saloon;
        this.movie = movie;
        this.asientosLibres = asientosLibres;
    }

    public Session(Long id, BigDecimal price, LocalDateTime sessionStartTime, Saloon saloon, Movie movie, int asientosLibres) {
        this.id = id;
        this.price = price;
        this.sessionStartTime = sessionStartTime;
        this.saloon = saloon;
        this.movie = movie;
        this.asientosLibres = asientosLibres;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    @Version
    public Long getVersion() {
        return version;
    }

    public void setVersion(Long version) {
        this.version = version;
    }

    public BigDecimal getPrice() {
        return price;
    }

    public void setPrice(BigDecimal price) {
        this.price = price;
    }

    public LocalDateTime getSessionStartTime() {
        return sessionStartTime;
    }

    public void setSessionStartTime(LocalDateTime sessionStartTime) {
        this.sessionStartTime = sessionStartTime;
    }

    @ManyToOne
    @JoinColumn(name = "saloon_id")
    public Saloon getSaloon() {
        return saloon;
    }

    public void setSaloon(Saloon saloon) {
        this.saloon = saloon;
    }

    @ManyToOne
    @JoinColumn(name = "movie_id")
    public Movie getMovie() {
        return movie;
    }

    public void setMovie(Movie movie) {
        this.movie = movie;
    }

    public int getAsientosLibres() {
        return asientosLibres;
    }

    public void setAsientosLibres(int asientosLibres) {
        this.asientosLibres = asientosLibres;
    }
}