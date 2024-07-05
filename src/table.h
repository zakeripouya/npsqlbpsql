#ifndef TABLE_H
#define TABLE_H

typedef struct {
    char **column_names;
    int num_columns;
    char ***rows;
    int num_rows;
} Table;

Table *create_table(char **column_names, int num_columns);
void insert_row(Table *table, char **row);

#endif
