package es.udc.paproject.backend.model.entities;


import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Saloon {
    private String name;
    private int capacity;
    private Long id;


    public Saloon() {}

    public Saloon(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    public Saloon(Long id, String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

}