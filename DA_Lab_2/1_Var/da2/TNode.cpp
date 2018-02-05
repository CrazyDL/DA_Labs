#include "TNode.h"

TNode::TNode(const char* str, unsigned long long val) {
    key = new char[strlen(str) + 1];
    strcpy(key, str);
    l = r = nullptr;
    height = 1;
    value = val;
}

 int TNode::Height() {
    if (this) return height;
    else return 0;
}

int TNode::Balance() {
    return r->Height() - l->Height();
}

void TNode::FixHeight() {
    if (l->Height() > r->Height())
        height = l->Height() + 1;
    else
        height = r->Height() + 1;
}

TNode::~TNode() {
    delete [] key;
}