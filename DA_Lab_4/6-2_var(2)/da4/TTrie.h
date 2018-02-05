#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class TTrie;
class TNode {
public:
    friend TTrie;
    TNode() : failLink(nullptr), exitLink(nullptr), leaf(false) {}
    TNode(const TNode& other) {
        failLink = other.failLink;
        exitLink = other.exitLink;
    }
private:
    map<unsigned int, TNode*> childs;
    TNode* failLink;
    TNode* exitLink;
    bool leaf;
    vector<int> patNum;
};

class TTrie {
public:
    TTrie();
    void AddPat(vector<unsigned int>& pat, int num);
    void ProcessTrie(int len);
    void Search(vector<int>& text, vector<pair<int, int>>& pos, int patLen, int patCount);
    void DeleteTrie(TNode* node);
    ~TTrie();
private:
    TNode* root;

    void ProcessNode(TNode* node, int lvl);
};
