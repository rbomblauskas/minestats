#include "matches.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

MatchData matchData = {0};

void add_match(bool game_won, int board_size, float mine_percentage, const char *timestamp, bool *board_flat, bool *revealed_flat, bool *flags_flat)
{
    if (matchData.matchCount >= MAX_MATCHES)
    {
        fprintf(stderr, "Maximum amount of matches reached.\n");
        return;
    }

    MatchStats *new_match = &matchData.matches[matchData.matchCount++];
    new_match->gameWon = game_won;
    new_match->boardSize = board_size;
    new_match->minePercentage = mine_percentage;

    strncpy(new_match->timestamp, timestamp, sizeof(new_match->timestamp) - 1);
    new_match->timestamp[sizeof(new_match->timestamp) - 1] = '\0';

    memcpy(new_match->boardFlat, board_flat, BOARD_CELL_COUNT * sizeof(bool));
    memcpy(new_match->revealedFlat, revealed_flat, BOARD_CELL_COUNT * sizeof(bool));
    memcpy(new_match->flagsFlat, flags_flat, BOARD_CELL_COUNT * sizeof(bool));
}
