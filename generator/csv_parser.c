#include "csv_parser.h"
#include "matches.h"
#include <string.h>

PlayerStats *tempPlayer = NULL;
MatchStats *tempMatch = NULL;
int fieldIndex = 0;

void cb_field(void *field, size_t field_len, void *data)
{
    if (!tempPlayer)
    {
        if ((tempPlayer = malloc(sizeof(PlayerStats))) == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for PlayerStats.\n");
            exit(1);
        }
    }
    if (!tempMatch)
    {
        if ((tempMatch = malloc(sizeof(MatchStats))) == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for MatchStats\n");
            exit(1);
        }
    }

    char buffer[256];
    size_t copy_len = (field_len < sizeof(buffer) - 1) ? field_len : sizeof(buffer) - 1;
    memcpy(buffer, field, copy_len);
    buffer[copy_len] = '\0';

    switch (fieldIndex)
    {
    case FIELD_IP_ADDRESS:
        strncpy(tempMatch->ipAddress, buffer, sizeof(tempMatch->ipAddress) - 1);
        strncpy(tempPlayer->ipAddress, buffer, sizeof(tempPlayer->ipAddress) - 1);
        break;
    case FIELD_PLAYER_NAME:
        strncpy(tempMatch->playerName, buffer, sizeof(tempMatch->playerName) - 1);
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
        else if (fieldIndex >= FIELD_FLAGS_FLAT_START && fieldIndex < FIELD_FLAGS_FLAT_START + BOARD_CELL_COUNT)
        {
            tempMatch->flagsFlat[fieldIndex - FIELD_FLAGS_FLAT_START] = atoi(buffer);
        }
        break;
    }
    ++fieldIndex;
}

void cb_row(int columnCount, void *data)
{
    if (tempPlayer && tempMatch && fieldIndex == FIELD_NUM)
    {
        update_player_stats(tempPlayer, tempMatch);
        add_match(tempPlayer, tempMatch);
    }
    else
    {
        fprintf(stderr, "Ignoring line. The number of columns is incorrect.\n");
    }

    free(tempPlayer);
    tempPlayer = NULL;

    free(tempMatch);
    tempMatch = NULL;

    fieldIndex = 0;
}
