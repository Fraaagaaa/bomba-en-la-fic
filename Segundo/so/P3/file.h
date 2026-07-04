#ifndef FILE_H
#define FILE_H

#include "list.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define NULLFILE *newNullFile()

typedef struct FileEntry{
  int fd;
  char filename[512];
  int mode;
  int offset;
} FileEntry;

bool insertFile(List *, const char *, int , int );
FileEntry *newNullFile();
FileEntry *newFile(const char *, int, int, int );
void remove_file(int , List *);
bool insertFileInList(List *, const char*, int, int);
FileEntry *getFileByFd(int, List *);

#endif // FILE_H
