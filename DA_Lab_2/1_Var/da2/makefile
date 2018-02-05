PROJECT = da2
OBJ = main.o TNode.o TAVLtree.o
CC = g++ -std=c++11

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CC) -o $@ $< TNode.o TAVLtree.o

main.o: main.cpp TAVLtree.h TNode.h
	$(CC)  -c $<

TAVLtree.o: TAVLtree.cpp TAVLtree.h TNode.h
	$(CC)  -c $<

TNode.o : TNode.cpp TNode.h
	$(CC)  -c $<

clean:
	rm -f *.o $(PROJECT)