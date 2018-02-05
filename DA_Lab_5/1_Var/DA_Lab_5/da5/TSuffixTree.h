#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

const char terminationChar = '$';

using namespace std;

class TSuffixTree;
class TNode {
public:
    friend TSuffixTree;
    TNode(TNode* link, int start, int* end) : TNode(link, start, end, -1) { }
    TNode(TNode* link, int start, int* end, int ind) : suffixLink(link), start(start), end(end), suffixIndex(ind) { }
private:
    map<char, TNode*> childs;
    TNode* suffixLink;
    int start;
    int *end;
    int suffixIndex;
};

class TSuffixTree{
public:
    TSuffixTree(string& text);
    void BuildSuffixTree();
    void PrintTree(TNode *node, int lvl);
    void Search(string& pat, int patNum);
    ~TSuffixTree();
private:
    void ExtendSuffixTree(int pos);
    void DeleteSuffixTree(TNode* node);
    void CountIndex(TNode* node, vector<int>& vec);
    int EdgeLength(TNode *node);

    TNode* root = new TNode(nullptr, -1, new int(-1));
    TNode *lastNewNode = nullptr;
    TNode *activeNode = nullptr;
    string text;
    int activeEdge = -1;
    int activeLength = 0;
    int remainingSuffCount = 0;
    int leafEnd = -1;
};