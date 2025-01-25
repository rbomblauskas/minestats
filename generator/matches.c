#include "matches.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

MatchData matchData = {0};

void add_match(const PlayerStats *player, const MatchStats *match)
{
    if (matchData.matchCount >= MAX_MATCHES)
    {
        fprintf(stderr, "Maximum amount of matches reached.\n");
        return;
    }

    MatchStats *new_match = &matchData.matches[matchData.matchCount++];
    new_match->gameWon = match->gameWon;
    new_match->boardSize = match->boardSize;
    new_match->minePercentage = match->minePercentage;

    strncpy(new_match->ipAddress, match->ipAddress, sizeof(new_match->ipAddress) - 1);
    strncpy(new_match->playerName, match->playerName, sizeof(new_match->playerName) - 1);
    strncpy(new_match->timestamp, match->timestamp, sizeof(new_match->timestamp) - 1);
    new_match->timestamp[sizeof(new_match->timestamp) - 1] = '\0';

    memcpy(new_match->boardFlat, match->boardFlat, BOARD_CELL_COUNT * sizeof(bool));
    memcpy(new_match->revealedFlat, match->revealedFlat, BOARD_CELL_COUNT * sizeof(bool));
    memcpy(new_match->flagsFlat, match->flagsFlat, BOARD_CELL_COUNT * sizeof(bool));
}
