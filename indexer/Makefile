CC = gcc
DIR_SRC = ./src
DIR_BIN = ./bin
DIR_HEAD = ./headers
CFLAGS = -Wall -fPIC

all: main.out

main.out: main.o $(DIR_BIN)/libsearch.so
	$(CC) $(CFLAGS) -o $@ $< -L$(DIR_BIN) -lsearch -Wl,-rpath,$(DIR_BIN)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_SRC)/compression.o: $(DIR_SRC)/compression.c $(DIR_HEAD)/compression.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_SRC)/trie.o: $(DIR_SRC)/trie.c $(DIR_HEAD)/trie.h
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/libsearch.so: $(DIR_SRC)/trie.o $(DIR_SRC)/compression.o
	$(CC) $(CFLAGS) -shared -o $@ $^


clean:
	rm -f $(DIR_SRC)/*.o *.o *.out $(DIR_BIN)/*.so
