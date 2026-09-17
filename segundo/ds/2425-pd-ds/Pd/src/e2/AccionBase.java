package e2;

public record AccionBase(String nomeAccion, int feche, int maximo, int minimo, int volume) {

    @Override
    public String nomeAccion() {
        if (nomeAccion == null || nomeAccion.length() > 4) {
            throw new IllegalArgumentException("O nome da accion ten un erro.");
        }
        return nomeAccion;
    }
}