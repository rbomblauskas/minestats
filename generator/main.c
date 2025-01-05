#include "csv_parser.h"
#include "leaderboard.h"
#include "html_generator.h"
#include "types.h"
#include "minestats.h"
#include <string.h>
#include <stdbool.h>

void print_usage(const char *program_name)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  Generate both matches and leaderboard:\n");
    fprintf(stderr, "    %s <matches.csv> <output_directory>\n", program_name);
    fprintf(stderr, "  Generate matches only:\n");
    fprintf(stderr, "    %s -m <matches.csv> <output_location>\n", program_name);
    fprintf(stderr, "  Generate leaderboard only:\n");
    fprintf(stderr, "    %s -l <matches.csv> <output_location>\n", program_name);
}

int main(int argc, char *argv[])
{
    const char *input_file = NULL;
    const char *output_location = NULL;
    bool generate_matches = false;
    bool generate_leaderboard = false;

    if (argc == 3)
    {
        input_file = argv[1];
        output_location = argv[2];
        generate_matches = true;
        generate_leaderboard = true;
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-m") == 0)
        {
            generate_matches = true;
        }
        else if (strcmp(argv[1], "-l") == 0)
        {
            generate_leaderboard = true;
        }
        else
        {
            print_usage(argv[0]);
            return 1;
        }
        input_file = argv[2];
        output_location = argv[3];
    }
    else
    {
        print_usage(argv[0]);
        return 1;
    }

    initialize_minestats();

    parse_csv_file(input_file);

    if (generate_leaderboard)
    {
        generate_leaderboard_html(output_location);
    }

    if (generate_matches)
    {
        char matches_path[MAX_FILE_PATH_SIZE];
        snprintf(matches_path, sizeof(matches_path), "%s/matches.html", output_location);
        generate_matches_html(matches_path);
        generate_individual_matches_html(output_location);
    }

    cleanup_minestats();
    return 0;
}