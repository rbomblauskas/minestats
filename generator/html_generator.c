#include "html_generator.h"
#include <stdlib.h>
#include <string.h>
#include "enigma_html.c"

void write_leaderboard_html_header(FILE *html_file)
{
    html_document_begin(html_file, "Minesweeper - Leaderboard", "style.css");
}

void write_leaderboard_html_body(FILE *html_file)
{
    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL}
    };
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 2};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, "leaderboard-container", NULL);
    h1_gen(html_file, "Top Players", "leaderboard-title");
    div_begin(html_file, "leaderboard-table-container", NULL);

    TableColumn columns[] = {
        {"Rank", NULL, ALIGN_LEFT},
        {"IP Address", NULL, ALIGN_LEFT},
        {"Best Time", NULL, ALIGN_LEFT},
        {"Games Won", NULL, ALIGN_LEFT},
        {"Win Rate", NULL, ALIGN_LEFT},
        {"Last Played", NULL, ALIGN_LEFT}
    };
    TableConfig tableConfig = {"leaderboard-table", "leaderboard-table", NULL, false, false, false};

    table_begin(html_file, &tableConfig);
    table_header(html_file, columns, sizeof(columns) / sizeof(columns[0]));

    table_row_begin(html_file);
}

void write_player_data(FILE *html_file, int rank, PlayerStats *player)
{
    char *escaped_timestamp = html_escape(player->lastPlayed);
    if (!escaped_timestamp)
    {
        return;
    }
    table_cell(html_file, rank, NULL, ALIGN_LEFT);
    table_cell(html_file, player->ipAddress, NULL, ALIGN_LEFT); 

    if (player->gamesWon == 0)
    {
        table_cell(html_file, "No data", NULL, ALIGN_LEFT);
    }
    else
    {
        table_cell(html_file, player->elapsedSeconds, NULL, ALIGN_LEFT);
    }
    table_cell(html_file, player->gamesWon, NULL, ALIGN_LEFT);
    table_cell_number(html_file, player->winRate, 1, NULL, ALIGN_LEFT);
    table_cell(html_file, escaped_timestamp, NULL, ALIGN_LEFT);

    free(escaped_timestamp);
    table_row_end(html_file);
}

void write_leaderboard_html_footer(FILE *html_file)
{
    table_end(html_file);
    div_end(html_file);
    div_end(html_file);
    html_document_end(html_file);
}
