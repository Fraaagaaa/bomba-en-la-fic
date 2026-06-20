#include "commandsp0.h"

void cmd_listopen(List *opened_files)
{
    ListPos p = list_first(*opened_files);
    while(!list_end(p))
    {
        FileEntry* f = (FileEntry*)list_get(p);
        if(f->offset == -1)
            printf("descriptor: %d, offset: (  )-> %s %s\n", f->fd, f->filename, modetostring(f->mode));
        else
            printf("descriptor: %d, offset: (%d)-> %s %s\n", f->fd, f->offset, f->filename, modetostring(f->mode));
        p = list_next(p);
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
        else if(!strcmp(args[i], "ex")) mode |= O_EXCL;
        else if(!strcmp(args[i], "ro")) mode |= O_RDONLY;
        else if(!strcmp(args[i], "wo")) mode |= O_WRONLY;
        else if(!strcmp(args[i], "rw")) mode |= O_RDWR;
        else if(!strcmp(args[i], "ap")) mode |= O_APPEND;
        else if(!strcmp(args[i], "tr")) mode |= O_TRUNC;
        else break;
    }

    fd = open(args[1], mode, 0777);
    if(fd == -1)
    { 
        perror("Unable to open file");
        return;
    }

    if(insertFileInList(opened_files, args[1], fd, mode) == false)
    {
        close(fd);
        return;
    }
    printf("File '%s' opened with fd %d and mode %x\n", args[1], fd, mode);
}

void cmd_close(char *args[], List *opened_files)
{ 
    int fd;
    FileEntry *file = NULL;

    if(args[1] != NULL) 
        fd = atoi(args[1]);

    if (args[1]== NULL)
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
            file = f;
            break;
        }
        pos = list_next(pos);
    }


    if(close(file->fd) == -1 || file == NULL)
    {
        perror("Unable to identify file descriptor");
        return;
    }
    else
        remove_file(fd, opened_files);
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
    snprintf(dupFile->filename, sizeof(dupFile->filename), "dupplicated from %d (%.480s)", origFile->fd, origFile->filename);

    dupFile->fd = duplicado;
    dupFile->filename[sizeof(dupFile->filename) - 1] = '\0'; // opcional, snprintf ya garantiza terminador
    dupFile->offset = lseek(duplicado, 0, SEEK_CUR);
    dupFile->mode = fcntl(duplicado, F_GETFL);
    // man fcntl:
    // Get  the  file status flags and file access modes, defined in <fcntl.h>, for the file description associated with fildes.  The file access modes can be
    // extracted from the return value using the mask O_ACCMODE, which is defined in <fcntl.h>.  File status flags and file access modes are  associated  with
    // the file description and do not affect other file descriptors that refer to the same file with different open file descriptions. The flags returned may
    // include  non-standard file status flags which the application did not set, provided that these additional flags do not alter the behavior of a conform‐ing application.

    if (!list_insert(opened_files, dupFile))
    {
        perror("Unable to add duplicated file into file list");
        close(duplicado);
        free(dupFile);
        return;
    }
}

void init_standard_fds(List *opened_files)
{
    FileEntry *f;

    f = malloc(sizeof(FileEntry));
    f->fd = 0;
    f->offset = lseek(0, 0, SEEK_CUR);
    strcpy(f->filename, "standard input");
    f->mode = O_RDWR;
    list_insert(opened_files, f);

    f = malloc(sizeof(FileEntry));
    f->fd = 1;
    f->offset = lseek(1, 0, SEEK_CUR);
    strcpy(f->filename, "standard output");
    f->mode = O_RDWR;
    list_insert(opened_files, f);

    f = malloc(sizeof(FileEntry));
    f->fd = 2;
    f->offset = lseek(2, 0, SEEK_CUR);
    strcpy(f->filename, "standard error");
    f->mode = O_RDWR;
    list_insert(opened_files, f);
}

char* modetostring(int mode)
{
    static char buf[32];

    if((mode & O_ACCMODE) == O_RDONLY || mode == 0) strcpy(buf, "O_RDONLY");
    if((mode & O_ACCMODE) == O_WRONLY) strcpy(buf, "O_WRONLY");
    if((mode & O_ACCMODE) == O_RDWR)   strcpy(buf, "O_RDWR");

    if(mode & O_APPEND) strcat(buf, " | O_APPEND");
    if(mode & O_CREAT)  strcat(buf, " | O_CREAT");
    if(mode & O_EXCL)   strcat(buf, " | O_EXCL");
    if(mode & O_TRUNC)  strcat(buf, " | O_TRUNC");

    return buf;
}

void cmd_authors(char **args)
{
    if(args[1] == NULL)
    {
        printf("Author: Miguel Fraga Pico\n");
        printf("Login: miguel.fraga.pico\n");
        return;
    }
    else if(strcmp(args[1], "-n") == 0) printf("Authors: Miguel Fraga Pico\n");
    else if(strcmp(args[1], "-l") == 0) printf("Login: miguel.fraga.pico\n");
    else
    {
        printf("Wrong use of authors:\n");
        cmd_help(args);
    }
}

void cmd_getpid(char **args)
{
    if(args[1] == NULL) printf("Shell's process PID: %d\n", getpid());
    else if(strcmp(args[1], "-p") == 0) printf("Shell's parent PID: %d\n", getppid());
    else
    {
        printf("Wrong use of getppid:\n");
        cmd_help(args);
    }
}

void cmd_chdir(char **args)
{
    char *cwd = getcwd(NULL, 0);
    if(args[1]==NULL) printf("%s\n", cwd);
    else if(chdir(args[1])!=0) perror("Unable to change directory");
    free(cwd);
}

void cmd_getcwd(char **args)
{
    char *cwd = getcwd(NULL, 0);
    if(cwd != NULL) printf("Directory: %s\n", cwd);
    else perror("getcwd");
    free(cwd);
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

void cmd_hour(char **args)
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
        list_clear(history); // esto da muchos problemas
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


void add_command_to_history(char *command, List *history)
{
    list_insert(history, command);
}

void cmd_help(char **args)
{
    if (args[1] == NULL && !strcmp(args[0], "help"))
    {
        printf("Available commands (type \"help cmd\" for details):\n");
        // P0
        printf("\tauthors\n");
        printf("\tgetpid\n");
        printf("\tchdir\n");
        printf("\tgetcwd\n");
        printf("\tdate\n");
        printf("\thour\n");
        printf("\thistoric\n");
        printf("\topen\n");
        printf("\tclose\n");
        printf("\tdup\n");
        printf("\tlistopen\n");
        printf("\tinfosys\n");
        printf("\thelp\n");
        printf("\tquit\n");
        // P1
        printf("\tcreate\n");
        printf("\tsetdirparams\n");
        printf("\tgetdirparams\n");
        printf("\tdir\n");
        printf("\terrase\n");
        printf("\tdelrec\n");
        printf("\tlseekd\n");
        printf("\twritestr\n");
        // P2
        printf("\tmalloc\n");
        printf("\tmmap\n");
        printf("\tshared\n");
        printf("\tfree\n");
        printf("\tmemfill\n");
        printf("\tmemdump\n");
        printf("\tmem\n");
        printf("\treadfile\n");
        printf("\twritefile\n");
        printf("\tread\n");
        printf("\twrite\n");
        printf("\trecurse\n");
        return;
    }
    else if(args[1] != NULL) // POR HELP <COMANDO>
    {
        // P0
        if(!strcmp(args[0], "authors") || !strcmp(args[1], "authors"))
        {
            printf("authors | authors -l | authors -n\n");
            printf("Prints authors and logins; -l logins only, -n names only.\n");
        }
        else if(!strcmp(args[0], "getpid") || !strcmp(args[1], "getpid"))
        {
            printf("getpid | getpid -p\n");
            printf("Shows the shell PID; with -p, shows the parent PID.\n");
        }
        else if(!strcmp(args[0], "chdir") || !strcmp(args[1], "chdir"))
        {
            printf("chdir [dir]\n");
            printf("Changes current directory to dir; without arguments, prints the current working directory.\n");
        }
        else if(!strcmp(args[0], "getcwd") || !strcmp(args[1], "getcwd"))
        {
            printf("getcwd\n");
            printf("Prints the current working directory.\n");
        }
        else if(!strcmp(args[0], "date") || !strcmp(args[1], "date"))
        {
            printf("date | date -d | date -t\n");
            printf("No option: date and time; -d date only; -t time only.\n");
        }
        else if(!strcmp(args[0], "hour") || !strcmp(args[1], "hour"))
        {
            printf("hour\n");
            printf("Prints current time hh:mm:ss.\n");
        }
        else if(!strcmp(args[0], "historic") || !strcmp(args[1], "historic"))
        {
            printf("historic | historic N | historic -N | historic -count | historic -clear\n");
            printf("Lists command history; shows the Nth number with N; last N with -N; -count returns the number of elements in the list; -clear emptyes the list.\n");
        }
        else if(!strcmp(args[0], "open") || !strcmp(args[1], "open"))
        {
            printf("open [file] mode\n");
            printf("Opens file with mode or, with no args, lists open files.\n");
            printf("Modes: cr, ap, ex, ro, rw, wo, tr.\n");
        }
        else if(!strcmp(args[0], "close") || !strcmp(args[1], "close"))
        {
            printf("close fd\n");
            printf("Closes file descriptor fd and remove it from the list.\n");
        }
        else if(!strcmp(args[0], "dup") || !strcmp(args[1], "dup"))
        {
            printf("dup fd\n");
            printf("Duplicates file descriptor fd and adds it to the list.\n");
        }
        else if(!strcmp(args[0], "listopen") || !strcmp(args[1], "listopen"))
        {
            printf("listopen\n");
            printf("Lists the shell’s opened files.\n");
        }
        else if(!strcmp(args[0], "infosys") || !strcmp(args[1], "infosys"))
        {
            printf("infosys\n");
            printf("Print system information.\n");
        }
        else if(!strcmp(args[0], "quit") || !strcmp(args[1], "quit"))
        {
            printf("quit\n");
            printf("Exit the shell.\n");
        }
        // P1
        else if(!strcmp(args[0], "create") || !strcmp(args[1], "create"))
        {
            printf("create [name]| create -f [name]\n");
            printf("No option: create a directory called name; -f create a file called name\n");
        }
        else if(!strcmp(args[0], "setdirparams") || !strcmp(args[1], "setdirparams"))
        {
            printf("setdirparams long | setdirparams short | setdirparams link | setdirparams nolink | setdirparams hid | setdirparams nohid | setdirparams reca | setdirparams recb | setdirparams norec\n");
            printf("Set directory listing parameters to long; set listing parameters to short; set listing parameters with symbolic link destination; set listing parameters without symbolic link destination; set listing parameters to omit hidden files; set lising parameters to list hidden directories; set listing parameters to show recurse directories after; set listing parameters to show recurse directories before; set listing parameters to not show recurse directories\n");
        }
        else if(!strcmp(args[0], "getdirparams") || !strcmp(args[1], "getdirparams"))
        {
            printf("getdirparams\n");
            printf("Shows the parameters values for listing directories\n");
        }
        else if(!strcmp(args[0], "dir") || !strcmp(args[1], "dir"))
        {
            printf("dir n1 n2...| dir -d n1 n2...\n");
            printf("Shows information for the following files/dirs depending on the parameters; shows informetion for the following files/dirs and its content if is a directorie\n");
        }
        else if(!strcmp(args[0], "erase") || !strcmp(args[1], "erase"))
        {
            printf("erase n1 n2...\n");
            printf("Delete the following files or empty directories\n");
        }
        else if(!strcmp(args[0], "delrec") || !strcmp(args[1], "delrec"))
        {
            printf("delrec n1 n2...\n");
            printf("Delete the following files or non empty directories\n");
        }
        else if(!strcmp(args[0], "lseek") || !strcmp(args[1], "lseek"))
        {
            printf("lseek df off ref\n");
            printf("Positions the offset in an open file; df: file descriptor for the open file; off: new offset; ref: reference SEEK_SET (offset from the beginning), SEEK_CUR (offset from current position), SEEK_END (offset from the end)\n");
        }
        else if(!strcmp(args[0], "writestr") || !strcmp(args[1], "writestr"))
        {
            printf("writestr df str\n");
            printf("Write the string str in the open file with the descriptor df\n");
        }
        // P2
        else if(!strcmp(args[0], "malloc") || !strcmp(args[1], "malloc"))
        {
            printf("malloc n | malloc -free n | malloc\n");
            printf("Allocates n bytes; deallocates a block of size n; lists allocated malloc blocks.\n");
        }
        else if(!strcmp(args[0], "mmap") || !strcmp(args[1], "mmap"))
        {
            printf("mmap fich perm | mmap -free fich | mmap\n");
            printf("Maps file fich with permissions perm; unmaps file fich; lists mapped file blocks.\n");
        }
        else if(!strcmp(args[0], "shared") || !strcmp(args[1], "shared"))
        {
            printf("shared -create cl n | shared cl | shared -free cl | shared -delkey cl | shared\n");
            printf("Creates & attaches shared memory block cl of size n; attaches shared memory block cl; detaches block cl; removes block cl key from system; lists attached shared blocks.\n");
        }
        else if(!strcmp(args[0], "free") || !strcmp(args[1], "free"))
        {
            printf("free addr\n");
            printf("Deallocates/detaches the block with address addr (malloc, shared, or mmap).\n");
        }
        else if(!strcmp(args[0], "memfill") || !strcmp(args[1], "memfill"))
        {
            printf("memfill addr cont ch\n");
            printf("Fills memory with character ch, starting at address addr, for cont bytes.\n");
        }
        else if(!strcmp(args[0], "memdump") || !strcmp(args[1], "memdump"))
        {
            printf("memdump addr cont\n");
            printf("Dumps cont bytes of memory at address addr (hex codes and printable chars).\n");
        }
        else if(!strcmp(args[0], "mem") || !strcmp(args[1], "mem"))
        {
            printf("mem -funcs | mem -vars | mem -blocks | mem -all | mem -pmap\n");
            printf("Prints addresses of functions; addresses of variables; list of allocated blocks; all of the above; shows pmap/vmmap output.\n");
        }
        else if(!strcmp(args[0], "readfile") || !strcmp(args[1], "readfile"))
        {
            printf("readfile file addr cont\n");
            printf("Reads cont bytes of a file into memory address addr.\n");
        }
        else if(!strcmp(args[0], "writefile") || !strcmp(args[1], "writefile"))
        {
            printf("writefile file addr cont\n");
            printf("Writes to a file cont bytes starting at memory address addr.\n");
        }
        else if(!strcmp(args[0], "read") || !strcmp(args[1], "read"))
        {
            printf("read df addr cont\n");
            printf("Reads cont bytes from opened file descriptor df into memory address addr.\n");
        }
        else if(!strcmp(args[0], "write") || !strcmp(args[1], "write"))
        {
            printf("write df addr cont\n");
            printf("Writes to opened file descriptor df cont bytes starting at memory address addr.\n");
        }
        else if(!strcmp(args[0], "recurse") || !strcmp(args[1], "recurse"))
        {
            printf("recurse n\n");
            printf("Executes a recursive function n times, printing addresses of automatic, static arrays, and parameter.\n");
        }
    }
    else // POR MAL USO DEL COMANDO
    {
        // P0
        if(!strcmp(args[0], "authors"))
        {
            printf("authors | authors -l | authors -n\n");
            printf("Prints authors and logins; -l logins only, -n names only.\n");
        }
        else if(!strcmp(args[0], "getpid"))
        {
            printf("getpid | getpid -p\n");
            printf("Shows the shell PID; with -p, shows the parent PID.\n");
        }
        else if(!strcmp(args[0], "chdir"))
        {
            printf("chdir [dir]\n");
            printf("Changes current directory to dir; without arguments, prints the current working directory.\n");
        }
        else if(!strcmp(args[0], "getcwd"))
        {
            printf("getcwd\n");
            printf("Prints the current working directory.\n");
        }
        else if(!strcmp(args[0], "date"))
        {
            printf("date | date -d | date -t\n");
            printf("No option: date and time; -d date only; -t time only.\n");
        }
        else if(!strcmp(args[0], "hour"))
        {
            printf("hour\n");
            printf("Prints current time hh:mm:ss.\n");
        }
        else if(!strcmp(args[0], "historic"))
        {
            printf("historic | historic N | historic -N | historic -count | historic -clear\n");
            printf("Lists command history; shows the Nth number with N; last N with -N; -count returns the number of elements in the list; -clear emptyes the list.\n");
        }
        else if(!strcmp(args[0], "open"))
        {
            printf("open [file] mode\n");
            printf("Opens file with mode or, with no args, lists open files.\n");
            printf("Modes: cr, ap, ex, ro, rw, wo, tr.\n");
        }
        else if(!strcmp(args[0], "close"))
        {
            printf("close fd\n");
            printf("Closes file descriptor fd and remove it from the list.\n");
        }
        else if(!strcmp(args[0], "dup"))
        {
            printf("dup fd\n");
            printf("Duplicates file descriptor fd and adds it to the list.\n");
        }
        else if(!strcmp(args[0], "listopen"))
        {
            printf("listopen\n");
            printf("Lists the shell’s opened files.\n");
        }
        else if(!strcmp(args[0], "infosys"))
        {
            printf("infosys\n");
            printf("Print system information.\n");
        }
        else if(!strcmp(args[0], "quit"))
        {
            printf("quit\n");
            printf("Exit the shell.\n");
        }
        else if(!strcmp(args[0], "create"))
        {
            printf("create [name]| create -f [name]\n");
            printf("No option: create a directory called name; -f create a file called name\n");
        }
        else if(!strcmp(args[0], "setdirparams"))
        {
            printf("setdirparams long | setdirparams short | setdirparams link | setdirparams nolink | setdirparams hid | setdirparams nohid | setdirparams reca | setdirparams recb | setdirparams norec\n");
            printf("Set directory listing parameters to long; set listing parameters to short; set listing parameters with symbolic link destination; set listing parameters without symbolic link destination; set listing parameters to omit hidden files; set lising parameters to list hidden directories; set listing parameters to show recurse directories after; set listing parameters to show recurse directories before; set listing parameters to not show recurse directories\n");
        }
        else if(!strcmp(args[0], "getdirparams"))
        {
            printf("getdirparams\n");
            printf("Shows the parameters values for listing directories\n");
        }
        else if(!strcmp(args[0], "dir"))
        {
            printf("dir n1 n2...| dir -d n1 n2...\n");
            printf("Shows information for the following files/dirs depending on the parameters; shows informetion for the following files/dirs and its content if is a directorie\n");
        }
        else if(!strcmp(args[0], "erase"))
        {
            printf("erase n1 n2...\n");
            printf("Delete the following files or empty directories\n");
        }
        else if(!strcmp(args[0], "delrec") || !strcmp(args[1], "delrec"))
        {
            printf("delrec n1 n2...\n");
            printf("Delete the following files or non empty directories\n");
        }
        else if(!strcmp(args[0], "lseek"))
        {
            printf("lseek df off ref\n");
            printf("Positions the offset in an open file; df: file descriptor for the open file; off: new offset; ref: reference SEEK_SET (offset from the beginning), SEEK_CUR (offset from current position), SEEK_END (offset from the end)\n");
        }
        else if(!strcmp(args[0], "writestr"))
        {
            printf("writestr df str\n");
            printf("Write the string str in the open file with the descriptor df\n");
        }
        // --- (Nuevos comandos de gestión de memoria con 'cmd')
        else if(!strcmp(args[0], "malloc"))
        {
            printf("malloc n | malloc -free n | malloc\n");
            printf("Allocates n bytes; deallocates a block of size n; lists allocated malloc blocks.\n");
        }
        else if(!strcmp(args[0], "mmap"))
        {
            printf("mmap fich perm | mmap -free fich | mmap\n");
            printf("Maps file fich with permissions perm; unmaps file fich; lists mapped file blocks.\n");
        }
        else if(!strcmp(args[0], "shared"))
        {
            printf("shared -create cl n | shared cl | shared -free cl | shared -delkey cl | shared\n");
            printf("Creates & attaches shared memory block cl of size n; attaches shared memory block cl; detaches block cl; removes block cl key from system; lists attached shared blocks.\n");
        }
        else if(!strcmp(args[0], "free"))
        {
            printf("free addr\n");
            printf("Deallocates/detaches the block with address addr (malloc, shared, or mmap).\n");
        }
        else if(!strcmp(args[0], "memfill"))
        {
            printf("memfill addr cont ch\n");
            printf("Fills memory with character ch, starting at address addr, for cont bytes.\n");
        }
        else if(!strcmp(args[0], "memdump"))
        {
            printf("memdump addr cont\n");
            printf("Dumps cont bytes of memory at address addr (hex codes and printable chars).\n");
        }
        else if(!strcmp(args[0], "mem"))
        {
            printf("mem -funcs | mem -vars | mem -blocks | mem -all | mem -pmap\n");
            printf("Prints addresses of functions; addresses of variables; list of allocated blocks; all of the above; shows pmap/vmmap output.\n");
        }
        else if(!strcmp(args[0], "readfile"))
        {
            printf("readfile file addr cont\n");
            printf("Reads cont bytes of a file into memory address addr.\n");
        }
        else if(!strcmp(args[0], "writefile"))
        {
            printf("writefile file addr cont\n");
            printf("Writes to a file cont bytes starting at memory address addr.\n");
        }
        else if(!strcmp(args[0], "read"))
        {
            printf("read df addr cont\n");
            printf("Reads cont bytes from opened file descriptor df into memory address addr.\n");
        }
        else if(!strcmp(args[0], "write"))
        {
            printf("write df addr cont\n");
            printf("Writes to opened file descriptor df cont bytes starting at memory address addr.\n");
        }
        else if(!strcmp(args[0], "recurse"))
        {
            printf("recurse n\n");
            printf("Executes a recursive function n times, printing addresses of automatic, static arrays, and parameter.\n");
        }
    }
}
