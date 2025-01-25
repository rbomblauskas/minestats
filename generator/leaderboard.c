#include "leaderboard.h"
#include "csv_parser.h"
#include <string.h>

LeaderboardData leaderboard = {0};

void update_player_stats(const PlayerStats *player, const MatchStats *match)
{
    // Randame esantį žaidėją
    for (int i = 0; i < leaderboard.playerCount; i++)
    {

        if (strcmp(leaderboard.players[i].ipAddress, player->ipAddress) == 0)
        {
            // Naudojame paskutinį nurodytą žaidėjo vardą
            strncpy(leaderboard.players[i].playerName, player->playerName, sizeof(leaderboard.players[i].playerName) - 1);
            // Atnaujiname statistiką, jei laikas geresnis
            if (player->elapsedSeconds < leaderboard.players[i].elapsedSeconds && match->gameWon)
            {
                leaderboard.players[i].elapsedSeconds = player->elapsedSeconds;
            }
            leaderboard.players[i].gamesWon += match->gameWon ? 1 : 0;
            leaderboard.players[i].gamesPlayed++;
            leaderboard.players[i].winRate = ((float)leaderboard.players[i].gamesWon / leaderboard.players[i].gamesPlayed) * 100.0f;
            strncpy(leaderboard.players[i].lastPlayed, player->lastPlayed, sizeof(leaderboard.players[i].lastPlayed) - 1);
            return;
        }
    }

    if (leaderboard.playerCount >= MAX_PLAYERS)
    {
        fprintf(stderr, "Maximum amount of matches reached.\n");
        return;
    }
    // Pridedame naują žaidėją
    int i = leaderboard.playerCount;
    strcpy(leaderboard.players[i].ipAddress, player->ipAddress);
    leaderboard.players[i].elapsedSeconds = match->gameWon ? player->elapsedSeconds : 1000000000;
    leaderboard.players[i].gamesWon = match->gameWon ? 1 : 0;
    leaderboard.players[i].gamesPlayed = 1;
    leaderboard.players[i].winRate = leaderboard.players[i].gamesWon * 100.0f;
    strcpy(leaderboard.players[i].lastPlayed, player->lastPlayed);
    leaderboard.playerCount++;
}

int compare_players(const void *a, const void *b)
{
    const PlayerStats *playerA = (const PlayerStats *)a;
    const PlayerStats *playerB = (const PlayerStats *)b;
    return playerA->elapsedSeconds - playerB->elapsedSeconds;
}