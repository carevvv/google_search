CC = gcc
CFLAGS = -I../structs/headers
DEPS = ../structs/headers/map.h ../structs/headers/compression.h ../structs/headers/trie.h ../structs/headers/list_str.h ../structs/headers/set.h ../structs/headers/temp_list.h

OBJ = searcher.o ../structs/src/map.o ../structs/src/compression.o ../structs/src/trie.o ../structs/src/list_str.o ../structs/src/set.o ../structs/src/temp_list.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

search.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o ../structs/src/*.o search.out
