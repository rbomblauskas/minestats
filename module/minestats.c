#include <stdio.h>
#include <stdlib.h>
#include "leaderboard.h"
#include "html_generator.h"
#include "types.h"
#include "minestats.h"
#include "csv_parser.h"


void initialize_minestats()
{
    leaderboard.players = malloc(sizeof(PlayerStats) * MAX_PLAYERS);
    if (!leaderboard.players)
    {
        fprintf(stderr, "Failed to allocate memory for leaderboard.\n");
        exit(1);
    }
    leaderboard.playerCount = 0;
}

void parse_csv_file(const char *filename)
{
    struct csv_parser parser;
    csv_init(&parser, CSV_STRICT);

    FILE *csv_file = fopen(filename, "r");
    if (!csv_file)
    {
        fprintf(stderr, "Failed to open input file\n");
        exit(1);
    }

    char buf[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buf, 1, sizeof(buf), csv_file)) > 0)
    {
        csv_parse(&parser, buf, bytes_read, cb_field, cb_row, NULL);
    }

    csv_fini(&parser, cb_field, cb_row, NULL);
    fclose(csv_file);
    csv_free(&parser);

    // Naudojame qsort, kad surikiuoti žaidėjus pagal atlikimo laiką
    qsort(leaderboard.players, leaderboard.playerCount, sizeof(PlayerStats), compare_players);
}

void generate_leaderboard_html(const char *filename)
{
    FILE *html_file = fopen(filename, "w");
    if (!html_file)
    {
        fprintf(stderr, "Failed to open output file\n");
        exit(1);
    }

    write_leaderboard_html_header(html_file);
    write_leaderboard_html_body(html_file);

    // Įrašome žaidėjų duomenis
    for (int i = 0; i < leaderboard.playerCount; i++)
    {
        write_player_data(html_file, i + 1, &leaderboard.players[i]);
    }

    write_leaderboard_html_footer(html_file);
    fclose(html_file);
}

void cleanup_minestats()
{
    free(leaderboard.players);
}
