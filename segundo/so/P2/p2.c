/*
 * Group 4.3 - SO 25-26
 *
 * Author:
 * - Miguel Fraga Pico
 *
 * Login:
 * - miguel.fraga.pico
 */

#include "p2.h"


int var_ext_no_ini; 
int var_ext_no_ini_2; 
int var_ext_no_ini_3; 

int var_glob = 1;
int var_glob_2 = 1;
int var_glob_3 = 1;
int var_glob_no_inicializada;

int main()
{
    List history;
    List opened_files;
    MemList memory_list;
    struct DirParams dirparams;
    char command[MAX_COMMAND_LENGHT];


    list_init(&history);
    list_init(&opened_files);
    createEmptyMemList(&memory_list);
    init_standard_fds(&opened_files);
    init_params(&dirparams);

    while(true)
    {
        prompt();
        read_input(command);
        handle_input(command, &history, &opened_files, &dirparams, &memory_list);
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

void handle_input(char *command, List *history, List *opened_files, struct DirParams *params, MemList *memory_list)
{
    char *args[64];
    char *original_command = strdup(command);

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
        list_free(memory_list);
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
    // P2
    else if(!strcmp(args[0], "malloc")) cmd_malloc(args, memory_list);
    else if (!strcmp(args[0], "mmap")) cmd_mmap(args, opened_files, memory_list);
    else if(!strcmp(args[0], "shared")) cmd_shared(args, memory_list);
    else if(!strcmp(args[0], "free")) cmd_free(args, memory_list);
    else if(!strcmp(args[0], "memfill")) cmd_memfill(args);
    else if(!strcmp(args[0], "memdump")) cmd_memdump(args);
    else if(!strcmp(args[0], "mem")) cmd_mem(args, memory_list);
    else if(!strcmp(args[0], "readfile")) cmd_readfile(args);
    else if(!strcmp(args[0], "read")) cmd_read(args, opened_files);
    else if(!strcmp(args[0], "writefile")) cmd_writefile(args);
    else if(!strcmp(args[0], "write")) cmd_write(args, opened_files);
    else if(!strcmp(args[0], "recurse")) cmd_recurse(args);
    else if(!strcmp(args[0], "clear")) printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    else cmd_unknown(args);
}
