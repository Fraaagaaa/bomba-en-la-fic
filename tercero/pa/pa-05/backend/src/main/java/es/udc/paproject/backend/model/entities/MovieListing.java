package es.udc.paproject.backend.model.entities;

import java.util.List;

public class MovieListing {

    private Long id;
    private List<MovieListingEntry> entries;

    public MovieListing(Long id, List<MovieListingEntry> entries) {
        this.id = id;
        this.entries = entries;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public List<MovieListingEntry> getEntries() {
        return entries;
    }

    public void setEntries(List<MovieListingEntry> entries) {
        this.entries = entries;
    }
}