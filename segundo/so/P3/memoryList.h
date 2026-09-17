#ifndef MEMLIST_H
#define MEMLIST_H

#include "list.h"
#include "file.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXDATA 4096
#define MAX_LISTMEM 2048
#define MAX_FILENAME 256
#define NULLKEY -1
#define NULLM -1

typedef enum memoryBlockType {
    MALLOC, MMAP, SHARED, ALLMEM
} memoryBlockType;


typedef struct dataMem {
    size_t size;
    void * address;
    char date[128];
    int key;
    FileEntry file;
    memoryBlockType type;
} dataMem;

typedef struct {
    dataMem itemM[MAX_LISTMEM];
    int lastPos;
} MemList;

void createEmptyMemList(MemList *memList);
bool isEmptyMemList(MemList memList);
int nextMemListPos(int pMem, MemList memList);
int prevMemListPos(int pMem, MemList memList);
int firstMemListPos( MemList memList);
int lastMemListPos(MemList memList);
bool insertMemList(MemList* memList, dataMem m);
dataMem getDataItemList(MemList memList, int pMem) ;
void list_free(MemList *memList);
void deleteItemMemList( int pMem,MemList* memList);
void deleteMemList(MemList* memList);
void InsertarNodoMmap(MemList *lista, void *address, size_t tam, const char *filename, int fd);
dataMem newMemData(size_t size, void *address, int key, FileEntry *file, memoryBlockType type);
void printMemoryList(MemList list, memoryBlockType mem);
bool deleteMemBySize(MemList *memList, size_t size);
bool deleteMemByAddress(MemList *memList, void *address);
bool deleteMemByKey(MemList *memList, key_t key);
bool deleteMemByFileName(MemList *list, char* name);
void *DireccionNodoShared(MemList *list, key_t cl);
void cmd_mmap(char **args, List *opened_files, MemList *memory_list);


#endif //MEMLIST_H
