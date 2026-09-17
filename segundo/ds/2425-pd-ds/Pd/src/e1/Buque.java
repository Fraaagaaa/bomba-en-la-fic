package e1;

import java.util.ArrayList;
import java.util.List;

class Buque implements Sujeto
{
    private final String nombre;
    private final TipoBuque tipo;
    boolean enBase;
    private FlotaBase flota;
    String estado;
    int misiones;
    boolean siendoReparado;
    private final double repairCostMultiplier;
    private final boolean express;
    private int dano;

    private final List<ObservadorInterfaz> Observadores = new ArrayList<>();

    public Buque(String nombre, TipoBuque tipo, String estado, int dano) {
        this.nombre = nombre;
        this.tipo = tipo;
        this.enBase = true;
        this.estado = estado;
        this.misiones = 0;
        this.dano = dano;
        this.siendoReparado = false;
        switch (tipo)
        {
            case DE: case DD: this.repairCostMultiplier = 1; break;
            case CL: case AV: this.repairCostMultiplier = 1.2; break;
            case CA: case CV: this.repairCostMultiplier = 1.5; break;
            default: this.repairCostMultiplier = 2; break;
        }
        this.express = (this.tipo.toString().equals("DE") || this.tipo.toString().equals("DD"));
    }

    @Override
    public void addObservador(ObservadorInterfaz Observador) {
        Observadores.add(Observador);
    }

    @Override
    public void removeObservador(ObservadorInterfaz Observador) {
        Observadores.remove(Observador);
    }

    @Override
    public void notifyObservador(String message)
    {
        for (ObservadorInterfaz Observador : Observadores)
            Observador.update(message);
    }
    public String getNombre()
    {
        return nombre;
    }

    public FlotaBase getFlota()
    {
        return this.flota;
    }

    public String getState()
    {
        return this.estado;
    }

    public int getDamage()
    {
        return this.dano;
    }

    public Boolean enBase()
    {
        return this.enBase;
    }

    public Boolean inRepair()
    {
        return this.siendoReparado;
    }

    public double getCostMultiplier()
    {
        return this.repairCostMultiplier;
    }

    public String getType()
    {
        return tipo.toString();
    }

    public Boolean heavyWeight()
    {
        return tipo.toString().equals("CA") || tipo.toString().equals("CV") || tipo.toString().equals("BB");
    }

    public void setFlota(FlotaBase flota)
    {
        this.flota = flota;
    }

    public Boolean isExpress()
    {
        return this.express;
    }

    public void reparar()
    {
        if (this.siendoReparado)
        {
            this.dano = 0;
            notifyObservador("El buque " + nombre + " ha sido reparado.");
        }
        else
            throw new IllegalArgumentException("El barco no está en reparación");
    }

    public void repararExpress()
    {
        this.dano = 0;
        notifyObservador("El buque " + nombre + " ha sido reparado de forma express.");
    }

    @Override
    public String toString()
    {
        return "Name: " + nombre + " (" + tipo + ") | Reasons: " + estado + " | Missions: " + misiones + "\n";
    }
}
