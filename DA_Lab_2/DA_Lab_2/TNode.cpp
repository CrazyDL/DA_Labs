#include "TNode.h"

TNode::TNode() : leaf(true){ }

TNode::TNode(const TNode& other) {
    leaf = other.leaf;
    elem = other.elem;
    if (!leaf) child = other.child;
}

TNode& TNode::operator=(const TNode& other) {
    if (this != &other) {
        leaf = other.leaf;
        elem = other.elem;
        if (!leaf) child = other.child;
    }
    return *this;
}
