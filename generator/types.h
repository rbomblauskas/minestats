#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

#define MAX_IP_LENGTH 16
#define MAX_FILE_PATH_SIZE 255
#define MAX_PLAYERS 1000
#define MAX_MATCHES 10000
#define FIELD_NUM 250
#define BOARD_SIZE 9
#define BOARD_CELL_COUNT BOARD_SIZE*BOARD_SIZE

typedef struct
{
    char ipAddress[16];
    char playerName[50];
    int elapsedSeconds;
    int gamesWon;
    int gamesPlayed;
    float winRate;
    char lastPlayed[25];
} PlayerStats;

typedef struct
{
    char ipAddress[16];
    char playerName[50];
    bool gameWon;
    int boardSize;
    float minePercentage;
    char timestamp[25];
    bool boardFlat[BOARD_CELL_COUNT];
    bool revealedFlat[BOARD_CELL_COUNT];
    bool flagsFlat[BOARD_CELL_COUNT];
} MatchStats;

typedef struct
{
    PlayerStats *players;
    int playerCount;
} LeaderboardData;

typedef struct
{
    MatchStats *matches;
    int matchCount;
} MatchData;

#endif
