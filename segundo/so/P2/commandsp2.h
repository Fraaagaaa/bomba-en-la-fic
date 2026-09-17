#ifndef COMMANDSP2_H
#define COMMANDSP2_H

#include "commandsp1.h"
#include "auxiliar.h"
#include "memoryList.h"

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/mman.h>

dataMem newMemData(size_t, void*, int, FileEntry*, memoryBlockType);
void cmd_malloc(char**, MemList*);
void cmd_mmap(char**, List*, MemList*);
void cmd_shared(char**, MemList*);
void cmd_free(char**, MemList*);
void cmd_memfill(char**);
void cmd_memdump(char**);
void cmd_mem(char**, MemList*);
void cmd_write(char**, List*);
void cmd_writefile(char**);
void cmd_readfile(char**);
void cmd_read(char**, List*);
void cmd_recurse(char**);

void cmd_shared_free(char**, MemList*);
void cmd_shared_delkey(char**, MemList*);
void cmd_shared_create(char**, MemList*);

#endif
