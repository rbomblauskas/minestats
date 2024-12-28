#include "html_generator.h"
#include <stdlib.h>
#include <string.h>

char *escape_html(const char *input)
{
    if (input == NULL)
    {
        return NULL;
    }

    size_t max_len = strlen(input) * 6 + 1;
    char *output = (char *)malloc(max_len);

    if (output == NULL)
    {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; input[i] != '\0'; i++)
    {
        switch (input[i])
        {
        case '&':
            strcpy(&output[j], "&amp;");
            j += 5;
            break;
        case '<':
            strcpy(&output[j], "&lt;");
            j += 4;
            break;
        case '>':
            strcpy(&output[j], "&gt;");
            j += 4;
            break;
        case '"':
            strcpy(&output[j], "&quot;");
            j += 6;
            break;
        case '\'':
            strcpy(&output[j], "&#39;");
            j += 5;
            break;
        default:
            output[j] = input[i];
            j++;
        }
    }
    output[j] = '\0';
    return output;
}

void write_leaderboard_html_header(FILE *html_file)
{
    fprintf(html_file, "<!DOCTYPE html>\n");
    fprintf(html_file, "<html lang=\"en\">\n");
    fprintf(html_file, "<head>\n");
    fprintf(html_file, "    <meta charset=\"UTF-8\">\n");
    fprintf(html_file, "    <title>Minesweeper - Leaderboard</title>\n");
    fprintf(html_file, "    <link rel=\"stylesheet\" href=\"style.css\">\n");
    fprintf(html_file, "</head>\n");
}

void write_leaderboard_html_body(FILE *html_file)
{
    fprintf(html_file, "<body>\n");
    fprintf(html_file, "    <nav class=\"navbar\">\n");
    fprintf(html_file, "        <div class=\"navbar-logo\">Minesweeper</div>\n");
    fprintf(html_file, "        <ul class=\"navbar-links\">\n");
    fprintf(html_file, "            <li><a href=\"/\">Play</a></li>\n");
    fprintf(html_file, "            <li><a href=\"/leaderboard.html\">Leaderboard</a></li>\n");
    // fprintf(html_file, "            <li><a href=\"/matches.html\">Matches</a></li>\n");
    fprintf(html_file, "        </ul>\n");
    fprintf(html_file, "    </nav>\n");
    fprintf(html_file, "    <div class=\"leaderboard-container\">\n");
    fprintf(html_file, "        <h1 class=\"leaderboard-title\">Top Players</h1>\n");
    fprintf(html_file, "        <div class=\"leaderboard-table-container\">\n");
    fprintf(html_file, "            <table class=\"leaderboard-table\">\n");
    fprintf(html_file, "                <thead>\n");
    fprintf(html_file, "                    <tr>\n");
    fprintf(html_file, "                        <th>Rank</th>\n");
    fprintf(html_file, "                        <th>IP Address</th>\n");
    fprintf(html_file, "                        <th>Best Time</th>\n");
    fprintf(html_file, "                        <th>Games Won</th>\n");
    fprintf(html_file, "                        <th>Win Rate</th>\n");
    fprintf(html_file, "                        <th>Last Played</th>\n");
    fprintf(html_file, "                    </tr>\n");
    fprintf(html_file, "                </thead>\n");
    fprintf(html_file, "                <tbody>\n");
}

void write_player_data(FILE *html_file, int rank, PlayerStats *player)
{
    char *escaped_timestamp = escape_html(player->lastPlayed);
    if (!escaped_timestamp)
    {
        return;
    }
    fprintf(html_file, "                    <tr>\n");
    fprintf(html_file, "                        <td><span class=\"rank\">%d</span></td>\n", rank);
    fprintf(html_file, "                        <td class=\"ip-address\">%s</td>\n", player->ipAddress);
    if (player->gamesWon == 0)
    {
        fprintf(html_file, "                        <td>No data</td>\n");
    }
    else
    {
        fprintf(html_file, "                        <td>%ds</td>\n", player->elapsedSeconds);
    }
    fprintf(html_file, "                        <td>%d</td>\n", player->gamesWon);
    fprintf(html_file, "                        <td>%.1f%%</td>\n", player->winRate);
    fprintf(html_file, "                        <td>%s</td>\n", escaped_timestamp);
    fprintf(html_file, "                    </tr>\n");
    free(escaped_timestamp);
}

void write_leaderboard_html_footer(FILE *html_file)
{
    fprintf(html_file, "                </tbody>\n");
    fprintf(html_file, "            </table>\n");
    fprintf(html_file, "        </div>\n");
    fprintf(html_file, "    </div>\n");
    fprintf(html_file, "</body>\n");
    fprintf(html_file, "</html>\n");
}