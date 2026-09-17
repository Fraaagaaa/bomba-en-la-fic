#ifndef PRO2_2023_P2_TYPES_H
#define PRO2_2023_P2_TYPES_H

#define NAME_LENGTH_LIMIT 25
#include <stdbool.h>

typedef char tUserName[NAME_LENGTH_LIMIT];
typedef enum {basic, pro} tUserCategory;
typedef int tPlayTime;
typedef char tSongTitle[NAME_LENGTH_LIMIT];



typedef struct Song{
    tSongTitle songTitle;
    tPlayTime playTime;
} tSong;


#endif //PRO2_2023_P2_TYPES_H
