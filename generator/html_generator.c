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
        {"/matches.html", "Matches", NULL}
    };
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
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
    table_cell_format(html_file, NULL, ALIGN_CENTER, "<span class=\"rank\">%d</span>", rank);
    table_cell(html_file, player->ipAddress, "ip-address", ALIGN_LEFT); 

    if (player->gamesWon == 0)
    {
        table_cell(html_file, "No data", NULL, ALIGN_LEFT);
    }
    else
    {
        table_cell_format(html_file, NULL, ALIGN_LEFT, "%ds", player->elapsedSeconds);
    }
    table_cell_number(html_file, player->gamesWon, 0, NULL, ALIGN_LEFT);

    char win_rate[32];
    snprintf(win_rate, sizeof(win_rate), "%.1f%%", player->winRate);
    table_cell(html_file, win_rate, NULL, ALIGN_LEFT);

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

void write_matches_html_header(FILE *html_file)
{
    html_document_begin(html_file, "Minesweeper - Matches", "style.css");
}

void write_matches_html_body(FILE *html_file)
{
    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL},
        {"/matches.html", "Matches", NULL}
    };
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, "leaderboard-container", NULL);
    h1_gen(html_file, "All Matches", "leaderboard-title");
    div_begin(html_file, "leaderboard-table-container", NULL);

    TableColumn columns[] = {
        {"Game Won", NULL, ALIGN_LEFT},
        {"Board Size", NULL, ALIGN_LEFT},
        {"Mine Percentage", NULL, ALIGN_LEFT},
        {"Time Stamp", NULL, ALIGN_LEFT},
        {"View Board", NULL, ALIGN_LEFT},
    };
    TableConfig tableConfig = {"leaderboard-table", "leaderboard-table", NULL, false, false, false};

    table_begin(html_file, &tableConfig);
    table_header(html_file, columns, sizeof(columns) / sizeof(columns[0]));

    table_row_begin(html_file);
}

void write_matches_data(FILE *html_file, int rank, MatchStats *match)
{
    char *escaped_timestamp = html_escape(match->timestamp);
    if (!escaped_timestamp)
    {
        return;
    }
    table_cell(html_file, match->gameWon ? "Won" : "Lost", NULL, ALIGN_LEFT); 
    table_cell_number(html_file, match->boardSize, 0, NULL, ALIGN_LEFT);

    char mine_percentage[32];
    snprintf(mine_percentage, sizeof(mine_percentage), "%.1f%%", match->minePercentage);
    table_cell(html_file, mine_percentage, NULL, ALIGN_LEFT);
   
    table_cell(html_file, escaped_timestamp, NULL, ALIGN_LEFT);

    // Create a link to the individual match board view
    fprintf(html_file, "<td><a href='match%d.html' class='board-button'>View Board</a></td>", rank);

    free(escaped_timestamp);
    table_row_end(html_file);

    // Generate individual match page
    char filename[32];
    snprintf(filename, sizeof(filename), "../frontend/match%d.html", rank);
    FILE* match_file = fopen(filename, "w");
    
    if (match_file) {
        write_match_board_page(match_file, match, rank);
        fclose(match_file);
    }
}

void write_match_board_page(FILE *html_file, MatchStats *match, int rank)
{
    html_document_begin(html_file, "Minesweeper - Match Board", "style.css");
    
    NavbarItem navbarItems[] = {
        {"/", "Play", NULL},
        {"/leaderboard.html", "Leaderboard", NULL},
        {"/matches.html", "Matches", NULL}
    };
    NavbarConfig navbarConfig = {"navbar", "navbar", "Minesweeper", "navbar-logo", navbarItems, 3};
    navbar_gen(html_file, &navbarConfig);

    div_begin(html_file, "game-container", NULL);
    
    fprintf(html_file, "<div id='game-status' style='padding-top: 80px; font-size: 1.8rem;'>");
    char title[64];
    snprintf(title, sizeof(title), "Match #%d - %s", rank, match->gameWon ? "Won" : "Lost");
    h1_gen(html_file, title, NULL);
    div_end(html_file);

    // Convert bool arrays to strings
    char board_str[BOARD_SIZE * 2 + 1] = {0};
    char revealed_str[BOARD_SIZE * 2 + 1] = {0};
    char flags_str[BOARD_SIZE * 2 + 1] = {0};

    for (int i = 0; i < BOARD_SIZE; i++) {
        strcat(board_str, match->boardFlat[i] ? "1" : "0");
        strcat(revealed_str, match->revealedFlat[i] ? "1" : "0");
        strcat(flags_str, match->flagsFlat[i] ? "1" : "0");
    }

    // Add the board visualization script
    fprintf(html_file, "<script>\n");
    fprintf(html_file, "function visualizeBoard(boardFlat, revealedFlat, flagsFlat, size) {\n");
    fprintf(html_file, "    const board = document.createElement('table');\n");
    fprintf(html_file, "    board.id = 'gameBoard';\n");
    fprintf(html_file, "    for (let i = 0; i < size; i++) {\n");
    fprintf(html_file, "        const row = document.createElement('tr');\n");
    fprintf(html_file, "        for (let j = 0; j < size; j++) {\n");
    fprintf(html_file, "            const cell = document.createElement('td');\n");
    fprintf(html_file, "            const index = i * size + j;\n");
    fprintf(html_file, "            if (flagsFlat[index] === '1') {\n");
    fprintf(html_file, "                cell.textContent = '🚩';\n");
    fprintf(html_file, "                cell.classList.add('flag');\n");
    fprintf(html_file, "            } else if (boardFlat[index] === '1') {\n");
    fprintf(html_file, "                cell.textContent = '💣';\n");
    fprintf(html_file, "                cell.classList.add('mine');\n");
    fprintf(html_file, "            } else if (revealedFlat[index] === '1') {\n");
    fprintf(html_file, "                cell.classList.add('revealed');\n");
    fprintf(html_file, "                let mineCount = 0;\n");
    fprintf(html_file, "                for (let di = -1; di <= 1; di++) {\n");
    fprintf(html_file, "                    for (let dj = -1; dj <= 1; dj++) {\n");
    fprintf(html_file, "                        const ni = i + di;\n");
    fprintf(html_file, "                        const nj = j + dj;\n");
    fprintf(html_file, "                        if (ni >= 0 && ni < size && nj >= 0 && nj < size) {\n");
    fprintf(html_file, "                            if (boardFlat[ni * size + nj] === '1') mineCount++;\n");
    fprintf(html_file, "                        }\n");
    fprintf(html_file, "                    }\n");
    fprintf(html_file, "                }\n");
    fprintf(html_file, "                if (mineCount > 0) {\n");
    fprintf(html_file, "                    cell.textContent = mineCount;\n");
    fprintf(html_file, "                    cell.classList.add(`number${mineCount}`);\n");
    fprintf(html_file, "                }\n");
    fprintf(html_file, "            } else {\n");
    fprintf(html_file, "                cell.style.backgroundColor = 'rgba(255, 255, 255, 0.7)';\n");
    fprintf(html_file, "            }\n");
    fprintf(html_file, "            row.appendChild(cell);\n");
    fprintf(html_file, "        }\n");
    fprintf(html_file, "        board.appendChild(row);\n");
    fprintf(html_file, "    }\n");
    fprintf(html_file, "    return board;\n");
    fprintf(html_file, "}\n");
    fprintf(html_file, "</script>\n");

    // Create the board
    fprintf(html_file, "<div id='board' style='display: flex; justify-content: center;'></div>");
    fprintf(html_file, "<script>document.getElementById('board').appendChild(visualizeBoard('%s', '%s', '%s', %d));</script>", 
        board_str, revealed_str, flags_str, (int)sqrt(BOARD_SIZE));

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