package e1;

import static e1.TipoBuque.*;
import static org.junit.jupiter.api.Assertions.*;
import java.util.List;
import java.util.ArrayList;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class FlotaTest
{
    private FlotaBase FlotaAzul, FlotaRoja, FlotaVerde, FlotaAmarilla;
    private Buque buque1, buque2, buque3, buque4, buque5, buque6, buque7, buque8, buque9;

    @BeforeEach
    void setUp()
    {
        // Flotas
        FlotaAzul = new CrearFlota("Azul", 50000);
        FlotaRoja = new CrearFlota("Red", 37000);
        FlotaVerde = new CrearFlota("Verde", 100);
        FlotaAmarilla = new CrearFlota("Amarilla", 100);

        // Buques
        buque1 = new Buque("USS Enterprise", DE, "Decommissioned", 20);
        buque2 = new Buque("Admiral Kuznetsov", DD, "Decommissioned", 10);
        buque3 = new Buque("USS Arizona", CL, "Decommissioned", 0);
        buque4 = new Buque("USS Missouri", AV, "In repair", 20);
        buque5 = new Buque("USS Carl Vinson", CA, "Battling", 130);
        buque6 = new Buque("USS John S. McCain", CV, "Decommissioned", 0);
        buque7 = new Buque("K-141 Kursk", BB, "Decommissioned", 0);
        buque8 = new Buque("Sovremenny", DD, "Battling", 50);
        buque9 = new Buque("Varyag", BB, "Battling", 80);

        // Asignar flotas
        buque1.setFlota(FlotaAzul);
        buque2.setFlota(FlotaRoja);
        buque3.setFlota(FlotaAzul);
        buque4.setFlota(FlotaAzul);
        buque5.setFlota(FlotaAzul);
        buque6.setFlota(FlotaAzul);
        buque7.setFlota(FlotaAzul);
        buque8.setFlota(FlotaRoja);
        buque9.setFlota(FlotaAmarilla);

        // Añadir buques a las flotas
        FlotaAzul.addBuque(buque1);
        FlotaRoja.addBuque(buque2);
        FlotaAzul.addBuque(buque3);
        FlotaAzul.addBuque(buque4);
        FlotaAzul.addBuque(buque5);
        FlotaAzul.addBuque(buque6);
        FlotaAzul.addBuque(buque7);
        FlotaRoja.addBuque(buque8);
        FlotaAmarilla.addBuque(buque9);
    }

    @Test
    void testVerificarToString() {
        assertEquals("Azul", FlotaAzul.toString());
        assertEquals(37000, FlotaRoja.getFondos());
        assertEquals("Name: USS Enterprise (DE) | Reasons: Decommissioned | Missions: 0\n", buque1.toString());
        assertEquals("Name: Admiral Kuznetsov (DD) | Reasons: Decommissioned | Missions: 0\n", buque2.toString());
    }

    @Test
    void testGetType() {
        assertEquals("DE", buque1.getType());
        assertEquals("DD", buque2.getType());
        assertEquals("CL", buque3.getType());
        assertEquals("AV", buque4.getType());
        assertEquals("CA", buque5.getType());
        assertEquals("CV", buque6.getType());
        assertEquals("BB", buque7.getType());
        assertEquals("DD", buque8.getType());
    }

    @Test
    void testArmamento() {
        assertEquals("""
                Name: USS Enterprise (DE) | Reasons: Decommissioned | Missions: 0
                Name: USS Arizona (CL) | Reasons: Decommissioned | Missions: 0
                Name: USS Missouri (AV) | Reasons: In repair | Missions: 0
                Name: USS Carl Vinson (CA) | Reasons: Battling | Missions: 0
                Name: USS John S. McCain (CV) | Reasons: Decommissioned | Missions: 0
                Name: K-141 Kursk (BB) | Reasons: Decommissioned | Missions: 0
                """, FlotaAzul.listarBuques());

        assertEquals("""
                INACTIVE VESSELS
                ----------------------------------
                Name: USS Enterprise (DE) | Reasons: Decommissioned | Missions: 0
                Name: USS Arizona (CL) | Reasons: Decommissioned | Missions: 0
                Name: USS John S. McCain (CV) | Reasons: Decommissioned | Missions: 0
                Name: K-141 Kursk (BB) | Reasons: Decommissioned | Missions: 0
                """, FlotaAzul.listarInactivos());

        assertEquals("""
                [Name: USS Enterprise (DE) | Reasons: Decommissioned | Missions: 0
                , Name: USS Arizona (CL) | Reasons: Decommissioned | Missions: 0
                , Name: USS Missouri (AV) | Reasons: In repair | Missions: 0
                , Name: USS Carl Vinson (CA) | Reasons: Battling | Missions: 0
                , Name: USS John S. McCain (CV) | Reasons: Decommissioned | Missions: 0
                , Name: K-141 Kursk (BB) | Reasons: Decommissioned | Missions: 0
                ]""", FlotaAzul.getArmamento().toString());

        assertThrows(IllegalArgumentException.class, () -> FlotaVerde.listarInactivos());
        assertThrows(IllegalArgumentException.class, () -> FlotaVerde.listarBuques());

        FlotaAzul.desmantelamiento(buque1);
        assertEquals("""
                Name: USS Arizona (CL) | Reasons: Decommissioned | Missions: 0
                Name: USS Missouri (AV) | Reasons: In repair | Missions: 0
                Name: USS Carl Vinson (CA) | Reasons: Battling | Missions: 0
                Name: USS John S. McCain (CV) | Reasons: Decommissioned | Missions: 0
                Name: K-141 Kursk (BB) | Reasons: Decommissioned | Missions: 0
                """, FlotaAzul.listarBuques());

        assertThrows(IllegalArgumentException.class, () -> FlotaVerde.desmantelamiento(buque2));
        assertThrows(IllegalArgumentException.class, () -> FlotaAmarilla.listarInactivos());
    }

    @Test
    void testFlotaEquivoca() {
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.addBuque(buque2));
        assertThrows(IllegalArgumentException.class, () -> FlotaRoja.addBuque(buque1));
        assertThrows(IllegalArgumentException.class, () -> FlotaRoja.addBuque(buque2));
    }

    @Test
    void testReparaciones()
    {
        assertEquals(1, buque1.getCostMultiplier());
        assertEquals(1.2, buque3.getCostMultiplier());
        assertEquals(1.5, buque5.getCostMultiplier());
        assertEquals(2, buque7.getCostMultiplier());

        assertTrue(buque1.isExpress());
        assertFalse(buque2.siendoReparado);
        assertFalse(buque6.isExpress());

        FlotaRoja.joinBattle(buque2);
        FlotaAzul.joinBattle(buque3);
        FlotaAmarilla.joinBattle(buque9);
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.sendRepairRequest(buque3));
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.repararBuque(buque3));
        assertThrows(IllegalArgumentException.class, () -> FlotaRoja.sendRepairRequest(buque2));
        assertThrows(IllegalArgumentException.class, () -> FlotaAmarilla.sendRepairRequest(buque9));
        FlotaRoja.leaveBattle(buque2);
        FlotaAzul.leaveBattle(buque3);
        FlotaAmarilla.leaveBattle(buque9);
        FlotaAmarilla.sendRepairRequest(buque9);
        assertFalse(FlotaAmarilla.repararBuque(buque9));

        assertThrows(IllegalArgumentException.class, () -> buque2.reparar());
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.repararBuque(buque9));
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.repararBuque(buque3));

        FlotaAzul.sendRepairRequest(buque4);
        FlotaAzul.repararBuque(buque4);
        FlotaAmarilla.sendRepairRequest(buque9);
        FlotaRoja.sendRepairRequest(buque2);
        FlotaRoja.repararBuque(buque2);

        assertFalse(buque8.inRepair());
        assertEquals("A repair request has been filed for Sovremenny | Expected repair cost: 50.0", FlotaRoja.sendRepairRequest(buque8));
        assertTrue(buque8.inRepair());
        assertEquals("In repair", buque8.getState());
        assertTrue(buque8.getDamage() > 0);
        FlotaRoja.repararBuque(buque8);
        assertEquals(0, buque8.getDamage());

        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.sendRepairRequest(buque4));
    }
    @Test
    void testRecompensa() {
        assertEquals(1, FlotaAzul.Recompensa(buque1));
        assertEquals(1, FlotaAzul.Recompensa(buque3));
        assertEquals(1, FlotaAzul.Recompensa(buque4));
        assertEquals(5, FlotaAzul.Recompensa(buque5));
        assertEquals(5, FlotaAzul.Recompensa(buque6));
        assertEquals(5, FlotaAzul.Recompensa(buque7));
        assertThrows(IllegalArgumentException.class, () -> FlotaAzul.Recompensa(buque2));
    }

    @Test
    void testJoinBattle()
    {
        FlotaAzul.joinBattle(buque6);
        FlotaAzul.joinBattle(buque5);
        assertTrue(FlotaAzul.joinBattle(buque1));
        assertFalse(FlotaAzul.joinBattle(buque6));
        assertThrows(IllegalArgumentException.class, () -> FlotaRoja.leaveBattle(buque2));
        assertTrue(FlotaAzul.leaveBattle(buque1));
        assertEquals(130, buque5.getDamage());
        assertFalse(FlotaAzul.leaveBattle(buque5));
        assertEquals("Sunk", buque5.getState());
    }
    @Test
    void testObservadores()
    {
        Observador observador = new Observador();

        buque8.addObservador(observador);
        FlotaRoja.addObservador(observador);

        List<String> notificaciones = new ArrayList<>();
        ObservadorInterfaz capturador = notificaciones::add;
        buque8.addObservador(capturador);
        FlotaRoja.addObservador(capturador);

        FlotaRoja.sendRepairRequest(buque8);

        assertEquals(1, notificaciones.size());
        assertEquals("El buque Sovremenny ha solicitado una reparación.", notificaciones.get(0));

        buque8.reparar();

        assertEquals(2, notificaciones.size());
        assertEquals("El buque Sovremenny ha sido reparado.", notificaciones.get(1));

        FlotaRoja.joinBattle(buque8);

        assertEquals(2, notificaciones.size());

        buque8.removeObservador(capturador);
        FlotaRoja.removeObservador(capturador);
    }
}
