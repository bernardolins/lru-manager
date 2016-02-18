BINARY=lrumr
CC=gcc

SRC=src
BIN=bin
INC=inc
OBJ=obj

INCCMD=-I$(INC)
FLAGS=-Wall -pthread

OBJS=$(OBJ)/main.o $(OBJ)/lru.o $(OBJ)/mem.o $(OBJ)/tab.o

build: clean setup $(OBJS)
	$(CC) -o $(BIN)/$(BINARY) $(OBJS) $(INCCMD) $(FLAGS)

setup:
	mkdir -p obj
	mkdir -p bin

clean:
	rm -rf $(OBJ) $(BIN)/*
	mkdir $(OBJ)

$(OBJ)/main.o:
	$(CC) -o $(OBJ)/main.o -c $(SRC)/main.c $(INCCMD) $(FLAGS)

$(OBJ)/lru.o:
	$(CC) -o $(OBJ)/lru.o -c $(SRC)/lru.c $(INCCMD) $(FLAGS)

$(OBJ)/mem.o:
	$(CC) -o $(OBJ)/mem.o -c $(SRC)/mem.c $(INCCMD) $(FLAGS)

$(OBJ)/tab.o:
	$(CC) -o $(OBJ)/tab.o -c $(SRC)/tab.c $(INCCMD) $(FLAGS)
