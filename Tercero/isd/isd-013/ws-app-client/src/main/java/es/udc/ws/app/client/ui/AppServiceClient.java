package es.udc.ws.app.client.ui;

import es.udc.ws.app.client.service.ClientEncuestaService;
import es.udc.ws.app.client.service.ClientEncuestaServiceFactory;
import es.udc.ws.app.client.service.dto.ClientEncuestaDto;
import es.udc.ws.app.client.service.dto.ClientRespuestaDto;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaCanceladaException;
import es.udc.ws.app.client.service.exceptions.ClientEncuestaExpirationException;
import es.udc.ws.util.exceptions.InputValidationException;
import es.udc.ws.util.exceptions.InstanceNotFoundException;

import java.time.LocalDateTime;
import java.util.List;

public class AppServiceClient
{
    public static void main(String[] args)
    {
        if(args.length == 0)
        {
            System.err.println("No hay argumentos");
            printUsageAndExit();
        }

        String command = args[0];

        ClientEncuestaService clientEncuestaService = ClientEncuestaServiceFactory.getService();
        if("-crearEncuesta".equals(command) || "-addSurvey".equals(command))
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
                System.out.println(encuesta);
            }
            catch (java.time.format.DateTimeParseException ex)
            {
                ex.printStackTrace();
                System.err.println("Error: El formato de la fecha es incorrecto.");
            }
            catch (Exception ex)
            {
                ex.printStackTrace();
                System.err.println("Error: " + ex.getMessage());
            }
        }

        else if("-buscarEncuestas".equals(command) || "-findSurveys".equals(command))
        {
            // FUNCIONALIDAD 2: BUSCAR POR PALABRA CLAVE
            try
            {
                String keyword;
                if(args.length == 1)
                    keyword = "";
                else
                    keyword = args[1];

                List<ClientEncuestaDto> encuestas = clientEncuestaService.buscarEncuestaPorPalabraClave(keyword);

                System.out.println("Encontradas " + encuestas.size() + " encuestas con la palabra clave '" + keyword + "':");
                for (ClientEncuestaDto encuesta : encuestas)
                    System.out.println(encuesta);
            }
            catch (Exception ex)
            {
                ex.printStackTrace();
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
            }
            catch (NumberFormatException e)
            {
                e.printStackTrace();
                System.err.println("Error: El ID debe ser un número.");
            }
            catch (InstanceNotFoundException e)
            {
                e.printStackTrace();
                System.err.println("Error: No existe encuesta con id " + e.getInstanceId());
            }
            catch (Exception ex)
            {
                ex.printStackTrace();
                System.err.println("Error: " + ex.getMessage());
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
                System.out.println(respuesta);

            }
            catch (NumberFormatException e)
            {
                e.printStackTrace();
                System.err.println("Error: El ID debe ser numérico y el voto true/false.");
            }
            catch (InstanceNotFoundException e)
            {
                e.printStackTrace();
                System.err.println("Error: No existe encuesta con id " + e.getInstanceId());
            }
            catch (InputValidationException e)
            {
                e.printStackTrace();
                System.err.println("Error de validación: " + e.getMessage());
            }
            catch (ClientEncuestaCanceladaException e)
            {
                System.err.println("Error: La encuesta está cancelada.");
            }
            catch (ClientEncuestaExpirationException e)
            {
                e.printStackTrace();
                System.err.println("Error: La encuesta ya ha finalizado");
            }
            catch (Exception ex)
            {
                ex.printStackTrace();
                System.err.println("Error: " + ex.getMessage());
            }
        }

        else if("-cancelar".equals(command) || "-cancel".equals(command))
        {

            // FUNCIONALIDAD 5: CANCELAR ENCUESTA
            validateArgs(args, 2, new int[]{1});

            try
            {
                long encuestaId = Long.parseLong(args[1]);
                clientEncuestaService.cancelarEncuesta(encuestaId);
                System.out.println("Encuesta con id " + encuestaId + " cancelada exitosamente.");
            }
            catch (NumberFormatException e)
            {
                e.printStackTrace();
                System.err.println("Error: El ID debe ser un número válido.");
            }
            catch (InstanceNotFoundException e)
            {
                e.printStackTrace();
                System.err.println("Error: No existe encuesta con id " + e.getInstanceId());
            }
            catch (ClientEncuestaCanceladaException e)
            {
                e.printStackTrace();
                System.err.println("Error: La encuesta " + e.getEncuestaId() + " ya estaba cancelada.");
            }
            catch (Exception e)
            {
                e.printStackTrace();
                System.err.println("Error al intentar buscar encuesta. " +  e.getMessage());
            }
        }

        else if ("-buscarRespuestas".equals(command) || "-findAnswers".equals(command))
        {
            // FUNCIONALIDAD 6: BUSCAR RESPUESTAS

            try
            {
                long encuestaId = Long.parseLong(args[1]);

                boolean soloPositivas = false;

                if (args.length >= 3)
                    soloPositivas = Boolean.parseBoolean(args[2]); 

                List<ClientRespuestaDto> respuestas = clientEncuestaService.buscarRespuestasEncuesta(encuestaId, soloPositivas);

                for (ClientRespuestaDto respuesta : respuestas) System.out.println("Respuestas: " + respuesta);
            }
            catch (NumberFormatException e)
            {
                e.printStackTrace();
                System.err.println("Error: El ID de la encuesta y/o el filtro booleano deben ser válidos.");
            }
            catch (InputValidationException e)
            {
                e.printStackTrace();
                System.err.println("Error de validación: " + e.getMessage());
            }
            catch (Exception e)
            {
                e.printStackTrace();
                System.err.println("Se ha producido un error: " + e.getMessage());
            }
        }

        else
        {
            System.out.println("Comando no encontrado");
            printUsageAndExit();
        }
    }

    public static void printUsageAndExit()
    {
        printUsage();
        System.exit(-1);
    }

    public static void validateArgs(String[] args, int expectedArgs,
            int[] numericArguments) {
        if (expectedArgs != args.length) {
            printUsageAndExit();
        }
        for (int position : numericArguments) {
            try {
                Double.parseDouble(args[position]);
            } catch (NumberFormatException n) {
                printUsageAndExit();
            }
        }
    }

    public static void printUsage()
    {
        System.err.println("Usage:\n" +
                "    [crear]                -crearEncuesta <pregunta> <fecha>\n" +
                "    [buscar por keyword]   -buscarEncuestas <keyword>\n" +
                "    [buscar por id]        -buscarEncuesta <ID>\n" +
                "    [responder]            -responder <ID> <email> <voto>\n" +
                "    [cancelar]             -cancelar <ID>\n" +
                "    [buscar respuestas]    -buscarRespuestas <ID>\n");
    }
}
