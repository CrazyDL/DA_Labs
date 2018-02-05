#ifndef TAVLTREE_H
#define TAVLTREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "TNode.h"

class TAVLtree {
    public:
        TAVLtree();
        
        void Insert(const char* k, unsigned long long val);
        void DeleteNode(const char* k) ;
        void Search(const char* k);    
    
        void Serialization(const char* nameFile);
        int DeSerialization(const char* nameFile);

        ~TAVLtree();
    private:
        TNode *root;

        TNode* TurnRight(TNode* root);
        TNode* TurnLeft(TNode *root);
        TNode* Balancing(TNode *root);

        TNode* Insert(TNode* tree, const char* k, unsigned long long val);
        TNode* DeleteNode(TNode* tree, const char* k);
        TNode* DeleteMin(TNode* n, TNode*& min);
        void Search(TNode* n, const char* k);

        void DeleteTree(TNode* n);

        void Write( TNode* n, FILE* out );
        int Read( TNode* n, FILE* in );
};

#endif
