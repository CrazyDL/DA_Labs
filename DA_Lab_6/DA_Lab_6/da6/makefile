TARGET = da6
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o TBigUInt.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

TBigUInt.o: TBigUInt.cpp TBigUInt.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp TBigUInt.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
