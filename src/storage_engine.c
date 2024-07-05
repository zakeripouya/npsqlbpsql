#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage_engine.h"

void write_data(const char *filename, char **data, int num_rows) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_rows; i++) {
        fprintf(file, "%s\n", data[i]);
    }

    fclose(file);
}

char **read_data(const char *filename, int *num_rows) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char **data = NULL;
    char buffer[256];
    *num_rows = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        data = realloc(data, (*num_rows + 1) * sizeof(char *));
        data[*num_rows] = strdup(buffer);
        (*num_rows)++;
    }

    fclose(file);
    return data;
}
