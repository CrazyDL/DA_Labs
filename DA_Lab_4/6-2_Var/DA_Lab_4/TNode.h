#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class TNode {
public:
    TNode();
    TNode(const TNode& other) {
        suffLink = other.suffLink;
        exitLink = other.exitLink;
    }
    map<uint32_t, TNode*> child;
    TNode* suffLink;
    TNode* exitLink;
    bool leaf;
    vector<size_t> patSize;
};

void addPattern(TNode* root, vector<uint32_t>& pat, size_t patSize);
void processTrie(TNode* root, size_t maxLen);
void printTrie(TNode* node, size_t lvl);
void Search(TNode* root, vector< pair<int32_t, pair<size_t, size_t> > >& text, size_t patLen, size_t patCount);
void DeleteTrie(TNode* node);