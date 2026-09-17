#include "auxiliar.h"
#include "memoryList.h"

#define TAMANO 1024 

void Recursiva (int n)
{
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

    if (n>0)
        Recursiva(n-1);
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
    unsigned char *arr=(unsigned char *) p;
    size_t i;

    for (i=0; i<cont;i++)
        arr[i]=byte;
}

void * ObtenerMemoriaShmget (MemList *list, key_t clave, size_t tam)
{
    void * p;
    int aux,id,flags=0777; /*los 9 bits menos significativos de los flags:permisos*/
    struct shmid_ds s;

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL; /*cuando no es crear pasamos de tamano 0*/
    if (clave==IPC_PRIVATE)  /*no nos vale*/
    {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
            shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s); /* si no es crear, necesitamos el tamano, que es s.shm_segsz*/

    dataMem guardarMem = newMemData(tam, p, clave, NULL, SHARED);
    insertMemList(list, guardarMem);

    return (p);
}

void do_SharedCreate (char *tr[], MemList *memory_list)
{
    key_t cl;
    size_t tam;
    void *p;

    if (tr[2]==NULL || tr[3]==NULL)
    {
        printMemoryList(*memory_list, SHARED);
        return;
    }

    cl=(key_t)  strtoul(tr[2],NULL,10);
    tam=(size_t) strtoul(tr[3],NULL,10);
    if (tam==0)
    {
        printf ("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p=ObtenerMemoriaShmget(memory_list, cl, tam))!=NULL)
        printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_Shared (MemList memory_list, char *tr[])
{
    key_t cl;
    void *p;

    if (tr[1]==NULL) {
        printMemoryList(memory_list, SHARED);
        return;
    }

    cl=(key_t)  strtoul(tr[1],NULL,10);

    if ((p=ObtenerMemoriaShmget(&memory_list, cl, 0))!=NULL)
        printf ("Asignada memoria compartida de clave %lu en %p\n",(unsigned long) cl, p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void doSharedFree (MemList *memory_list, key_t cl)
{
    void *p;                                 /*llamo a la funcion de la lista*/
    /*que devuelve la direccion donde*/
    if ((p=DireccionNodoShared (memory_list,cl))==NULL)/*esta la memoria de clave cl*/
    {
        printf ("No hay bloque de esa clave mapeado en el proceso\n");
        return;
    }
    shmdt(p);
    if (!deleteMemByKey(memory_list,cl))  /*elimino el nodo */
        printf ("Imposible quitar de lista: %s\n",strerror(errno));
}

void do_SharedDelkey (char *args[])
{
    key_t clave;
    int id;
    char *key=args[2];

    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
    }
    if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
    // PUEDE QUE LA HAYA QUE ELIMINAR DE LA LISTA TAMBIEN
}

void * MapearFichero (MemList *memory_list, List opened_files, char * fichero, int protection)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
        modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
        return NULL;

    FileEntry *archivoAbierto = newFile(fichero, df, modo, 0); 

    if (archivoAbierto == NULL) // Error de malloc en newFile
    {
        munmap(p, s.st_size);
        close(df);
        return NULL;
    }

    dataMem nuevaMemoria = newMemData(s.st_size, p, NULLKEY, archivoAbierto,  MMAP);
    insertMemList(memory_list, nuevaMemoria);
    insertFileInList(&opened_files, fichero, df, modo);

    free(archivoAbierto); 

    /* Guardar en la lista    InsertarNodoMmap (&L,p, s.st_size,df,fichero); */
    /* Gurdas en la lista de descriptores usados df, fichero*/
    return p;
}

void do_Mmap(MemList *memory_list, List opened_files, char *arg[])
{ 
    void *p;
    int protection=0;

    if(arg[2][0] == 'r')  protection|=PROT_READ;
    if(arg[2][1] == 'w') protection|=PROT_WRITE;
    if(arg[2][2] == 'x') protection|=PROT_EXEC;

    if ((p=MapearFichero(memory_list, opened_files, arg[1],protection))==NULL)
        perror ("Imposible mapear fichero");
    else
        printf ("fichero %s mapeado en %p\n", arg[1], p);
}

void * CadenatoPointer (char * s)
{
    void *p;
    sscanf(s,"%p",&p);
    if (p==NULL)
        errno=EFAULT;
    return p;
}

ssize_t LeerFichero (char *f, void *p, size_t cont)
{
    struct stat s;
    ssize_t  n;  
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
        return -1;     
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=read(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

void Cmd_ReadFile (char *ar[])
{
    void *p;
    size_t cont=-1;  /*si no pasamos tamano se lee entero */
    ssize_t n;
    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    p=CadenatoPointer(ar[2]);  /*convertimos de cadena a puntero*/
    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);

    if ((n=LeerFichero(ar[1],p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[1],p);
}

void Do_pmap (void) /*sin argumentos*/
{ pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;   
        if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;    
        if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
        if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");      
        exit(1);
    }
    waitpid (pid,NULL,0);
}

//las siguientes funciones devuelven los permisos de un fichero en formato rwx----
//a partir del campo st_mode de la estructura stat 
//las tres son correctas pero usan distintas estrategias de asignación de memoria

char * ConvierteModo (mode_t m, char *permisos)
{
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    //propietario
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    //grupo
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    //resto
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    //setuid, setgid y stickybit
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

char LetraTF (mode_t m)
{
    switch (m&S_IFMT) 
    { //and bit a bit con los bits de formato,0170000 
        case S_IFSOCK: return 's'; //socket 
        case S_IFLNK: return 'l'; //symbolic link
        case S_IFREG: return '-'; // fichero normal
        case S_IFBLK: return 'b'; //block device
        case S_IFDIR: return 'd'; //directorio  
        case S_IFCHR: return 'c'; //char device
        case S_IFIFO: return 'p'; //pipe
        default: return '?'; //desconocido, no deberia aparecer
    }
}

int isDirectory(char * dir)          //para saber si algo es directorio o no
{
    struct stat s;
    if (lstat(dir,&s)==-1)       //si no puedo acceder: para mi no es directorio
        return 0;
    return (S_ISDIR(s.st_mode));
}

void remove_endline(char *string)
{
    char *pos;
    if((pos = strchr(string, '\n')) != NULL)
        *pos = '\0';
}

ssize_t EscribirFichero (char *f, void *p, size_t cont)
{
    ssize_t n;
    int df, aux;

    df = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
    if (df == -1)
        return -1;

    // Escribir 'cont' bytes desde la dirección 'p' en el descriptor 'df'
    if ((n = write(df, p, cont)) == -1) {
        aux = errno;
        close(df);
        errno = aux;
        return -1;
    }

    close(df);
    return n;
}
