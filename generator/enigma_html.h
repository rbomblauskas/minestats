#ifndef ENIGMA_HTML_H
#define ENIGMA_HTML_H

#include <stdio.h>
#include <stdbool.h>

typedef enum
{
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_NONE
} ColumnAlignment;

typedef struct
{
    const char *header;
    const char *css_class;
    ColumnAlignment align;
} TableColumn;

typedef struct
{
    const char *table_id;
    const char *css_class;
    const char *caption;
    bool striped;
    bool hoverable;
    bool bordered;
} TableConfig;

typedef struct
{
    const char *link;
    const char *label;
    const char *css_class;
} NavbarItem;

typedef struct
{
    const char *navbar_id;
    const char *css_class;
    const char *logo_text;
    const char *logo_css_class;
    NavbarItem *items;
    int num_items;
} NavbarConfig;

// Write the opening of the HTML document and head
void html_document_begin(FILE *fp, const char *title, const char *css_file);

// Write the closing of the HTML document
void html_document_end(FILE *fp);

// Generates the navigation bar
void navbar_gen(FILE *fp, const NavbarConfig *config);

// Begin a new div with optional CSS class
void div_begin(FILE *fp, const char *css_class, const char *id);

// End the current div
void div_end(FILE *fp);

// Generates an h1 header.
void h1_gen(FILE *fp, const char *title, const char *css_class);

// Generates an h1 header with format
void h1_gen_format(FILE *fp, const char *css_class, const char *format, ...);

// Initialize a new table with given configuration
void table_begin(FILE *fp, const TableConfig *config);

// Write table header with column definitions
void table_header(FILE *fp, const TableColumn columns[], int num_columns);

// Begin a new table row
void table_row_begin(FILE *fp);

// Write a cell with text content
void table_cell(FILE *fp, const char *content, const char *css_class, ColumnAlignment align);

// Function to format and directly write a table cell
void table_cell_format(FILE *fp, const char *css_class, ColumnAlignment align, const char *format, ...);

// Write a cell with numeric content
void table_cell_number(FILE *fp, double number, int decimals, const char *css_class, ColumnAlignment align);

// End current table row
void table_row_end(FILE *fp);

// End the table
void table_end(FILE *fp);

// Initialize a new list
void list_begin(FILE *fp, const char *css_class);

// End the list
void list_end(FILE *fp);

// Write a list item with text content
void list_item(FILE *fp, const char *content, const char *css_class);

// Converts an ISO 8601 timestamp to a human-readable format. The result does not need to be freed.
char *format_timestamp(const char *iso_timestamp);

// Escape HTML special characters in a string. Caller must free the result.
char *html_escape(const char *input);

#endif