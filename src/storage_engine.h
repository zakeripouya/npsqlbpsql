#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

void write_data(const char *filename, char **data, int num_rows);
char **read_data(const char *filename, int *num_rows);

#endif
