#include "memoryList.h"

void createEmptyMemList(MemList* memList)
{
    memList->lastPos=NULLM;
}

bool isEmptyMemList(MemList memList)
{
    return memList.lastPos==NULLM;
}

int nextMemListPos(int pMem, MemList memList)
{
    if(pMem==memList.lastPos)
        return NULLM;
    else
        return ++pMem;
}

int prevMemListPos(int pMem, MemList memList)
{
    if(pMem > 0)
        return --pMem;
    else
        return NULLM;
}

int firstMemListPos( MemList memList)
{
    return 0;
}

int lastMemListPos(MemList memList)
{
    return memList.lastPos;
}

bool insertMemList(MemList* memList, dataMem m)
{
    if(memList->lastPos < MAX_LISTMEM - 1)
    {
        memList->lastPos++;
        memList->itemM[memList->lastPos]=m;
        return true;
    }

    return false;
}

dataMem getDataItemList(MemList memList, int pMem)
{
    return memList.itemM[pMem];
}


void list_free(MemList *memList)
{
    int pos;
    dataMem item;

    for(pos = firstMemListPos(*memList); pos <= lastMemListPos(*memList); pos++)
    {
        item=getDataItemList(*memList,pos);

        if(item.type == MALLOC)
            free(item.address);
        if(item.type == MMAP)
            munmap(item.address, item.size);
        else if(item.type == SHARED && shmget(item.key,0,0) != -1 && shmdt(item.address) == -1)
            return;
    }
    memList->lastPos = NULLM;
}

void deleteItemMemList(int pos ,MemList *memList)
{
    int i;
    for(i = pos; i < memList->lastPos;i++)
        memList->itemM[i] = memList->itemM[i+1];

    memList->lastPos--;
}

void deleteMemList(MemList* memList)
{   // Mejor usar freeMemList antes de esta función
    int i;
    for(i=0;i<=memList->lastPos;i--)
    {
        deleteItemMemList(i,memList);
        memList->lastPos--;
    }
}

void InsertarNodoMmap(MemList *lista, void *address, size_t size, const char *filename, int fd)
{
    if (lista->lastPos >= MAX_LISTMEM)
    {
        printf("No hay espacio para más bloques de memoria.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(lista->itemM[lista->lastPos].date, 128, "%Y-%m-%d %H:%M:%S", tm_info);

    lista->itemM[lista->lastPos].size = size;
    lista->itemM[lista->lastPos].address = address;
    lista->itemM[lista->lastPos].type = MMAP;
    lista->itemM[lista->lastPos].file.fd = fd;
    snprintf(lista->itemM[lista->lastPos].file.filename, MAX_FILENAME, "%s", filename);

    lista->lastPos++;
}

void *DireccionNodoShared(MemList *lista, key_t clave)
{
    int i;
    for(i = 0; i <= lista->lastPos; i++)
    {
        if(lista->itemM[i].type == SHARED && lista->itemM[i].key==clave)
            return lista->itemM[i].address;
    }
    return NULL;
}

dataMem newMemData(size_t size, void *address, int key, FileEntry *file, memoryBlockType type) {
    dataMem memData;
    memData.size = size;
    memData.address = address;
    memData.type = type;

    // obtener la fecha y hora actual
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(memData.date, sizeof(memData.date), "%Y-%m-%d %H:%M:%S", t);
    
    if(type == SHARED) memData.key = key;
    else memData.key = NULLKEY;
    if(type == MMAP) memData.file = *file;
    else
    {
        FileEntry *archivoNulo = newNullFile();
        if(archivoNulo == NULL)
        {
            memData.file.fd = -1;
            memData.file.offset = 0;
            memData.file.filename[0] = '\0';
        }
        else
        {
            memData.file = *archivoNulo;
            free(archivoNulo);
        }
    }

    return memData;
}

bool deleteMemBySize(MemList *memList, size_t size)
{
    // PARA MALLOC
    int pos;
    dataMem memData;

    for(pos = firstMemListPos(*memList); pos <= lastMemListPos(*memList); pos = nextMemListPos(pos, *memList))
    {
        memData = getDataItemList(*memList, pos);

        if(memData.type == MALLOC && memData.size == size)
        {
            printf("Memory at %p freed\n", memData.address);
            free(memData.address);
            deleteItemMemList(pos, memList);
            return true;
        }
    }
    return false;
}

bool deleteMemByKey(MemList *memList, key_t key)
{
    // PARA SHARED
    int pos;
    dataMem memData;

    for (pos = firstMemListPos(*memList); pos <= lastMemListPos(*memList); pos++)
    {
        memData = getDataItemList(*memList, pos);

        if (memData.type == SHARED && memData.key == (int)key)
        {
            deleteItemMemList(pos, memList);
            return true;
        }
    }
    return false;
}

bool deleteMemByAddress(MemList *memList, void *address)
{
    int pos;
    dataMem memData;

    for (pos = firstMemListPos(*memList); pos <= lastMemListPos(*memList); pos++)
    {
        memData = getDataItemList(*memList, pos);
        if(memData.address != address)
            continue;

        switch(memData.type)
        {
            case MALLOC:
                free(memData.address);
                deleteItemMemList(pos,memList);
                return true;
            case SHARED:
                deleteItemMemList(pos, memList);
            case MMAP:
                munmap(memData.address, memData.size);
                deleteItemMemList(pos, memList);
                return true;
            case ALLMEM:
                return false;
        }
    }
    return false;
}

bool deleteMemByFileName(MemList *list, char* name)
{
    int pos;
    dataMem memData;
    for (pos = firstMemListPos(*list); pos <= lastMemListPos(*list); pos++)
    {
        memData = getDataItemList(*list, pos);
        if(memData.type == MMAP && !strcmp(memData.file.filename, name))
        {
            deleteItemMemList(pos, list);
            return true;
        }
    }
    return false;
}

void printMemoryList(MemList list, memoryBlockType mem)
{
    int pos;
    dataMem memData;

    switch(mem)
    {
        case MALLOC:
            printf("Lista de bloques asignados con malloc para el proceso %d\n", getpid());
            break;
        case SHARED:
            printf("Lista de bloques asignados con shared para el proceso %d\n", getpid());
            break;
        case MMAP:
            printf("Lista de bloques asignados con mmap para el proceso %d\n", getpid());
            break;
        case ALLMEM: break;
    }

    if(isEmptyMemList(list))
    {
        printf("La lista está vacía\n");
        return;
    }
    
    switch (mem)
    {
        case MALLOC:
            for(pos = firstMemListPos(list); pos <= lastMemListPos(list); pos++)
            {
                memData = getDataItemList(list, pos);
                if(memData.type == MALLOC)
                {
                    printf("\t%p\t\t%zu %s malloc\n", memData.address, memData.size, memData.date);
                }
            }
            return;
        case SHARED:
            for(pos = firstMemListPos(list); pos <= lastMemListPos(list); pos++)
            {
                memData = getDataItemList(list, pos);
                if(memData.type == SHARED)
                {
                    printf("\t%p\t\t%zu %s shared (key: %d)\n", memData.address, memData.size, memData.date, memData.key);
                }
            }
            return;
        case MMAP:
            for(pos = firstMemListPos(list); pos <= lastMemListPos(list); pos++)
            {
                memData = getDataItemList(list, pos);
                if(memData.type == MMAP)
                {
                    printf("\t%p\t\t%zu %s %s  (descriptor %d)\n", memData.address, memData.size, memData.date, memData.file.filename, memData.file.fd);
                }
            }
            return;
        case ALLMEM:
            for(pos = firstMemListPos(list); pos <= lastMemListPos(list); pos++)
            {
                memData = getDataItemList(list, pos);
                switch (memData.type)
                {
                    case MALLOC: 
                        printf("\t%p\t\t%zu %s malloc\n", memData.address, memData.size, memData.date);
                        break;
                    case SHARED:
                        printf("\t%p\t\t%zu %s shared (key: %d)\n", memData.address, memData.size, memData.date, memData.key);
                        break;
                    case MMAP:
                        printf("\t%p\t\t%zu %s %s  (descriptor %d)\n", memData.address, memData.size, memData.date, memData.file.filename, memData.file.fd);
                        break;
                    case ALLMEM: break;
                }
            }
    }
}
