#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_processor.h"
#include "table.h"

void execute_query(const char *query, Table *table) {
    if (strncmp(query, "INSERT", 6) == 0) {
        char *values = strdup(query + 7); // Skip "INSERT "
        char **row = malloc(table->num_columns * sizeof(char *));
        char *token = strtok(values, ",");
        int i = 0;
        while (token != NULL) {
            row[i++] = strdup(token);
            token = strtok(NULL, ",");
        }
        insert_row(table, row);
        free(values);
    } else if (strcmp(query, "SELECT *") == 0) {
        for (int i = 0; i < table->num_rows; i++) {
            for (int j = 0; j < table->num_columns; j++) {
                printf("%s ", table->rows[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Invalid query\n");
    }
}
