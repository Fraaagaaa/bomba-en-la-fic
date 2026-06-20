package es.udc.ws.app.restservice.json;

import com.fasterxml.jackson.databind.node.JsonNodeFactory;
import com.fasterxml.jackson.databind.node.ObjectNode;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaCanceladaException;
import es.udc.ws.app.model.encuestaservice.exceptions.EncuestaFinalizadaException;

public class AppExceptionToJsonConversor {

    public static ObjectNode toEncuestaFinalizadaException(EncuestaFinalizadaException ex) {

        ObjectNode exceptionObject = JsonNodeFactory.instance.objectNode();

        exceptionObject.put("errorType", "EncuestaFinalizada");
        exceptionObject.put("encuestaId", ex.getEncuestaId());
        if (ex.getFechaFin() != null) {
            exceptionObject.put("fechaFin", ex.getFechaFin().toString());
        } else {
            exceptionObject.putNull("fechaFin");
        }

        return exceptionObject;
    }

    public static ObjectNode toEncuestaCanceladaException(EncuestaCanceladaException ex) {

        ObjectNode exceptionObject = JsonNodeFactory.instance.objectNode();

        exceptionObject.put("errorType", "EncuestaCancelada");
        exceptionObject.put("encuestaId", ex.getEncuestaId());

        return exceptionObject;
    }
}
