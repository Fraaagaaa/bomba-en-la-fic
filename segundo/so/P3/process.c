#include "process.h"

void anadirProceso(pid_t pid, char *command_line, List *processList) {
    process *new_process = malloc(sizeof(struct process));
    if (new_process == NULL) {
        perror("Error al agregar proceso a la lista");
        return;
    }
    new_process->pid = pid;
    new_process->date = time(NULL);
    new_process->state = ACTIVE;
    new_process->commandLine = strdup(command_line);
    new_process->priority = 0;

    list_insert(processList, new_process);
}

void printProcessList(List *processList) {
    ListPos pos;
    process *proceso;

    printf("DATE --- PID  --- STATUS --- PRIORITY --- COMMAND LINE\n");
    int i = 0;

    for (pos = list_first(*processList); pos != NULL; pos = list_next(pos)) {
        i++;
        // PID --- HORA --- STATUS --- PRIORIDAD --- COMMAND LINE
        proceso = list_get(pos);

        char fecha[26];
        struct tm *tm_info = localtime(&proceso->date);
        strftime(fecha, 26, "%H:%M:%S", tm_info);

        char *state = proccessToString(proceso->state);
        printf("%s  %d\t%s\t%5d\t%10s\n", fecha, proceso->pid, state,
                proceso->priority, proceso->commandLine);
    }
    if (i == 0)
        printf("La lista está vacía\n");
}

char *proccessToString(PROCESSSTATUS status) {
    switch (status) {
        case FINISHED:
            return "Finished";
        case STOPPED:
            return "Stopped";
        case SIGNALED:
            return "Signaled";
        case ACTIVE:
            return "Active";
    }
    return "UNKNOWN";
}

process *getProcessByPID(List *processList, pid_t pid) {
    ListPos pos;
    process *proceso;
    for (pos = list_first(*processList); pos != NULL; pos = list_next(pos)) {
        proceso = list_get(pos);
        if (proceso->pid == pid)
            return proceso;
    }
    return NULL;
}

void deleteProcessBySignal(List *processList, int target_state) {
    ListPos pos;
    process *proceso;
    ListPos next_pos;

    for (pos = list_first(*processList); pos != NULL; pos = next_pos) {
        next_pos = list_next(pos);
        proceso = list_get(pos);

        if (proceso->state == target_state) {
            printf("Proceso %d eliminado \n", proceso->pid);
            free(proceso->commandLine);
            free(proceso);

            list_remove(processList, pos);
        }
    }
}

void freeProcessList(List *processList)
{
    ListPos pos;
    process *proceso;
    ListPos next_pos;

    for (pos = list_first(*processList); pos != NULL; pos = next_pos)
    {
        next_pos = list_next(pos);
        proceso = list_get(pos);

        free(proceso->commandLine);
        free(proceso);

        list_remove(processList, pos);
    }
}

process *create_process(pid_t pid, char *command_line, int priority) {
    process *p = (process *)malloc(sizeof(process));
    if (p == NULL) {
        perror("Error en malloc para proceso");
        return NULL;
    }

    p->pid = pid;
    p->date = time(NULL);
    p->state = ACTIVE;
    p->commandLine = strdup(command_line);
    p->returnSignal = 0;
    p->priority = priority;

    if (p->commandLine == NULL) {
        perror("Error en strdup para commandLine");
        free(p);
        return NULL;
    }

    return p;
}

int getPriority(char **args) {
    int i;
    for (i = 0; args[i] != NULL; i++)
        if (args[i][0] == '@')
            return atoi(args[i] + 1);

    return -1;
}

bool getBackground(char **args) {
    int i;
    for (i = 0; args[i] != NULL; i++)
        if (args[i][0] == '&')
            return true;

    return false;
}

char **removeBackgroundAndPriority(char **args)
{
    int i, j = 0;
    int count = 0;
    
    for(count = 0; args[count] != NULL; count++);

    char **newArgs = malloc((count + 1) * sizeof(char *)); 

    if (newArgs == NULL)
        return NULL;

    for(i = 0; args[i] != NULL; i++)
    {
        if(args[i][0] != '&' && args[i][0] != '@')
        {
            newArgs[j] = args[i];
            j++;
        }
    }
     
    newArgs[j] = NULL; 
    
    return newArgs;
}

struct SEN sigstrnum[] = {
    {"HUP", SIGHUP},
    {"INT", SIGINT},
    {"QUIT", SIGQUIT},
    {"ILL", SIGILL},
    {"TRAP", SIGTRAP},
    {"ABRT", SIGABRT},
    {"IOT", SIGIOT},
    {"BUS", SIGBUS},
    {"FPE", SIGFPE},
    {"KILL", SIGKILL},
    {"USR1", SIGUSR1},
    {"SEGV", SIGSEGV},
    {"USR2", SIGUSR2},
    {"PIPE", SIGPIPE},
    {"ALRM", SIGALRM},
    {"TERM", SIGTERM},
    {"CHLD", SIGCHLD},
    {"CONT", SIGCONT},
    {"STOP", SIGSTOP},
    {"TSTP", SIGTSTP},
    {"TTIN", SIGTTIN},
    {"TTOU", SIGTTOU},
    {"URG", SIGURG},
    {"XCPU", SIGXCPU},
    {"XFSZ", SIGXFSZ},
    {"VTALRM", SIGVTALRM},
    {"PROF", SIGPROF},
    {"WINCH", SIGWINCH},
    {"IO", SIGIO},
    {"SYS", SIGSYS},
#ifdef SIGPOLL
    {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
    {"PWR", SIGPWR},
#endif
#ifdef SIGINFO
#endif
    {NULL, -1}};

int ValorSenal(char *sen) /*devuelve el numero de senial a partir del nombre*/
{
    int i;
    for (i = 0; sigstrnum[i].nombre != NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}

char *NombreSenal(int sen) /*devuelve el nombre senal a partir de la senal*/
{                          /* para sitios donde no hay sig2str*/
    int i;
    for (i = 0; sigstrnum[i].nombre != NULL; i++)
        if (sen == sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}

void updateProcessStatus(List *processList) {
    ListPos pos;
    process *proceso;
    pid_t status_pid;
    int status;

    for (pos = list_first(*processList); pos != NULL; pos = list_next(pos)) {
        proceso = list_get(pos);

        if (proceso->state != ACTIVE)
            continue;

        status_pid = waitpid(proceso->pid, &status, WNOHANG | WUNTRACED);

        if (status_pid == proceso->pid) {
            if (WIFEXITED(status)) {
                proceso->state = FINISHED;
                proceso->returnSignal = WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                proceso->state = SIGNALED;
                proceso->returnSignal = WTERMSIG(status);
            } else if (WIFSTOPPED(status)) {
                proceso->state = STOPPED;
            } else if (WIFCONTINUED(status)) {
                proceso->state = ACTIVE;
            }
        }
    }
}
