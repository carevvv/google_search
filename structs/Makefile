TARGET=decompress_test
OBJ=list_str
OBJ2=map
OBJ3=set
OBJ4=trie
OBJ5=compression
CC=gcc
MAINDIR=./
SRCDIR=./src/
BINDIR=./bin/
HEADDIR=./headers/
FLAGS = -Wall -iquote $(HEADDIR)

all: $(TARGET).out

$(TARGET).out: $(TARGET).o \
	$(BINDIR)lib$(OBJ).so \
	$(BINDIR)lib$(OBJ2).so \
	$(BINDIR)lib$(OBJ3).so \
	$(BINDIR)lib$(OBJ4).so \
	$(BINDIR)lib$(OBJ5).so
	$(CC) $< -L$(BINDIR) -o $@ -l$(OBJ) -l$(OBJ2) -l$(OBJ3) -l$(OBJ4) -l$(OBJ5)

$(TARGET).o: $(MAINDIR)$(TARGET).c
	$(CC) -c $< -o $@ $(FLAGS)

# string list
$(BINDIR)lib$(OBJ).so: $(SRCDIR)$(OBJ).c 
	$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ).c: $(HEADDIR)$(OBJ).h

# map
$(BINDIR)lib$(OBJ2).so: $(SRCDIR)$(OBJ2).c $(SRCDIR)$(OBJ).c
	$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ2).c: $(HEADDIR)$(OBJ2).h $(HEADDIR)$(OBJ).h

# set
$(BINDIR)lib$(OBJ3).so: $(SRCDIR)$(OBJ3).c
	$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ3).c: $(HEADDIR)$(OBJ3).h

# trie
$(BINDIR)lib$(OBJ4).so: $(SRCDIR)$(OBJ4).c
	$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ4).c: $(HEADDIR)$(OBJ4).h

# compression
$(BINDIR)lib$(OBJ5).so: $(SRCDIR)$(OBJ5).c
	$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ5).c: $(HEADDIR)$(OBJ5).h

run: all
	./$(TARGET).out
