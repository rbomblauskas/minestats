#include "csv_parser.h"
#include <string.h>

PlayerStats *tempPlayer = NULL;
MatchStats *tempMatch = NULL;
int fieldIndex = 0;

void cb_field(void *field, size_t field_len, void *data)
{
    if (!tempPlayer)
    {
        tempPlayer = malloc(sizeof(PlayerStats));
    }
    if (!tempMatch)
    {
        tempMatch = malloc(sizeof(MatchStats));
    }

    char buffer[256];

    snprintf(buffer, field_len + 1, "%.*s", (int)field_len, (char *)field);

    switch (fieldIndex)
    {
    case FIELD_IP_ADDRESS:
        strncpy(tempPlayer->ipAddress, buffer, sizeof(tempPlayer->ipAddress) - 1);
        break;
    case FIELD_PLAYER_NAME:
        strncpy(tempPlayer->playerName, buffer, sizeof(tempPlayer->playerName) - 1);
        break;
    case FIELD_ELAPSED_SECONDS:
        tempPlayer->elapsedSeconds = atoi(buffer);
        break;
    case FIELD_TIMESTAMP:
        strncpy(tempMatch->timestamp, buffer, sizeof(tempMatch->timestamp) - 1);
        strncpy(tempPlayer->lastPlayed, buffer, sizeof(tempPlayer->lastPlayed) - 1);
        break;
    case FIELD_GAME_WON:
        tempMatch->gameWon = atoi(buffer);
        break;
    case FIELD_BOARD_SIZE:
        tempMatch->boardSize = atoi(buffer);
        break;
    case FIELD_MINE_PERCENTAGE:
        tempMatch->minePercentage = atof(buffer);
        break;
    default:
        if (fieldIndex >= FIELD_BOARD_FLAT_START && fieldIndex < FIELD_REVEALED_FLAT_START)
        {
            tempMatch->boardFlat[fieldIndex - FIELD_BOARD_FLAT_START] = atoi(buffer);
        }
        else if (fieldIndex >= FIELD_REVEALED_FLAT_START && fieldIndex < FIELD_FLAGS_FLAT_START)
        {
            tempMatch->revealedFlat[fieldIndex - FIELD_REVEALED_FLAT_START] = atoi(buffer);
        }
        else if (fieldIndex >= FIELD_FLAGS_FLAT_START && fieldIndex < FIELD_TOTAL)
        {
            tempMatch->flagsFlat[fieldIndex - FIELD_FLAGS_FLAT_START] = atoi(buffer);
        }
        break;
    }
    fieldIndex++;
}

void cb_row(int c, void *data)
{
    if (tempPlayer && tempMatch && fieldIndex == FIELD_NUM)
    {
        update_player_stats(tempPlayer->ipAddress, tempPlayer->elapsedSeconds, tempPlayer->lastPlayed, tempMatch->gameWon);
    }
    else
    {
        printf("Ignoring line. The number of columns is incorrect.\n");
    }
    if (tempPlayer)
    {
        free(tempPlayer);
        tempPlayer = NULL;
    }
    if (tempMatch)
    {
        free(tempMatch);
        tempMatch = NULL;
    }
    fieldIndex = 0;
}