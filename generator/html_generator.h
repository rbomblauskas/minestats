#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <stdio.h>
#include "types.h"

void write_leaderboard_html_header(FILE *html_file);
void write_leaderboard_html_body(FILE *html_file);
void write_player_data(FILE *html_file, int rank, PlayerStats *player);
void write_leaderboard_html_footer(FILE *html_file);
void write_matches_html_header(FILE *html_file);
void write_matches_html_body(FILE *html_file);
void write_matches_data(FILE *html_file, int match_num, MatchStats *match);
void write_cell_with_board_content(FILE *html_file, bool is_bomb, bool is_flag, bool is_revealed, int mine_count);
void write_game_board(FILE *html_file, const bool *board_flat, const bool *revealed_flat, const bool *flags_flat, int size);
void write_match_board_page(FILE *html_file, MatchStats *match, int match_num);
void write_matches_html_footer(FILE *html_file);

#endif