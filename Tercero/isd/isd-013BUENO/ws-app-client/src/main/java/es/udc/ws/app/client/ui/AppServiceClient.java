package es.udc.ws.app.client.ui;

import es.udc.ws.app.client.service.ClientEncuestaService;
import es.udc.ws.app.client.service.ClientEncuestaServiceFactory;
import es.udc.ws.app.client.service.dto.ClientEncuestaDto;
import es.udc.ws.app.client.service.dto.ClientRespuestaDto;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaCanceladaException;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.time.LocalDateTime;
import java.util.List;

public class AppServiceClient
{
    public static void main(String[] args)
    {
        if(args.length == 0)
            printUsageAndExit();

        String command = args[0];

        ClientEncuestaService clientEncuestaService = ClientEncuestaServiceFactory.getService();
        if("-crearEncuesta".equals(command) || "-addsurvey".equals(command))
        {
            // FUNCIONALIDAD 1: CREAR ENCUESTA

            if (args.length != 3)
            {
                System.out.println("Error al intentar crear encuesta, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                String pregunta = args[1];
                LocalDateTime date = LocalDateTime.parse(args[2]);

                ClientEncuestaDto clientEncuestaDto = new ClientEncuestaDto(pregunta, date);
                ClientEncuestaDto encuesta = clientEncuestaService.crearEncuesta(clientEncuestaDto);

                System.out.println("Encuesta con id " + encuesta.getId() + " creada exitosamente");
            }
            catch (java.time.format.DateTimeParseException ex)
            {
                System.err.println("Error: El formato de la fecha es incorrecto.");
            }
            catch (InputValidationException ex)
            {
                System.err.println("Error: " + ex.getMessage());
            }
            catch (Exception ex)
            {
                ex.printStackTrace(System.err);
            }
        }

        else if("-buscarEncuestas".equals(command) || "-findSurveys".equals(command))
        {
            // FUNCIONALIDAD 2: BUSCAR POR PALABRA CLAVE
            if (args.length != 2)
            {
                System.out.println("Error al intentar buscar encuestas, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                String keyword = args[1];
                List<ClientEncuestaDto> encuestas = clientEncuestaService.buscarEncuestaPorPalabraClave(keyword);

                System.out.println("Encontradas " + encuestas.size() + " encuestas con la palabra clave '" + keyword + "':");
                for (ClientEncuestaDto encuesta : encuestas)
                    System.out.println(encuesta);

                return;
            }
            catch (Exception ex)
            {
                ex.printStackTrace(System.err);
            }
        }
        else if("-buscarEncuesta".equals(command) || "-findSurvey".equals(command))
        {
            // FUNCIONALIDAD 3: BUSCAR POR ID
            if (args.length != 2)
            {
                System.out.println("Error al intentar buscar encuesta, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                long encuestaId = Long.parseLong(args[1]);

                ClientEncuestaDto encuesta = clientEncuestaService.buscarEncuestaPorId(encuestaId);

                System.out.println("Encuesta encontrada: " + encuesta);
                printEncuesta(encuesta);

            }
            catch (NumberFormatException e)
            {
                System.err.println("Error: El ID debe ser un número.");
            }
            catch (InstanceNotFoundException e)
            {
                System.err.println("Error: No existe encuesta con id " + e.getInstanceId());
            }
            catch (Exception ex)
            {
                ex.printStackTrace(System.err);
            }
        }

        else if("-responder".equals(command) || "-answer".equals(command))
        {
            // FUNCIONALIDAD 4: RESPONDER ENCUESTA
            if (args.length != 4)
            {
                System.out.println("Error al intentar responder, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                long encuestaId = Long.parseLong(args[1]);
                String email = args[2];
                boolean voto = Boolean.parseBoolean(args[3]);

                ClientRespuestaDto respuesta = clientEncuestaService.responderEncuesta(encuestaId, email, voto);

                System.out.println("Encuesta " + encuestaId + " respondida correctamente. ID Respuesta: " + respuesta.getRespuestaId());

            }
            catch (NumberFormatException e)
            {
                System.err.println("Error: El ID debe ser numérico y el voto true/false.");
            }
            catch (InstanceNotFoundException e)
            {
                System.err.println("Error: No existe encuesta con id " + e.getInstanceId());
            }
            catch (InputValidationException e)
            {
                System.err.println("Error de validación: " + e.getMessage());
            }
            catch (es.udc.ws.app.client.service.exceptions.ClientEncuestaCanceladaException e)
            {
                System.err.println("Error: La encuesta está cancelada.");
            }
            catch (Exception ex)
            {
                ex.printStackTrace(System.err);
            }
        }
        else if("-cancelar".equals(command) || "-cancel".equals(command))
        {
            // FUNCIONALIDAD 5: CANCELAR ENCUESTA
            if (args.length != 2)
            {
                System.out.println("Error al intentar cancelar la encuesta, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                long encuestaId = Long.parseLong(args[1]);
                clientEncuestaService.cancelarEncuesta(encuestaId);
                System.out.println("Encuesta con id " + encuestaId + " cancelada exitosamente.");
            }
            catch (NumberFormatException e)
            {
                System.err.println("Error: El ID de la encuesta debe ser un número válido.");
            }
            catch (InstanceNotFoundException e)
            {
                System.err.println("Error: No se ha encontrado la encuesta con id " + e.getInstanceId());
            }
            catch (ClientEncuestaCanceladaException e)
            {
                System.err.println("Error: La encuesta con id " + e.getEncuestaId() + " ya ha sido cancelada previamente.");
            }
            catch (Exception e)
            {
                e.printStackTrace(System.err);
            }
        }
        else if("-buscarRespuestas".equals(command) || "-findAnswers".equals(command))
        {
            // FUNCIONALIDAD 6: BUSCAR RESPUESTAS
            // Argumentos esperados: <ID_Encuesta> [soloPositivas (true/false) - Opcional]

            if (args.length < 2)
            {
                System.out.println("Error al intentar buscar respuestas, revise los parámetros");
                printUsageAndExit();
            }

            try
            {
                long encuestaId = Long.parseLong(args[1]);
                boolean soloPositivas = false; // Por defecto mostramos todas

                if (args.length >= 3)
                    soloPositivas = Boolean.parseBoolean(args[2]);

                List<ClientRespuestaDto> respuestas = clientEncuestaService.buscarRespuestasEncuesta(encuestaId, soloPositivas);

            }
            catch (NumberFormatException e)
            {
                System.err.println("Error: El ID de la encuesta debe ser un número entero válido.");
            }
            catch (InstanceNotFoundException e)
            {
                System.err.println("Error: No se ha encontrado la encuesta con id " + e.getInstanceId());
            }
            catch (InputValidationException e)
            {
                System.err.println("Error de validación: " + e.getMessage());
            }
            catch (Exception ex)
            {
                ex.printStackTrace(System.err);
            }
        }
        else
        {
            System.out.println("No se ha encontrado el comando");
            printUsageAndExit();
        }
    }

    public static void printEncuesta(ClientEncuestaDto encuesta)
    {
        System.out.println("Encuesta: " + encuesta.getId() + '\r');
        System.out.println("Pregunta: " + encuesta.getPregunta() + '\r');
        System.out.println("Fecha fin: " + encuesta.getFechaFin() + '\r');
        System.out.println("Estado: " + (encuesta.isCancelada() ? "Cancelada" : "Activa") + '\r');
        System.out.println("Respuestas positivas" + encuesta.getRepuestasPositivas() + '\r');
        System.out.println("Respuestas totales: " + encuesta.getRespuestasTotales() + '\r');
    }

    public static void printUsageAndExit()
    {
        printUsage();
        System.exit(-1);
    }

    public static void printUsage()
    {
        System.err.println("Usage:\n" +
                "    [crear]                -crearEncuesta <pregunta> <fecha>\n" +
                "    [buscar por keyword]   -buscarEncuestas <keyword>\n" +
                "    [buscar por id]        -buscarEncuesta <ID>\n" +
                "    [responder]            -responder <>\n" +
                "    [cancelar]             -cancelar <ID>\n" +
                "    [buscar respuestas]    -buscarRespuestas <ID> <Solo positivas (opcional)>\n");
    }
}
