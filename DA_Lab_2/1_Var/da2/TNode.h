#ifndef TNODE_H
#define TNODE_H

#include <string.h>

class TAVLtree;

class TNode {
    public:
        friend TAVLtree;
        TNode() : height(0) {};
        TNode(const char* str, unsigned long long val);
        int Height();
        int Balance();
        void FixHeight();
        ~TNode();
    private:
        char* key;
        unsigned long long value;
        int height;
        TNode* l;
        TNode* r;
};

#endif
