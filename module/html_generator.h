#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <stdio.h>
#include "types.h"

void write_leaderboard_html_header(FILE *html_file);
void write_leaderboard_html_body(FILE *html_file);
void write_player_data(FILE *html_file, int rank, PlayerStats *player);
void write_leaderboard_html_footer(FILE *html_file);

#endif