/*
 * Group 4.3 - SO 25-26
 *
 * Authors:
 * - Miguel Fraga Pico
 *
 * Logins:
 * - miguel.fraga.pico
 */

#include "p0.h"

int main()
{
    List history;
    List opened_files;
    char command[MAX_COMMAND_LENGHT];

    list_init(&history);
    list_init(&opened_files);

    while(true)
    {
        prompt();
        read_input(command);
        handle_input(command, &history, &opened_files);
    }

    return 0;
}

void read_input(char *input)
{
    fgets(input, MAX_COMMAND_LENGHT, stdin);
}

void prompt()
{
    char hostname[256];
    char *cwd = getcwd(NULL, 0);
    char *user = getenv("USER");

    gethostname(hostname, sizeof(hostname));
    char *token = strtok(cwd, "/");

    while (token != NULL)
    {
        cwd = token;
        token = strtok(NULL, "/");
    }

    printf("%s@%s -> %s ", hostname, user, cwd);
}

int TrocearCadena(char * cadena, char * trozos[])
{ 
    int i=1;

    if ((trozos[0]=strtok(cadena," \n\t"))==NULL) return 0;

    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) i++;

    return i;
}

void handle_input(char *command, List *history, List *opened_files)
{
    char *args[64];
    char *original_command = strdup(command);

    remove_endline(command);
    TrocearCadena(command, args);
    if(args[0] == NULL) return;

    if(strcmp(args[0], "authors") == 0) cmd_authors(args); // -n -l
    else if(strcmp(args[0], "getpid") == 0) cmd_getpid(args); // -p
    else if(strcmp(args[0], "chdir") == 0) cmd_chdir(args);
    else if(strcmp(args[0], "getcwd") == 0) cmd_getcwd(args);
    else if(strcmp(args[0], "date") == 0) cmd_date(args); // -t -d
    else if(strcmp(args[0], "hours") == 0) cmd_hours(args);
    else if(strcmp(args[0], "open") == 0) cmd_open(args, opened_files);
    else if(strcmp(args[0], "close") == 0) cmd_close(args, opened_files);
    else if(strcmp(args[0], "dup") == 0) cmd_dup(args, opened_files);
    else if(strcmp(args[0], "listopen") == 0) cmd_listopen(opened_files);
    else if(strcmp(args[0], "infosys") == 0) cmd_infosys(args);
    else if(strcmp(args[0], "help") == 0) return; // cmd_help(args);
    else if(strcmp(args[0], "historic") == 0)
    {
        add_command_to_history(original_command, history);
        cmd_historic(args, history); // N -N -clear -count
    }
    else if(strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0 || strcmp(args[0], "bye") == 0)
    {
        list_clear(history);
        list_clear(opened_files);
        exit(0);
    }
    else cmd_unknown(args);

    if(strcmp(args[0], "historic") != 0)  add_command_to_history(original_command, history);
    else free(original_command);
}

void add_command_to_history(char *command, List *history)
{
    list_insert(history, command);
}

void cmd_authors(char **args)
{
    if(args[1] == NULL)
    {
        printf("Authors: Miguel Fraga Pico\n");
        printf("Login: miguel.fraga.pico\n");
        return;
    }
    if(strcmp(args[1], "-n") == 0) printf("Authors: Miguel Fraga Pico\n");
    if(strcmp(args[1], "-l") == 0) printf("Login: miguel.fraga.pico\n");
}

void cmd_getpid(char **args)
{
    if(args[1] == NULL) printf("Shell's process PID: %d\n", getpid());
    else if(strcmp(args[1], "-p") == 0) printf("Shell's parent PID: %d\n", getppid());
}

void cmd_chdir(char **args)
{
    char *cwd = getcwd(NULL, 0);
    if(args[1]==NULL) printf("%s\n", cwd);
    else if(chdir(args[1])!=0) perror("Unable to change directory");
}

void cmd_getcwd(char **args)
{
    char *cwd = getcwd(NULL, 0);
    if(cwd != NULL)
    {
        printf("Directory: %s\n", cwd);
        free(cwd);
    }
    else
    {
        perror("getcwd");
    }
}

void cmd_date(char **args)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    if(args[1] == NULL)
    {
        printf("%02d/%02d/%04d %02d:%02d:%02d\n",
                tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    }
    else if(strcmp(args[1], "-d") == 0)
    {
        printf("%02d/%02d/%02d\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    }
    else if(strcmp(args[1], "-t") == 0)
    {
        printf("%02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    }
}

void cmd_hours(char **args)
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    printf("%02d:%02d:%02d\n", tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
}

void cmd_unknown(char **args)
{
    printf("Unknown command '%s', do 'help' for a command list.\n", args[0]);
}

void cmd_historic(char **args, List *history)
{
    int i = 0;
    char *command;
    if(args[1] == NULL)
    {
        for(ListPos p = list_first(*history); !list_end(p); p = list_next(p))
        {
            command = list_get(p);
            printf("%d: %s", i, command);
            i++;
        }
        return;
    }
    if(strcmp(args[1], "-clear") == 0)
    {
        list_clear(history);
        // list_init(history);
        return;
    }
    if(strcmp(args[1], "-count") == 0)
    {
        printf("Historic contains %d commands\n", list_length(*history));
        // Se cuenta a si mismo
        return;
    }
    int index;
    sscanf(args[1], "%d", &index);
    int total = list_length(*history);
    ListPos p = list_first(*history);

    if(index < 0)
    {
        int n = -index;

        for(i = 0; i < total - n; i++)
            p = list_next(p);

        while(!list_end(p))
        {
            command = list_get(p);
            printf("%d: %s", i, command);
            p = list_next(p);
            i++;
        }
    }
    else
    {
        for(i = 0; i < index; i++)
            p = list_next(p);
        command = list_get(p);
        printf("%d: %s", i, command);

    }
}

void cmd_infosys(char **args)
{
    struct utsname info;
    if (uname(&info) != 0)  perror("uname");
    else printf("%s@%s %s, OS: %s-%s-%s\n", info.sysname, info.nodename, info.machine, info.sysname, info.release, info.version);
}

void remove_endline(char *string)
{
    char *pos;
    if((pos = strchr(string, '\n')) != NULL)
        *pos = '\0';
}

void list_opened_files(List *opened_files)
{
    ListPos pos = list_first(*opened_files);
    printf("Files opened:\n");
    while(!list_end(pos))
    {
        char mode_string[64];
        FileEntry *entry = list_get(pos);
        int mode = fcntl(entry->fd, F_GETFL);

        mode &= O_ACCMODE;
        switch(mode)
        {
            case O_RDONLY: strcpy(mode_string, "O_RDONLY"); break;
            case O_RDWR: strcpy(mode_string, "O_RDWR"); break;
            case O_EXCL: strcpy(mode_string, "O_EXCL"); break;
            case O_CREAT: strcpy(mode_string, "O_CREAT"); break;
            case O_TRUNC: strcpy(mode_string, "O_TRUNC"); break;
            case O_APPEND: strcpy(mode_string, "O_APPEND"); break;
            case O_WRONLY: strcpy(mode_string, "O_WRONLY"); break;
            default: strcpy(mode_string, ""); break;
        }
        printf("Descriptor: %d, Name: %s, Mode: %s\n", entry->fd, entry->filename, mode_string);
        pos = list_next(pos);
    }
}

void cmd_open(char* args[], List *opened_files)
{
    int i, mode = 0, fd;
    if (args[1] == NULL)
    {
        cmd_listopen(opened_files);
        return;
    }
    for(i = 2; args[i] != NULL; i++)
    {
        if (!strcmp(args[i], "cr")) mode |= O_CREAT;
        else if (!strcmp(args[i], "ex")) mode |= O_EXCL;
        else if (!strcmp(args[i], "ro")) mode |= O_RDONLY;
        else if (!strcmp(args[i], "wo")) mode |= O_WRONLY;
        else if (!strcmp(args[i], "rw")) mode |= O_RDWR;
        else if (!strcmp(args[i], "ap")) mode |= O_APPEND;
        else if (!strcmp(args[i], "tr")) mode |= O_TRUNC;
        else break;
    }
    fd = open(args[1], mode, 0777);
    if(fd == -1)
    { 
        perror("Unable to open file: ");
        return;
    }

    FileEntry *f = malloc(sizeof(FileEntry));
    f->fd = fd;
    strncpy(f->filename, args[1], 255);
    f->filename[255] = '\0';
    f->mode = mode;

    list_insert(opened_files, f);
    printf("File '%s' opened with fd %d and mode %x\n", f->filename, f->fd, f->mode);
}

void cmd_listopen(List *opened_files)
{
    ListPos p = list_first(*opened_files);
    while(!list_end(p))
    {
        FileEntry* f = (FileEntry*)list_get(p);
        printf("fd: %d\t%s\n", f->fd, f->filename);
        p = list_next(p);
    }
}

void cmd_close(char *args[], List *opened_files)
{ 
    int fd;
    if(args[1] != NULL) 
        fd = atoi(args[1]);

    if (args[1]==NULL || fd < 0)
    {
        list_opened_files(opened_files);
        return;
    }

    if(close(fd) == -1)
    {
        perror("Unable to identify file descriptor");
        return;
    }
    else
    {
        remove_file(fd, opened_files);
        printf("Descriptor %d closed\n", fd);
    }
}

void remove_file(int fd, List *opened_files)
{
    List pos;
    for(pos = list_first(*opened_files); !list_end(pos); pos = list_next(pos))
    {
        FileEntry *file = list_get(pos);
        if(file->fd == fd)
        {
            list_remove(opened_files, pos);
            printf("Removed fd=%d, name=%s", file->fd, file->filename);
            free(file);
            break;
        }
    }
}

void cmd_dup(char *args[], List *opened_files)
{
    int fd, duplicado;
    FileEntry *origFile = NULL;

    if (args[1] == NULL || (fd = atoi(args[1])) < 0)
    {
        cmd_listopen(opened_files);
        return;
    }

    ListPos pos = list_first(*opened_files);
    while (pos != NULL)
    {
        FileEntry *f = list_get(pos);
        if (f->fd == fd)
        {
            origFile = f;
            break;
        }
        pos = list_next(pos);
    }

    if (origFile == NULL)
    {
        fprintf(stderr, "File descriptor %d not found in file list\n", fd);
        return;
    }

    duplicado = dup(fd);
    if (duplicado == -1)
    {
        perror("Unable to duplicate file descriptor");
        return;
    }

    FileEntry *dupFile = malloc(sizeof(FileEntry));
    if (!dupFile)
    {
        perror("malloc");
        close(duplicado);
        return;
    }

    dupFile->fd = duplicado;
    strncpy(dupFile->filename, origFile->filename, sizeof(dupFile->filename));
    dupFile->filename[sizeof(dupFile->filename) - 1] = '\0';
    dupFile->mode = fcntl(duplicado, F_GETFL);

    if (!list_insert(opened_files, dupFile))
    {
        perror("Unable to add duplicated file into file list");
        close(duplicado);
        free(dupFile);
        return;
    }

    printf("File '%s' duplicated: original fd=%d, new fd=%d, mode=%x\n", dupFile->filename, fd, dupFile->fd, dupFile->mode);
}
