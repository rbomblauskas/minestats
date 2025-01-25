#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "types.h"

extern LeaderboardData leaderboard;

void update_player_stats(const PlayerStats *player, const MatchStats *match);
int compare_players(const void *a, const void *b);

#endif