package e1;

import java.util.List;
import java.util.Observer;

public interface Flota
{
    List<Buque> getArmamento();

    String getNombreFlota();

    void addBuque(Buque buque);

    String listarBuques();

    String listarInactivos();

    Boolean joinBattle(Buque buque);

    Boolean leaveBattle(Buque buque);

    Integer Recompensa(Buque buque);

    Boolean repararBuque(Buque buque);

    void desmantelamiento(Buque buque);

    String sendRepairRequest(Buque buque);
}
