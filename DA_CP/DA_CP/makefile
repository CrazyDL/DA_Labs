TARGET = DA_CP
CC=g++
FLAGS = -std=c++17 -Wall -pedantic -o2

OBJ = main.o TAudioSearch.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TAudioSearch.o: TAudioSearch.cpp TAudioSearch.h
	$(CC) $(FLAGS) -c $< -o $@ 
main.o: main.cpp TAudioSearch.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -L. -lmpg123
