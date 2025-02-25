#include "html_generator.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "enigma_html.h"

void write_leaderboard_html_header(FILE *html_file)
{
    html_document_begin(html_file, "Minesweeper - Leaderboard", "style.css");
}

void write_leaderboard_html_body(FILE *html_file)
{
    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL},
        {"/matches.html", "Matches", NULL}};
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, "leaderboard-container", NULL);
    h1_gen(html_file, "Top Players", "leaderboard-title");
    div_begin(html_file, "leaderboard-table-container", NULL);

    TableColumn columns[] = {
        {"Rank", NULL, ALIGN_LEFT},
        {"Name", NULL, ALIGN_LEFT},
        {"Best Time", NULL, ALIGN_LEFT},
        {"Games Won", NULL, ALIGN_LEFT},
        {"Win Rate", NULL, ALIGN_LEFT},
        {"Last Played", NULL, ALIGN_LEFT}};
    TableConfig tableConfig = {"leaderboard-table", "leaderboard-table", NULL, false, false, false};

    table_begin(html_file, &tableConfig);
    table_header(html_file, columns, sizeof(columns) / sizeof(columns[0]));

    table_row_begin(html_file);
}

void write_player_data(FILE *html_file, int rank, PlayerStats *player)
{
    table_cell_format(html_file, NULL, ALIGN_CENTER, "<span class=\"rank\">%d</span>", rank);

    table_cell(html_file, player->playerName, "player-name", ALIGN_LEFT);

    if (player->gamesWon == 0)
    {
        table_cell(html_file, "No data", NULL, ALIGN_LEFT);
    }
    else
    {
        table_cell_format(html_file, NULL, ALIGN_LEFT, "%ds", player->elapsedSeconds);
    }
    table_cell_number(html_file, player->gamesWon, 0, NULL, ALIGN_LEFT);

    table_cell_format(html_file, NULL, ALIGN_LEFT, "%.1f%%", player->winRate);

    table_cell(html_file, format_timestamp(player->lastPlayed), NULL, ALIGN_LEFT);

    table_row_end(html_file);
}

void write_leaderboard_html_footer(FILE *html_file)
{
    table_end(html_file);
    div_end(html_file);
    div_end(html_file);
    html_document_end(html_file);
}

void write_matches_html_header(FILE *html_file)
{
    html_document_begin(html_file, "Minesweeper - Matches", "style.css");
}

void write_matches_html_body(FILE *html_file)
{
    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL},
        {"/matches.html", "Matches", NULL}};
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, "leaderboard-container", NULL);
    h1_gen(html_file, "All Matches", "leaderboard-title");
    div_begin(html_file, "leaderboard-table-container", NULL);

    TableColumn columns[] = {
        {"Game Won", NULL, ALIGN_LEFT},
        {"Name", NULL, ALIGN_LEFT},
        {"Time Stamp", NULL, ALIGN_LEFT},
        {"View Board", NULL, ALIGN_LEFT},
    };
    TableConfig tableConfig = {"leaderboard-table", "leaderboard-table", NULL, false, false, false};

    table_begin(html_file, &tableConfig);
    table_header(html_file, columns, sizeof(columns) / sizeof(columns[0]));

    table_row_begin(html_file);
}

void write_matches_data(FILE *html_file, int match_num, MatchStats *match)
{
    table_cell(html_file, match->gameWon ? "Won" : "Lost", NULL, ALIGN_LEFT);
    table_cell(html_file, match->playerName, NULL, ALIGN_LEFT);
    table_cell(html_file, format_timestamp(match->timestamp), NULL, ALIGN_LEFT);
    table_cell_format(html_file, NULL, ALIGN_LEFT, "<a href='match%d.html' class='board-button'>View Board</a>", match_num);

    table_row_end(html_file);
}

void write_cell_with_board_content(FILE *html_file, bool is_bomb, bool is_flag, bool is_revealed, int mine_count)
{
    if (is_flag)
    {
        table_cell(html_file, "\xF0\x9F\x9A\xA9", "flag", ALIGN_CENTER);
    }
    else if (is_bomb)
    {
        table_cell(html_file, "\xF0\x9F\x92\xA3", "mine", ALIGN_CENTER);
    }
    else if (is_revealed)
    {
        if (mine_count > 0)
        {
            table_cell_format(html_file, "revealed", ALIGN_CENTER, "%d", mine_count);
        }
        else
        {
            table_cell(html_file, "", "revealed", ALIGN_CENTER);
        }
    }
    else
    {
        table_cell(html_file, "", "unrevealed", ALIGN_CENTER);
    }
}

void write_game_board(FILE *html_file, const bool *board_flat, const bool *revealed_flat, const bool *flags_flat, int size)
{
    TableConfig boardConfig = {"gameBoard", NULL, NULL, false, false, false};
    table_begin(html_file, &boardConfig);
    for (int i = 0; i < size; i++)
    {
        table_row_begin(html_file);
        for (int j = 0; j < size; j++)
        {
            int index = i * size + j;
            int mine_count = 0;
            if (revealed_flat[index])
            {
                for (int di = -1; di <= 1; di++)
                {
                    for (int dj = -1; dj <= 1; dj++)
                    {
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < size && nj >= 0 && nj < size)
                        {
                            if (board_flat[ni * size + nj])
                                mine_count++;
                        }
                    }
                }
            }
            write_cell_with_board_content(html_file, board_flat[index], flags_flat[index], revealed_flat[index], mine_count);
        }
        table_row_end(html_file);
    }
    table_end(html_file);
}

void write_match_board_page(FILE *html_file, MatchStats *match, int match_num)
{
    html_document_begin(html_file, "Minesweeper - Match Board", "style.css");

    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL},
        {"/matches.html", "Matches", NULL}};
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, NULL, "game-container");

    h1_gen_format(html_file, "gameboard-title", "Match #%d - %s", match_num, match->gameWon ? "Won" : "Lost");

    // Create the board
    write_game_board(html_file, match->boardFlat, match->revealedFlat, match->flagsFlat, BOARD_SIZE);

    div_end(html_file);
    html_document_end(html_file);
}

void write_matches_html_footer(FILE *html_file)
{
    table_end(html_file);
    div_end(html_file);
    div_end(html_file);
    html_document_end(html_file);
}