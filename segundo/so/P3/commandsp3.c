#include "commandsp3.h"
#include "process.h"

extern char **environ;

void getUid(char **args)
{
    printf("UID Real: %d\n", getuid());
    printf("UID Efectivo: %d\n", geteuid());
}

void setUid(char **args)
{
    uid_t target_uid;
    char *endptr;
    long id_long = strtol(args[2], &endptr, 10);

    if (*endptr != '\0' || id_long < 0)
    {
        fprintf(stderr, "Error: '%s' no es un UID numérico válido.\n", args[2]);
        return;
    }
    target_uid = (uid_t)id_long;

    if (seteuid(target_uid) == -1)
        perror("Error al cambiar el UID efectivo (seteuid)");
    else
        printf("UID efectivo cambiado con éxito. Nuevo UID: %d\n", geteuid());
}

void setUidLogIn(char **args)
{
    struct passwd *p = getpwnam(args[3]);
    if (p == NULL)
    {
        fprintf(stderr, "Error: Usuario '%s' no encontrado.\n", args[3]);
        return;
    }

    if (seteuid(p->pw_uid) == -1)
        perror("Error al cambiar el UID efectivo (seteuid)");
    else
        printf("UID efectivo cambiado con éxito. Nuevo UID: %d\n", geteuid());
}

void cmd_uid(char **args)
{
    if (args[1] == NULL)
    {
        printf("Uso incorrecto de uid\n");
        return;
    }
    
    if (!strcmp(args[1], "-get"))
    {
        getUid(args);
        return;
    }

    if (!strcmp(args[1], "-set"))
    {
        if(args[2] == NULL)
        {
            printf("Uso incorrecto de uid (falta el ID o el modificador -l)\n");
            return;
        }

        if(!strcmp(args[2], "-l"))
        {
            if(args[3] == NULL)
            {
                printf("Uso incorrecto de uid (falta el nombre de usuario)\n");
                return;
            }
            else
            {
                setUidLogIn(args);
                return;
            }
        }
        setUid(args);
        return;
    }
}
void cmd_envvar(char **args, char **envp)
{
    if(args[1] == NULL)
    {
        cmd_showenv(args, envp);
        return;
    }

    if(!strcmp(args[1], "-change"))
    {
        if(args[2] == NULL || args[3] == NULL || args[4] == NULL)
        {
            printf("Wrong use of envvar\n");
            return;
        }

        if(!strcmp(args[2], "-a"))
        {
            CambiarVariable(args[3], args[4], envp);
        }
        else if(!strcmp(args[2], "-e"))
        {
            CambiarVariable(args[3], args[4], environ);
        }
        else if(!strcmp(args[2], "-p"))
        {
            char *str = malloc(strlen(args[3]) + strlen(args[4]) + 2); // Los dos bytes extras son para el = y para el \0
            if (str == NULL)
            {
                perror("malloc");
                return;
            }
            sprintf(str, "%s=%s", args[3], args[4]);
            if(putenv(str) != 0)
            {
                perror("putenv");
                free(str);
            }
        }
    }
    else if(!strcmp(args[1], "-show"))
    {
        if(args[2] == NULL)
        {
             printf("Wrong use of envvar -show\n");
             return;
        }
        int pos;
        char *val;

        pos = BuscarVariable(args[2], envp);
        if(pos != -1)
            printf("with arg3 main: %s (%p)\n", envp[pos], envp[pos]);
        else
            printf("with arg3 main: not found\n");

        pos = BuscarVariable(args[2], environ);
        if(pos != -1)
            printf("with environ: %s (%p)\n", environ[pos], environ[pos]);
        else
            printf("with environ: not found\n");

        val = getenv(args[2]);
        if(val != NULL)
            printf("with getenv: %s (%p)\n", val, val);
        else
            printf("with getenv: not found\n");
    }
    else
    {
         printf("Wrong use of envvar\n");
    }
}

void cmd_showenv(char **args, char **envp)
{
    if(args[1] == NULL)
    {
        char **envp_aux = envp;
        while(*envp_aux != NULL)
        {
            printf("%p->main arg3[%ld]=(%p) %s\n", &envp_aux[0], envp_aux-envp, envp_aux[0], *envp_aux);
            envp_aux++;
        }
        return;
    }

    if(!strcmp(args[1], "-environ"))
    {
        int i = 0;
        while(environ[i] != NULL)
        {
            printf("%p->environ[%d]=(%p) %s\n", &environ[i], i, environ[i], environ[i]);
            i++;
        }
        return;
    }

    if(!strcmp(args[1], "-addr"))
    {
        printf("environ:   %p (almacenado en %p)\n", environ, &environ);
        printf("main arg3: %p (almacenado en %p)\n", envp, &envp);
        return;
    }
}

void cmd_fork(char **args)
{
    Cmd_fork(args);
}

void cmd_exec(char **args)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of exec\n");
        return;
    }
    
    int priority = getPriority(args);
    char **comando = removeBackgroundAndPriority(args);
    
    if(priority > 0)
        if(setpriority(PRIO_PROCESS, 0, priority) == -1)
            perror("setpriority");

    if (execvp(comando[1], &comando[1]) == -1)
        perror("execvp");
}


void cmd_jobs(List *processList)
{
    updateProcessStatus(processList);
    printProcessList(processList);
}

void cmd_deljobs(char **args, List *processList)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of deljobs\n");
        return;
    }

    if(!strcmp(args[1], "-term"))
        deleteProcessBySignal(processList, FINISHED);
    else if(!strcmp(args[1], "-sig"))
        deleteProcessBySignal(processList, SIGNALED);
    else
        printf("Wrong use of deljobs\n");
}

void cmd_execute_external(char **args, List *processList)
{
    int priority = getPriority(args);
    bool background = getBackground(args);

    char **comando = removeBackgroundAndPriority(args);
    
    pid_t pid = fork();

    if (pid == 0)
    {
        // Hijo
        if (priority != -1)
            if (setpriority(PRIO_PROCESS, 0, priority) == -1)
                perror("setpriority");

        if (execvp(comando[0], comando) == -1)
        {
            perror("execvp");
            exit(255);
        }
        return;
    }
    if (pid > 0)
    {
        // Padre
        if (background)
        {
            char cmdLine[256] = "";
            for (int j=0; comando[j]!=NULL; j++)
                strcat(cmdLine, comando[j]);

            anadirProceso(pid, cmdLine, processList);
        }
        else
        {
            // si se lanza en foreground esperamos a que acabe
            waitpid(pid, NULL, 0);
        }
        free(comando);
        return;
    }
    perror("fork");
}
