/*
 * Group 4.3 - SO 25-26
 *
 * Author:
 * - Miguel Fraga Pico
 *
 * Login:
 * - miguel.fraga.pico
 */

#include "p1.h"
#include "commandsp0.h"
#include "commandsp1.h"

int main()
{
    List history;
    List opened_files;
    struct DirParams dirparams;
    char command[MAX_COMMAND_LENGHT];


    list_init(&history);
    list_init(&opened_files);
    init_standard_fds(&opened_files);
    init_params(&dirparams);

    while(true)
    {
        prompt();
        read_input(command);
        handle_input(command, &history, &opened_files, &dirparams);
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

    if (cwd == NULL) return;

    gethostname(hostname, sizeof(hostname));

    char *last_dir = strrchr(cwd, '/');
    if (last_dir) last_dir++;
    else last_dir = cwd;

    printf("%s@%s{%s} -> ", hostname, user, last_dir);
    free(cwd);
}

int getArguments(char * cadena, char * trozos[])
{ 
    int i=1;

    if ((trozos[0]=strtok(cadena," \n\t"))==NULL) return 0;

    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) i++;

    return i;
}

void handle_input(char *command, List *history, List *opened_files, struct DirParams *params  )
{
    char *args[64];
    char *original_command = strdup(command); // este strdup da problemas

    remove_endline(command);
    getArguments(command, args);
    if(args[0] == NULL) { free(original_command); return; }
    add_command_to_history(original_command, history);  

    if(!strcmp(args[0], "authors")) cmd_authors(args); // -n -l
    else if(!strcmp(args[0], "getpid")) cmd_getpid(args); // -p
    else if(!strcmp(args[0], "chdir")) cmd_chdir(args);
    else if(!strcmp(args[0], "getcwd")) cmd_getcwd(args);
    else if(!strcmp(args[0], "date")) cmd_date(args); // -t -d
    else if(!strcmp(args[0], "hour")) cmd_hour(args);
    else if(!strcmp(args[0], "open")) cmd_open(args, opened_files);
    else if(!strcmp(args[0], "close")) cmd_close(args, opened_files);
    else if(!strcmp(args[0], "dup")) cmd_dup(args, opened_files);
    else if(!strcmp(args[0], "help")) cmd_help(args);
    else if(!strcmp(args[0], "historic")) cmd_historic(args, history);
    else if(!strcmp(args[0], "exit") || !strcmp(args[0], "quit") || !strcmp(args[0], "bye"))
    {
        list_clear(history);
        list_clear(opened_files);
        exit(0);
    }
    else if(!strcmp(args[0], "create")) cmd_create(args);
    else if(!strcmp(args[0], "setdirparams"))cmd_setdirparams(args, params);
    else if(!strcmp(args[0], "getdirparams"))cmd_getdirparams(args, params);
    else if(!strcmp(args[0], "erase")) cmd_erase(args);
    else if(!strcmp(args[0], "delrec")) cmd_delrec(args);
    else if(!strcmp(args[0], "lseek")) cmd_lseek(args, opened_files);
    else if(!strcmp(args[0], "writestr")) cmd_writestr(args, opened_files);
    else if(!strcmp(args[0], "dir")) cmd_dir(args, params);
    else cmd_unknown(args);
}

void remove_endline(char *string)
{
    char *pos;
    if((pos = strchr(string, '\n')) != NULL)
        *pos = '\0';
}
