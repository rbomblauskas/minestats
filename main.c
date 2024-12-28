#include "csv_parser.h"
#include "leaderboard.h"
#include "html_generator.h"
#include "types.h"
#include "minestats.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input.csv> <output.html>\n", argv[0]);
        return 1;
    }

    initialize_minestats();
    parse_csv_file(argv[1]);
    generate_leaderboard_html(argv[2]);
    cleanup_minestats();

    return 0;
}