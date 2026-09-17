#include "file.h"

FileEntry *newFile(const char *filename, int fd, int mode, int offset)
{
    FileEntry *fileEntry = malloc(sizeof(FileEntry));

    if (fileEntry == NULL)
    {
        perror("Unable to allocate memory for file");
        return NULL;
    }
    
    if (fd == -1) { 
        free(fileEntry);
        return NULL;
    }

    fileEntry->fd = fd;
    strncpy(fileEntry->filename, filename, 511); 
    fileEntry->filename[511] = '\0';
    fileEntry->mode = mode;
    fileEntry->offset = offset;
    
    return fileEntry;
}

FileEntry *newNullFile()
{
    return newFile("", -1, 0, 0); 
}

bool insertFileInList(List *opened_files, const char *filename, int fd, int mode)
{
    FileEntry *file = newFile(filename, fd, mode, 0); 

    if (file == NULL)
        return false;

    if (list_insert(opened_files, file)) 
        return true;
        
    free(file); 
    return false;
}

void remove_file(int fd, List *opened_files)
{
    List pos;
    FileEntry *file;
    for(pos = list_first(*opened_files); !list_end(pos); pos = list_next(pos))
    {
        file = list_get(pos);
        if(file->fd == fd)
        {
            list_remove(opened_files, pos);
            free(file);
            break;
        }
    }
}

FileEntry *getFileByFd(int fd, List *opened_files)
{
    List pos;
    FileEntry *file;
    for(pos = list_first(*opened_files); !list_end(pos); pos = list_next(pos))
    {
        file = list_get(pos);
        if(file->fd == fd)
            return file;
    }
    return NULL;
}
