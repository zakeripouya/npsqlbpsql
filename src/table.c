#include <stdlib.h>
#include <string.h>
#include "table.h"

Table *create_table(char **column_names, int num_columns) {
    Table *table = malloc(sizeof(Table));
    table->column_names = column_names;
    table->num_columns = num_columns;
    table->rows = NULL;
    table->num_rows = 0;
    return table;
}

void insert_row(Table *table, char **row) {
    table->rows = realloc(table->rows, (table->num_rows + 1) * sizeof(char **));
    table->rows[table->num_rows] = row;
    table->num_rows++;
}
