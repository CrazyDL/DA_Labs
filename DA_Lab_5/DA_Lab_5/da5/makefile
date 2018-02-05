TARGET = da5
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o TSuffixTree.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TSuffixTree.o: TSuffixTree.cpp TSuffixTree.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp TSuffixTree.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
