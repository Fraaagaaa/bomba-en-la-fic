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
    void* address;
    char date[128];
    int key;
    FileEntry file;
    memoryBlockType type;
} dataMem;

typedef struct {
    dataMem itemM[MAX_LISTMEM];
    int lastPos;
} MemList;

void createEmptyMemList(MemList*);
bool isEmptyMemList(MemList);
int nextMemListPos(int, MemList);
int prevMemListPos(int, MemList);
int firstMemListPos( MemList);
int lastMemListPos(MemList);
bool insertMemList(MemList* , dataMem);
dataMem getDataItemList(MemList, int) ;
void list_free(MemList*);
void deleteItemMemList(int, MemList*);
void deleteMemList(MemList*);
void InsertarNodoMmap(MemList*, void*, size_t, const char*, int);
dataMem newMemData(size_t,  void*, int, FileEntry*, memoryBlockType);
void printMemoryList(MemList, memoryBlockType);
bool deleteMemBySize(MemList*, size_t);
bool deleteMemByAddress(MemList*, void*);
bool deleteMemByKey(MemList*, key_t);
bool deleteMemByFileName(MemList*, char*);
void*DireccionNodoShared(MemList*, key_t);
void cmd_mmap(char**, List*, MemList*);


#endif //MEMLIST_H
