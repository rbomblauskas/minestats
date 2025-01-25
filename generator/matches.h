#ifndef MATCHES_H
#define MATCHES_H

#include "types.h"
#include <stdbool.h>

extern MatchData matchData;

void add_match(const PlayerStats *player, const MatchStats *match);

#endif
