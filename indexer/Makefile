CC = gcc
CFLAGS = -I../structs/headers
DEPS = ../structs/headers/map.h ../structs/headers/compression.h ../structs/headers/trie.h ../structs/headers/list_str.h ../structs/headers/set.h
OBJ = indexer.o ../structs/src/map.o ../structs/src/compression.o ../structs/src/trie.o ../structs/src/list_str.o ../structs/src/set.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

a.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o ../structs/src/*.o a.out

