#pragma once
#include "TVector.h"
#include "TSmartPointer.h"
#include "string.h"

class TElem {
public:
    TElem() : key(nullptr), value(0) {}
    ~TElem() { delete[] key;}
    TElem& operator=(const TElem& other){
        if(this != &other){
            key = new char[strlen(other.key) + 1];
            strcpy(key, other.key);
            value = other.value;
        }
        return *this;      
    }
    char* key;
    unsigned long long value;
};

class TBTree;

class TNode {
public:
    friend TBTree;
    TNode();
    TNode(const TNode& orig);
    TNode& operator=(const TNode& other);
private:
    bool leaf;
    TVector< TSmartPointer<TElem> > elem;
    TVector< TSmartPointer<TNode> > child;
};
