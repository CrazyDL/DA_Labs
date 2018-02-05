TARGET = da4
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o TTrie.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TTrie.o: TTrie.cpp TTrie.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp TTrie.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
