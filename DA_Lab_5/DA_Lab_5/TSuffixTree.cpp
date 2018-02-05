#include "TSuffixTree.h"

TSuffixTree::TSuffixTree(string& str) : text(str) {
    text += terminationChar;
    BuildSuffixTree();
}

void TSuffixTree::PrintTree(TNode* node, int lvl) {
    string spaces;
    for (int i = 0; i < lvl; i++) spaces += ' ';
    cout << "{" << endl << spaces << "Addres: " << node << "," << endl;
    cout << spaces << "suffixIndex: [";
    cout << node->suffixIndex << ", ";
    cout << "]," << endl;
    cout << spaces << "Text: '";
    if (node->start != -1)
        for (int k = node->start; k <= *node->end; k++)
            cout << text[k];
    cout << "'," << endl << spaces << "suffixLink: ";
    if (node->suffixLink) {
        cout << "{ Addres: " << node->suffixLink << ", Text: '";
        if (node->suffixLink != root)
            for (int k = node->suffixLink->start; k <= *node->suffixLink->end; k++)
                cout << text[k];
        cout << "'}," << endl;
    }
    else cout << "nullptr," << endl;
    cout << spaces << "Childs: [";
    for (auto it : node->childs)
        PrintTree(it.second, lvl + 4);
    cout << "]" << endl << spaces << "}, ";
}

int TSuffixTree::EdgeLength(TNode *node) {
    return *(node->end) - (node->start) + 1;
}

void TSuffixTree::ExtendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffCount++;
    lastNewNode = nullptr;
    while (remainingSuffCount) {
        if (!activeLength)
            activeEdge = pos;
        auto find = activeNode->childs.find(text[activeEdge]);
        if (find == activeNode->childs.end()) {
            activeNode->childs.insert(make_pair(text[activeEdge], new TNode(root, pos, &leafEnd, pos - remainingSuffCount + 1)));
            if (lastNewNode) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        }
        else {
            TNode* next = find->second;
            int edgeLen = EdgeLength(next);
            if (activeLength >= edgeLen) {
                activeEdge += edgeLen;
                activeLength -= edgeLen;
                activeNode = next;
                continue;
            }
            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode && activeNode != root)
                    lastNewNode->suffixLink = activeNode;
                activeLength++;
                break;
            }
            TNode* split = new TNode(root, next->start, new int(next->start + activeLength - 1));
            activeNode->childs[text[activeEdge]] = split;
            next->start += activeLength;
            split->childs.insert(make_pair(text[pos], new TNode(root, pos, &leafEnd, pos - remainingSuffCount + 1)));
            split->childs.insert(make_pair(text[next->start], next));
            if (lastNewNode)
                lastNewNode->suffixLink = split;
            lastNewNode = split;
        }
        remainingSuffCount--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffCount + 1;
        }
        else if (activeNode != root)
            activeNode = activeNode->suffixLink;
    }
}

void TSuffixTree::CountIndex(TNode* node, vector<int>& vec) {
    if (!node) return;
    for (auto it: node->childs)
        CountIndex(it.second, vec);
    if (node->suffixIndex != -1) vec.push_back(node->suffixIndex);
}

void TSuffixTree::BuildSuffixTree() {
    activeNode = root;
    size_t lenSize = text.length();
    for (size_t i = 0; i < lenSize; i++)
        ExtendSuffixTree(i);
}

void TSuffixTree::Search(string& pat, int patNum){
    TNode* current = root;
    for (auto it = pat.begin(); it != pat.end();) {
        auto find = current->childs.find(*it);
        if (find != current->childs.end()) {
            current = find->second;
            for (int j = current->start; j <= *current->end && it != pat.end(); j++, ++it)
                if (text[j] != *it) return;     
        }
        else return;
    }
    bool flag = false;
    cout << patNum << ": ";
    vector<int> ind;
    CountIndex(current, ind);
    sort(ind.begin(), ind.end());
    for (auto it: ind) {
        cout << (flag ? ", " : "") << it + 1;
        flag = true;
    }
    cout << endl;
}

void TSuffixTree::DeleteSuffixTree(TNode* node) {
    for (auto it : node->childs)
        DeleteSuffixTree(it.second);
    if (node->suffixIndex == -1)
        delete node->end;
    delete node;
}

TSuffixTree::~TSuffixTree() {
    DeleteSuffixTree(root);
}
