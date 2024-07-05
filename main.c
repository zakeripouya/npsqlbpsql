#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage_engine.h"
#include "table.h"
#include "query_processor.h"

void print_banner() {
    printf("========================================\n");
    printf("           npsqlbpsql Database          \n");
    printf("========================================\n");
    printf("Available Commands:\n");
    printf("  INSERT <values> - Insert a new row\n");
    printf("  SELECT *        - Select all rows\n");
    printf("  SAVE            - Save data to database.txt\n");
    printf("  LOAD            - Load data from database.txt\n");
    printf("  EXIT            - Exit the program\n");
    printf("========================================\n");
}

int main() {
    char *columns[] = {"id", "name", "age"};
    Table *table = create_table(columns, 3);

    print_banner();

    char input[256];
    while (1) {
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove trailing newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (strncmp(input, "INSERT", 6) == 0) {
            execute_query(input, table);
        } else if (strcmp(input, "SELECT *") == 0) {
            execute_query(input, table);
        } else if (strcmp(input, "SAVE") == 0) {
            char **data = malloc(table->num_rows * sizeof(char *));
            for (int i = 0; i < table->num_rows; i++) {
                data[i] = malloc(256 * sizeof(char));
                strcpy(data[i], table->rows[i][0]);
                for (int j = 1; j < table->num_columns; j++) {
                    strcat(data[i], ",");
                    strcat(data[i], table->rows[i][j]);
                }
            }
            write_data("database.txt", data, table->num_rows);

            for (int i = 0; i < table->num_rows; i++) {
                free(data[i]);
            }
            free(data);
            printf("Data saved to database.txt\n");
        } else if (strcmp(input, "LOAD") == 0) {
            int num_rows;
            char **loaded_data = read_data("database.txt", &num_rows);
            for (int i = 0; i < num_rows; i++) {
                char *row = strdup(loaded_data[i]);
                char *token = strtok(row, ",");
                char **row_data = malloc(table->num_columns * sizeof(char *));
                int j = 0;
                while (token != NULL) {
                    row_data[j++] = strdup(token);
                    token = strtok(NULL, ",");
                }
                insert_row(table, row_data);
                free(row);
                free(loaded_data[i]);
            }
            free(loaded_data);
            printf("Data loaded from database.txt\n");
        } else if (strcmp(input, "EXIT") == 0) {
            break;
        } else {
            printf("Invalid command. Try again.\n");
        }
    }

    // Free table rows
    for (int i = 0; i < table->num_rows; i++) {
        for (int j = 0; j < table->num_columns; j++) {
            free(table->rows[i][j]);
        }
        free(table->rows[i]);
    }
    free(table->rows);
    free(table);

    return 0;
}
