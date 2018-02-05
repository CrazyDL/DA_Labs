TARGET = da4
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o TNode.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TNode.o: TNode.cpp TNode.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp TNode.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
