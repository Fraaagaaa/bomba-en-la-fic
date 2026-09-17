package es.udc.paproject.backend.model.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Movie {
    private Long id;
    private String title;
    private String summary;
    private Integer duration;

    public Movie() {}

    public Movie(String title, String summary, Integer duration) {
        this.title = title;
        this.summary = summary;
        this.duration = duration;
    }

    public Movie(Long id, String title, String summary, Integer duration) {
        this.id = id;
        this.title = title;
        this.summary = summary;
        this.duration = duration;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getSummary() {
        return summary;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public Integer getDuration() {
        return duration;
    }

    public void setDuration(Integer duration) {
        this.duration = duration;
    }
}