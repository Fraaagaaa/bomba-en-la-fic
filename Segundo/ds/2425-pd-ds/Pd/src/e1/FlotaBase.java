package e1;

import java.util.ArrayList;
import java.util.List;

public abstract class FlotaBase implements Flota, Sujeto {
    private final String nombreFlota;
    private final int fondos;
    private final List<Buque> Armamento;
    private final List<ObservadorInterfaz> observadores = new ArrayList<>();

    public FlotaBase(String nombreFlota, int fondos)
    {
        this.nombreFlota = nombreFlota;
        this.fondos = fondos;
        this.Armamento = new ArrayList<>();
    }

    public int getFondos()
    {
        return fondos;
    }

    @Override
    public String getNombreFlota()
    {
        return nombreFlota;
    }

    @Override
    public List<Buque> getArmamento()
    {
        return Armamento;
    }

    @Override
    public void addBuque(Buque buque)
    {
        if (!buque.getFlota().getNombreFlota().equals(this.nombreFlota))
            throw new IllegalArgumentException("Nombre de la flota incorrecto");
        if (Armamento.contains(buque))
            throw new IllegalArgumentException("Ya existe este buque");

        buque.setFlota(this);
        Armamento.add(buque);
        notifyObservador("El buque " + buque + " se ha unido a la flota " + nombreFlota + ".");
    }

    public String listarBuques()
    {
        if (Armamento.isEmpty())
            throw new IllegalArgumentException("No hay buques en la flota");

        StringBuilder msg = new StringBuilder();

        for (Buque buque : Armamento)
            msg.append(buque.toString());

        return msg.toString();
    }

    public String listarInactivos()
    {
        if (Armamento.isEmpty())
            throw new IllegalArgumentException("No hay buques en la flota");

        String msg = "INACTIVE VESSELS\n----------------------------------\n";
        for (Buque buque : Armamento)
        {
            if (!buque.getState().equals("Decommissioned"))
                continue;
            msg += buque;
        }
        if (msg.equals("INACTIVE VESSELS\n----------------------------------\n"))
            throw new IllegalArgumentException("No hay buques inactivos en la flota");

        return msg;
    }

    public Boolean joinBattle(Buque buque)
    {
        if (buque.enBase && !buque.inRepair())
        {
            buque.enBase = false;
            notifyObservador("El buque " + buque.getNombre() + " se ha unido a la batalla.");
            return true;
        }
        return false;
    }

    public Boolean leaveBattle(Buque buque)
    {
        if (buque.enBase)
            throw new IllegalArgumentException("El buque ya está en la base");

        if (buque.getDamage() > 100)
        {
            buque.estado = "Sunk";
            notifyObservador("El buque " + buque.getNombre() + " se ha hundido.");
            return false;
        }
        buque.enBase = true;
        buque.misiones++;
        notifyObservador("El buque " + buque.getNombre() + " ha regresado a la base.");
        return true;
    }

    public Integer Recompensa(Buque buque)
    {
        if (!buque.getFlota().getNombreFlota().equals(this.nombreFlota))
            throw new IllegalArgumentException("El barco no es de esta flota");

        if (buque.heavyWeight())
            return 5;
        return 1;
    }

    public Boolean repararBuque(Buque buque)
    {
        if (!buque.enBase())
            throw new IllegalArgumentException("El barco no está en la base");
        if (!buque.getFlota().getNombreFlota().equals(this.nombreFlota))
            throw new IllegalArgumentException("El barco no es de esta flota");
        if(!buque.isExpress())
        {
            if (!buque.inRepair())
                throw new IllegalArgumentException("El barco no solicitó una reparación");
            if (this.getFondos() >= buque.getDamage() * buque.getCostMultiplier())
            {
                buque.reparar();
                notifyObservador("El buque " + buque + " ha sido reparado.");
                return true;
            }
            return false;
        }
        buque.repararExpress();
        notifyObservador("El buque " + buque + " ha sido reparado de forma express.");
        return true;
    }

    public void desmantelamiento(Buque buque)
    {
        if (Armamento.contains(buque))
        {
            Armamento.remove(buque);
            notifyObservador("El buque " + buque + " ha sido desmantelado de la flota " + nombreFlota + ".");
        }
        else
            throw new IllegalArgumentException("El buque no pertenece a la flota");
    }

    public String sendRepairRequest(Buque buque)
    {
        if (buque.getDamage() == 0)
            throw new IllegalArgumentException("El buque no está dañado");
        if (!buque.enBase)
            throw new IllegalArgumentException("El buque no está en la base");

        buque.siendoReparado = true;
        buque.estado = "In repair";
        notifyObservador("El buque " + buque.getNombre() + " ha solicitado una reparación.");
        return "A repair request has been filed for " + buque.getNombre() + " | Expected repair cost: " + buque.getCostMultiplier() * buque.getDamage();
    }
}
