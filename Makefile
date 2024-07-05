CC = gcc
CFLAGS = -Wall -Wextra -I./src

SRC = src/storage_engine.c src/table.c src/query_processor.c
OBJ = $(SRC:.c=.o)

all: npsqlbpsql

npsqlbpsql: $(OBJ) main.o
	$(CC) $(CFLAGS) -o npsqlbpsql $(OBJ) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

src/storage_engine.o: src/storage_engine.c src/storage_engine.h
src/table.o: src/table.c src/table.h
src/query_processor.o: src/query_processor.c src/query_processor.h src/table.h

clean:
	rm -f $(OBJ) main.o npsqlbpsql

.PHONY: clean
