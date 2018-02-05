#pragma once
#include "TNode.h"
#include "TSmartPointer.h"

enum Errors
{
    EXIST = -2,
    NOT_FOUND,
    OK,
    MEMORY_ERROR,
    FILE_ERROR,
    DESERIALIZATION_ERROR,
    JUST_RETURN
};

class TBTree {
public:

    TBTree(size_t t);
    TSmartPointer<TNode>& GetRoot();
    int Insert(TSmartPointer<TElem>& elem);
    int Search(TSmartPointer<TNode>& node, char* key);
    int Delete(char* key);
    int Serialization(char* fileName);
    int DeSerialization(char* fileName);
    void PrintTree(TSmartPointer<TNode>& node, size_t lvl, size_t k);
private:
    TSmartPointer<TNode> root;
    size_t t;

    void WriteNode(FILE* in, TSmartPointer<TNode>& node);
    int ReadNode(FILE* in, TSmartPointer<TNode>& node);
    int SplitTree(TSmartPointer<TNode>& node, int i);
    int InsertNonFull(TSmartPointer<TNode>& node, TSmartPointer<TElem>& elem);
    int DelInLeaf(TSmartPointer<TNode>& node, int i, char* key);
    int DelInNode(TSmartPointer<TNode>& node, int i, char* key);
    int DeleteNonEmpty(TSmartPointer<TNode>& node, char* key);
    int MergeTree(TSmartPointer<TNode>& node, int& i);
};
