#include "TTrie.h"

TTrie::TTrie() : root(new TNode()) {}

void TTrie::AddPat(vector<unsigned int>& pat, int num) {
    TNode* cur = root;
    for (auto it : pat) {
        if (cur->childs.find(it) == cur->childs.end())
            cur->childs.insert(make_pair(it, new TNode()));
        cur = cur->childs.find(it)->second;
    }
    cur->leaf = true;
    cur->patNum.push_back(num);
}

void TTrie::ProcessNode(TNode* node, int lvl) {
    if (lvl != 1)
        for (auto it : node->childs)
            ProcessNode(it.second, lvl - 1);
    else
        for (auto it : node->childs) {
            TNode* link = node->failLink;
            auto find = link->childs.find(it.first);
            while (link != root && find == link->childs.end()) {
                link = link->failLink;
                find = link->childs.find(it.first);
            }
            if (find != link->childs.end()) {
                it.second->failLink = find->second;
                link = find->second;
                if (link->leaf)
                    it.second->exitLink = link;
                else if (link->exitLink)
                    it.second->exitLink = link->exitLink;

            }
            else
                it.second->failLink = root;
        }
}

void TTrie::ProcessTrie(int len) {
    root->failLink = root;
    for (auto it : root->childs)
        it.second->failLink = root;
    for (int i = 1; i < len; i++)
        for (auto it : root->childs)
            ProcessNode(it.second, i);
}

void TTrie::Search(vector<int>& text, vector<pair<int, int>>& pos, int patLen, int patCount){
    int textLen = text.size();
    vector<int> ind(textLen, 0);
    TNode* cur = root;
    TNode* link;
    for (int i = 0; i < textLen; i++) {
        auto find = cur->childs.find(text[i]);
        if (find == cur->childs.end()) {
            cur = cur->failLink;
            find = cur->childs.find(text[i]);
            while (cur->failLink != root && find == cur->childs.end()) {
                cur = cur->failLink;
                find = cur->childs.find(text[i]);
            }
            if (find != cur->childs.end())
                cur = find->second;
            else cur = root;
        }
        else
            cur = find->second;
        if (cur->leaf)
            for (auto it : cur->patNum)
                if (i - it + 1 >= 0)
                    ind[i - it + 1]++;
        link = cur->exitLink;
        while (link) {
            for (auto it : link->patNum)
                if (i - it + 1 >= 0)
                    ind[i - it + 1]++;
            link = link->exitLink;
        }
        if (cur->childs.empty()) {
            if (cur->exitLink)
                cur = cur->exitLink;
            else
                cur = cur->failLink;
        }
    }
    for (int i = 0; i < textLen - patLen + 1; i++)
        if (ind[i] == patCount)
            cout << pos[i].first << ", " << pos[i].second << endl;
}

void TTrie::DeleteTrie(TNode* node) {
    for (auto it : node->childs)
        DeleteTrie(it.second);
    delete node;
}

TTrie::~TTrie() {
    DeleteTrie(root);
}
