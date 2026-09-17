#include "commandsp2.h"

void cmd_malloc(char **args, MemList *memory_list)
{
    if(args[1] == NULL)
    {
        printMemoryList(*memory_list, MALLOC);
        return;
    }
    
    else if (args[1] != NULL && !strcmp(args[1], "-free"))
    {
        // 2 = tamaño
        if (args[2] == NULL)
        {
            printf("Wrong use of malloc -free:\n");
            cmd_help(args);
            return;
        }

        size_t size = (size_t) strtoul(args[2], NULL, 10);

        if(!deleteMemBySize(memory_list, size))
            printf("Unable to remove memory\n");
        return;
    }
    
    // 1 = tamaño
    size_t size = (size_t) strtoul(args[1], NULL, 10);
    void *address = malloc(size);
    
    if(address == NULL)
    {
        printf("Unable to allocate memory\n");
        return;
    }

    dataMem newMem = newMemData(size, address, NULLKEY, NULL, MALLOC);

    insertMemList(memory_list, newMem);
    printf("Memory allocated at %p\n", address);
}

void cmd_mmap(char **args, List *opened_files, MemList *memory_list)
{
    if(args[1] == NULL)
    {
        printMemoryList(*memory_list, MMAP);
        return;
    }

    if(!strcmp(args[1], "-free"))
    {
        // 2 = nombre del fichero 
        if(args[2] == NULL)
        {
            printf("Wrong use of mmap -free:\n");
            cmd_help(args);
            return;
        }
        deleteMemByFileName(memory_list, args[2]);
        return;
    }

    if(args[1] == NULL || args[2] == NULL)
    {
        printf("Wrong use of mmap\n");
        cmd_help(args);
        return;
    }

    // 1 = archivo
    // 2 = permisos

    do_Mmap(memory_list, *opened_files, args);
}

void cmd_shared(char **args, MemList *memory_list)
{
    if(args[1] == NULL)
    {
        printMemoryList(*memory_list, SHARED);
        return;
    }
    if(!strcmp(args[1], "-create"))
    {
        // 2 = key
        // 3 = tamaño
        if(args[2] == NULL || args[3] == NULL)
        {
            printf("Wrong use of shared\n");
            cmd_help(args);
            return;
        }

        do_SharedCreate(args, memory_list);
        return;
    }
    if(!strcmp(args[1], "-free"))
    {
        // 2 = key
        if(args[2] == NULL)
        {
            printf("Wrong use of shared\n");
            cmd_help(args);
            return;
        }
        key_t cl = (key_t) strtoul(args[2], NULL, 10);
        doSharedFree(memory_list, cl);
        return;
    }
    if(!strcmp(args[1], "-delkey"))
    {
        // 2 = key
        if(args[2] == NULL)
        {
            printf("Wrong use of shared\n");
            cmd_help(args);
            return;
        }
        do_SharedDelkey(args);
        return;
    }
    // 2 = key
    do_Shared(*memory_list, args);
}

void cmd_free(char **args, MemList *memory_list)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of free\n");
        cmd_help(args);
        return;
    }
    // Para buscar direcciones hay que usar base hexadecimal
    void *address = (void *) strtoul(args[1], NULL, 16);

    if(deleteMemByAddress(memory_list, address))
        printf("Memory at %p freed\n", address);
    else
        printf("No allocated memory found at %p\n", address);
}

void cmd_memfill(char **args)
{
    // 1 = dirección de memoria
    // 2 = cont
    // 3 = caracter
    if(args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Wrong use of memfill\n");
        cmd_help(args);
        return;
    }

    void *address = (void *) strtoul(args[1], NULL, 16); 
    unsigned char character = args[3][0];
    size_t cont = strtoul(args[2], NULL, 10); 

    LlenarMemoria(address, cont, character);
    printf("Llenando %ld bytes de memoria con el byte '%c'(%u) a partir de la dirección %p\n", cont, character, character, address);
}

void cmd_memdump(char **args)
{
    if(args[1] == NULL || args[2] == NULL)
    {
        printf("Wrong use of memdump\n");
        cmd_help(args);
        return; 
    }

    void *address = (void *) strtoul(args[1], NULL, 16);
    size_t cont = (size_t) strtoul(args[2], NULL, 10);

    unsigned char *arr = (unsigned char*) address;
    size_t i;

    // Separar cada 20 líneas para que se vea bien
    for(i = 0; i < cont; i += 20)
    {
        size_t current_chunk_size = (cont - i > 20) ? 20 : (cont - i);
        if (current_chunk_size == 0) break;
        void *current_addr = arr + i;

        printf("%p-> ", current_addr);

        // Print de los caracteres
        for (size_t k = 0; k < current_chunk_size; k++)
        {
            if (isprint(arr[i + k]))
                printf("%c  ", arr[i + k]);
            else
                // para los caracteres no imprimibles
                switch (arr[i + k])
                {
                    case '\n': printf("\\n "); break;
                    case '\t': printf("\\t "); break;
                    case '\r': printf("\\r "); break;
                    case 0x00: printf("  "); break;
                    default: printf(". ");
                }
        }
        printf("\n");

        printf("%p-> ", current_addr);
        
        // Imprime el valor ascii de cada símbolo
        for (size_t k = 0; k < current_chunk_size; k++)
            printf("%02X ", arr[i + k]);
        printf("\n");
    }
}

void cmd_mem_funcs()
{
    printf("Direcciones de funciones\n");
    printf("Funciones del programa:\t%p, %p, %p\n", cmd_malloc, cmd_shared, cmd_mmap);
    printf("Funciones de librería:\t%p, %p, %p\n", malloc, getpid, printf);
}

// VARIABLES PARA mem_vars
extern int var_ext_no_ini;
extern int var_ext_no_ini_2;
extern int var_ext_no_ini_3;

void cmd_mem_vars()
{
    int var_local;
    int var_local_2;
    int var_local_3;

    
    static int var_est_no_ini;
    static int var_est_no_ini_2;
    static int var_est_no_ini_3;
    static int var_est = 10;
    static int var_est_2 = 10;
    static int var_est_3 = 10;

    printf("Direcciones de Variables:\n");
    printf("Variables locales: \t\t\t%p,\t%p,\t%p\n", &var_local, &var_local_2, &var_local_3); 
    printf("Variables globales: \t\t\t%p,\t%p,\t%p\n", &var_glob, &var_glob_2, &var_glob_3); 
    printf("Variables globales no inicializadas:\t%p,\t%p,\t%p\n", &var_ext_no_ini, &var_ext_no_ini_2, &var_ext_no_ini_3);
    printf("Variables estaticas: \t\t\t%p,\t%p,\t%p\n", &var_est, &var_est_2, &var_est_3);
    printf("Variables estaticas no inicializadas: \t%p,\t%p,\t%p\n", &var_est_no_ini, &var_est_no_ini_2, &var_est_no_ini_3);
}
void cmd_mem_blocks(MemList *memory_list)
{
    printMemoryList(*memory_list, MALLOC);
    printMemoryList(*memory_list, SHARED);
    printMemoryList(*memory_list, MMAP);

    return;
}


void cmd_mem(char **args, MemList *memory_list)
{
    if(args[1] == NULL)
    {
        printf("Wrong use of mem\n");
        return;
    }

    if(!strcmp(args[1], "-funcs")) // printea las direcciones de las funciones del código o de librerias
        cmd_mem_funcs();

    if(!strcmp(args[1], "-vars")) // printea las direcciones de memoria de las variables
        cmd_mem_vars();

    if(!strcmp(args[1], "-blocks")) //printea las las 3 listas de memoria
        cmd_mem_blocks(memory_list);

    if(!strcmp(args[1], "-pmap"))
        Do_pmap();

    if(!strcmp(args[1], "-all"))
    {
        cmd_mem_funcs();
        printf("\n");
        cmd_mem_vars();
        printf("\n");
        cmd_mem_blocks(memory_list);
    }
}

void cmd_readfile(char **args)
{
    Cmd_ReadFile(args); // codigo auxiliar
}

void cmd_writefile(char **args)
{
    // args[1]: file (Nombre del archivo)
    // args[2]: addr (Dirección, en formato cadena)
    // args[3]: cont (Cantidad de bytes)
    
    if(args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Wrong use of writefile\n"); // Mensaje de uso corregido
        cmd_help(args);
        return;
    }
    
    char* filename = args[1];
    void *p = CadenatoPointer(args[2]);
    size_t cont = (size_t) atoll(args[3]);
    ssize_t n;

    if (p == NULL)
    {
        perror("Direccion invalida");
        return;
    }
    
    if ((n = EscribirFichero(filename, p, cont)) == -1)
        perror("Imposible escribir fichero");
    else
        printf("escritos %lld bytes en %s desde %p\n", (long long) n, filename, p);
}

void cmd_write(char **args, List *opened_files)
{
    // args[1]: fd
    // args[2]: addr
    // args[3]: cont

    if(args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Wrong use of write");
        cmd_help(args);
        return;
    }
    
    int fd = atoi(args[1]);

    FileEntry *file = getFileByFd(fd, opened_files);
    args[1] = file->filename;
    
    cmd_writefile(args);
}

void cmd_read(char **args, List *opened_files)
{
    // 1 = FD
    // 2 = address
    // 3 = cont

    if(args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Wrong use of read");
        cmd_help(args);
        return;
    }
    
    // Cambia el el fd por el nombre del archivo para que sean los mismos
    // parámetros que para readfile
    int fd = atoi(args[1]);
    FileEntry *file = getFileByFd(fd, opened_files);

    // A Cmd_ReadFile le hay que pasar:
    // nombre archivo
    // addrs
    // cont
    if(file == NULL)
        perror("No se ha encontrado el archivo");
    args[1] = file->filename;

    Cmd_ReadFile(args);
}

void cmd_recurse(char **args)
{
    int n;
    if(args[1] == NULL)
    {
        printf("Wrong use of recurse");
        cmd_help(args);
        return;
    }
    n = atoi(args[1]);
    Recursiva(n);
}
