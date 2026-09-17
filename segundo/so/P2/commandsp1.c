#include "commandsp1.h"

void init_params(struct DirParams *params)
{
    params->long_format = 0;
    params->follow_links = 0;
    params->show_hidden = 0;
    params->recursion = 0; 
}

void cmd_create(char **args)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of create:\n");
        cmd_help(args);
        return;
    }
    if(!strcmp(args[1], "-f"))
    {
        if(creat(args[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1)
            perror("Unable to create file");
    }
    else
    {
        if(mkdir(args[1], S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1)
            perror("Unable to create directory");
    }
}

void cmd_setdirparams(char **args, struct DirParams *p)
{
    if(args[1] == NULL) cmd_getdirparams(args, p);
    else if(!strcmp(args[1], "long"))   p->long_format=1;
    else if(!strcmp(args[1], "short"))  p->long_format=0;
    else if(!strcmp(args[1], "link"))   p->follow_links=1;
    else if(!strcmp(args[1], "nolink")) p->follow_links=0;
    else if(!strcmp(args[1], "hid"))    p->show_hidden=1;
    else if(!strcmp(args[1], "nohid"))  p->show_hidden=0;
    else if(!strcmp(args[1], "reca"))   p->recursion=1;
    else if(!strcmp(args[1], "recb"))   p->recursion=2;
    else if(!strcmp(args[1], "norec"))  p->recursion=0;
    else fprintf(stderr,"Unknown parameter: %s\n",args[1]);
}

void cmd_getdirparams(char **args, struct DirParams *p)
{
    int params = p->long_format + p->follow_links * 10 + p->show_hidden * 100 + p->recursion * 1000;

    switch(params)
    {
        case 0:    printf("List: Short without links, non-recursive without hidden files"); break;
        case 1:    printf("List: Long without links, non-recursive without hidden files"); break;
        case 10:   printf("List: Short with links, non-recursive without hidden files"); break;
        case 11:   printf("List: Long with links, non-recursive without hidden files"); break;
        case 100:  printf("List: Short without links, non-recursive with hidden files"); break;
        case 101:  printf("List: Long without links, non-recursive with hidden files"); break;
        case 110:  printf("List: Short with links, non-recursive with hidden files"); break;
        case 111:  printf("List: Long with links, non-recursive with hidden files"); break;

        case 1000: printf("List: Short without links, recursive (preorder) without hidden files"); break;
        case 1001: printf("List: Long without links, recursive (preorder) without hidden files"); break;
        case 1010: printf("List: Short with links, recursive (preorder) without hidden files"); break;
        case 1011: printf("List: Long with links, recursive (preorder) without hidden files"); break;
        case 1100: printf("List: Short without links, recursive (preorder) with hidden files"); break;
        case 1101: printf("List: Long without links, recursive (preorder) with hidden files"); break;
        case 1110: printf("List: Short with links, recursive (preorder) with hidden files"); break;
        case 1111: printf("List: Long with links, recursive (preorder) with hidden files"); break;

        case 2000: printf("List: Short without links, recursive (posrtorder) without hidden files"); break;
        case 2001: printf("List: Long without links, recursive (posrtorder) without hidden files"); break;
        case 2010: printf("List: Short with links, recursive (posrtorder) without hidden files"); break;
        case 2011: printf("List: Long with links, recursive (posrtorder) without hidden files"); break;
        case 2100: printf("List: Short without links, recursive (posrtorder) with hidden files"); break;
        case 2101: printf("List: Long without links, recursive (posrtorder) with hidden files"); break;
        case 2110: printf("List: Short with links, recursive (posrtorder) with hidden files"); break;
        case 2111: printf("List: Long with links, recursive (posrtorder) with hidden files"); break;

        default: printf("Unable to resolve directory parameters"); break;
    }
    printf("\n");
}


void cmd_erase(char **args)
{
    // remove() llama a unlink para ficheros  y a rmdir para directorios
    // en la shell de referencia se pueden borrar archivos sin hacer primero un open, unlink no borra ficheros sin saber el df.
    // por lo que para ficheros usaremos remove 
    if(args[1] == NULL)
    {
        printf("Wrong use of erase:\n");
        cmd_help(args);
        return;
    }

    int i;
    for(i = 1; args[i] != NULL; i++)
    {
        if(isDirectory(args[i]))
        {
            if(rmdir(args[i]) == -1)
            {
                perror("Unable to remove folder");
                continue;
            }
        }
        else if(remove(args[i]) == -1)
            perror("Unable to remove file");
    }
}

void cmd_delrec(char **args)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of delrec:\n");
        cmd_help(args);
        return;
    }
    DIR *dir = NULL;
    struct dirent *entry;
    char *fullPath = NULL;

    if (!isDirectory(args[1]))
    {
        if (remove(args[1]) == -1)
            perror("Unable to remove file");
        return;
    }

    dir = opendir(args[1]);
    if (dir == NULL)
    {
        perror("Unable to open directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        size_t path_len = strlen(args[1]) + strlen(entry->d_name) + 2;
        fullPath = malloc(path_len);

        if (fullPath == NULL)
        {
            perror("Memory allocation failed");
            closedir(dir);
            return;
        }

        snprintf(fullPath, path_len, "%s/%s", args[1], entry->d_name);

        if (isDirectory(fullPath))
        {
            char *recursive_args[] = {"delrec", fullPath, NULL};
            cmd_delrec(recursive_args);
        }
        else
        {
            if (remove(fullPath) == -1)
                perror("Unable to remove file");
        }
        free(fullPath);
    }

    if(closedir(dir) == -1) perror("Unable to close directory");

    if (rmdir(args[1]) == -1) perror("Unable to remove directory");
}

void cmd_lseek(char **args, List *openedfiles)
{
    // args[1] = fd
    // args[2] = offset
    // args[3] = mode

    if(args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Wrong use of lseek:\n");
        cmd_help(args);
        return;
    }

    int fd = atoi(args[1]);
    int offset = atoi(args[2]);
    int mode;

    if(!strcmp(args[3], "SEEK_SET")) mode = SEEK_SET;      // new offset
    else if(!strcmp(args[3], "SEEK_CUR")) mode = SEEK_CUR; // original offset + new offset
    else if(!strcmp(args[3], "SEEK_END")) mode = SEEK_END; // size of file + new offset

    FileEntry *file;

    if(searchInList(&file, fd, openedfiles))
        if((file->offset = lseek(fd, offset, mode)) == -1)
            perror("Unable to change file offset");
}

void cmd_writestr(char **args, List *openedfiles)
{
    if(args[1] == NULL || args[2] == NULL)
    {
        printf("Wrong use of writestr:\n");
        cmd_help(args);
        return;
    }

    FileEntry *file;
    if(searchInList(&file, atoi(args[1]), openedfiles))
    {
        if(write(file->fd, args[2], strlen(args[2])) == -1)
        {
            printf("descriptor: %d", file->fd);
            perror("Unable to write file");
        }
    }
}

bool searchInList(FileEntry **file, int fd, List *list)
{ 
    if (file == NULL || list == NULL)
    {
        perror("Error: NULL parameters in searchInList");
        return false;
    }
    ListPos pos = list_first(*list);
    *file = NULL;

    while (pos != NULL)
    {
        FileEntry *current_file = list_get(pos);
        if (current_file->fd == fd)
        {
            *file = current_file;   
            return true;            
        }
        pos = list_next(pos);
    }

    fprintf(stderr, "File descriptor %d not found in file list\n", fd);
    return false;
}

void cmd_dir(char **args, struct DirParams *params)
{
    if (args[1] == NULL)
    {
        show_file_info(".", params);
        return;
    }
    else if(!strcmp(args[1], "-d") && args[2] != NULL)
    {
        for(int i = 2; args[i] != NULL; i++)
            show_file_info(args[i], params);
    }
    else
    {
        printf("Wrong use of dir:\n");
        cmd_help(args);
    }
}

void show_file_info(const char *path, struct DirParams *params)
{
    struct stat st;
    int result;

    if (params->follow_links)
        result = stat(path, &st);
    else
        result = lstat(path, &st);

    if (result == -1)
    {
        perror(path);
        return;
    }

    if (isDirectory((char*)path)) 
    {
        if (params->recursion > 0)
            list_directory_recursive(path, params);
        else
            list_directory(path, params);
    }
    else
    {
        if(params->long_format)
            print_long_format(path, &st, params);
        else 
            print_short_format(path, &st);
    }
}

void list_directory_recursive(const char *dirname, struct DirParams *params)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullpath[PATH_MAX];

    dir = opendir(dirname);
    if (dir == NULL)
    {
        perror(dirname);
        return;
    }

    // recA
    if (params->recursion == 1)
    {
        printf("************%s\n", dirname);

        while ((entry = readdir(dir)) != NULL)
        {
            if (!params->show_hidden && entry->d_name[0] == '.')
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);

            int result;
            if (params->follow_links)
                result = stat(fullpath, &st);
            else
                result = lstat(fullpath, &st);

            if (result == 0)
            {
                if(params->long_format)
                    print_long_format(entry->d_name, &st, params);
                else 
                    print_short_format(entry->d_name, &st);
            }
        }

        closedir(dir);
        dir = opendir(dirname);

        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if (!params->show_hidden && entry->d_name[0] == '.')
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);

            if (isDirectory(fullpath))
                list_directory_recursive(fullpath, params);
        }
    }
    else if (params->recursion == 2)// recB
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if (!params->show_hidden && entry->d_name[0] == '.')
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);

            if (isDirectory(fullpath))
                list_directory_recursive(fullpath, params);
        }

        closedir(dir);
        dir = opendir(dirname);

        printf("************%s\n", dirname);

        while ((entry = readdir(dir)) != NULL)
        {
            if (!params->show_hidden && entry->d_name[0] == '.')
                continue;

            snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);

            int result;
            if (params->follow_links)
                result = stat(fullpath, &st);
            else
                result = lstat(fullpath, &st);

            if (result == 0)
            {
                if(params->long_format)
                    print_long_format(entry->d_name, &st, params);
                else 
                    print_short_format(entry->d_name, &st);
            }
        }
    }

    closedir(dir);
}

void list_directory(const char *dirname, struct DirParams *params)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullpath[PATH_MAX];

    dir = opendir(dirname);
    if (dir == NULL)
    {
        perror(dirname);
        return;
    }

    printf("************%s\n", dirname);

    while ((entry = readdir(dir)) != NULL)
    {
        if (!params->show_hidden && entry->d_name[0] == '.')
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, entry->d_name);

        int result;
        if (params->follow_links)
            result = stat(fullpath, &st);
        else
            result = lstat(fullpath, &st);
        if (result == 0)
        {
            if(params->long_format)
                print_long_format(entry->d_name, &st, params);
            else 
                print_short_format(entry->d_name, &st);
        }
    }

    closedir(dir);
}

void print_short_format(const char *name, struct stat *st)
{
    printf("%8ld  %-s\n", st->st_size, name);
}


const char *get_username(uid_t uid)
{
    struct passwd *pw = getpwuid(uid);
    return pw ? pw->pw_name : "?";
}

const char *get_groupname(gid_t gid)
{
    struct group *gr = getgrgid(gid);
    return gr ? gr->gr_name : "?";
}


void print_long_format(const char *name, struct stat *st, struct DirParams *params)
{
    char permisos[12];
    char time_str[64];
    struct tm tm_info;

    ConvierteModo(st->st_mode, permisos);

    gmtime_r(&st->st_mtime, &tm_info);
    strftime(time_str, sizeof(time_str), "%Y/%m/%d-%H:%M", &tm_info);

    const char *user = get_username(st->st_uid);
    const char *group = get_groupname(st->st_gid);

    printf("%s %2ld %6ld %-8s %-8s %8s %10ld  %s",
            time_str,
            (long)st->st_nlink,
            (long)st->st_ino,
            user,
            group,
            permisos,
            (long)st->st_size,
            name);

    if (S_ISLNK(st->st_mode) && params->follow_links)
    {
        char linkbuf[PATH_MAX];
        ssize_t len = readlink(name, linkbuf, sizeof(linkbuf) - 1);
        if (len >= 0)
        {
            linkbuf[len] = '\0';
            printf(" -> %s", linkbuf);
        }
    }
    printf("\n");
}
