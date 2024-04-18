TARGET=main
OBJ=list_str
OBJ2=map
CC=gcc
MAINDIR=./
SRCDIR=./src/
BINDIR=./bin/
HEADDIR=./headers/
FLAGS = -Wall -iquote $(HEADDIR)

all: $(TARGET).out

$(TARGET).out: $(TARGET).o $(BINDIR)lib$(OBJ).so $(BINDIR)lib$(OBJ2).so
		$(CC) $< -L$(BINDIR) -o $@ -l$(OBJ) -l$(OBJ2)

$(TARGET).o: $(MAINDIR)$(TARGET).c
		$(CC) -c $< -o $@ $(FLAGS)

#string list
$(BINDIR)lib$(OBJ).so: $(SRCDIR)$(OBJ).c 
		$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ).c: $(HEADDIR)$(OBJ).h

#map
$(BINDIR)lib$(OBJ2).so: $(SRCDIR)$(OBJ2).c $(SRCDIR)$(OBJ).c
		$(CC) -c --shared $< -o $@ $(FLAGS)

$(SRCDIR)$(OBJ2).c: $(HEADDIR)$(OBJ2).h $(HEADDIR)$(OBJ).h


run: all
		./$(TARGET).out
