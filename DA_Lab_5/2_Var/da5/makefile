TARGET = da5
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o TSufArray.o TSufTree.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TSufArray.o: TSufArray.cpp TSufArray.h TSufTree.h
	$(CC) $(FLAGS) -c $< -o $@
TSufTree.o: TSufTree.cpp TSufTree.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp TSufArray.h TSufTree.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@