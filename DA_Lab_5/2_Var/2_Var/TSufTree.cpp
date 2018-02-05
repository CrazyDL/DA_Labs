#include "TSufTree.h"

TNode* activeNode = nullptr;
TNode* lastNode = nullptr;
int activeSuf = -1;
int activeLen = 0;
int sufCount = 0;
int leafInd = -1;

TNode::TNode(int begin, int* end, TNode* root, int sufIndex) : begin(begin), end(end), sufLink(root), sufIndex(sufIndex) {}

int TNode::SufLen() {
	return *end - begin + 1;
}

bool TNode::Down() {
	if (activeLen >= SufLen()) {
		activeSuf += SufLen();
		activeLen -= SufLen();
		activeNode = this;
		return true;
	}
	return false;
}


TSufTree::TSufTree() : root(new TNode(-1, new int(-1), nullptr, -1)) {}

void TSufTree::Insert(string& text, int i) {
	leafInd = i;
	sufCount++;
	lastNode = nullptr;

	while (sufCount > 0) {
        if (activeLen == 0)
			activeSuf = i;

		if (activeNode->childs.find(text[activeSuf]) == activeNode->childs.end()) {
			activeNode->childs.insert(make_pair(text[activeSuf], new TNode(i, &leafInd,root,i - sufCount + 1)));
			if (lastNode != nullptr) {
				lastNode->sufLink = activeNode;
				lastNode = nullptr;
			}
		} 
		else {
			TNode *next = activeNode->childs.find(text[activeSuf])->second;
            if (activeLen >= next->SufLen()) {
                activeSuf += next->SufLen();
                activeLen -= next->SufLen();
                activeNode = next;
                continue;
            }

			if (text[next->begin + activeLen] == text[i]) {
				if (lastNode != nullptr && activeNode != root) 
					lastNode->sufLink = activeNode;
				activeLen++;
				break;
			}
            int* endSplit = new int(next->begin + activeLen - 1);
			TNode* split = new TNode(next->begin, endSplit, root, -1);
			activeNode->childs[text[activeSuf]] = split;

			split->childs.insert(make_pair(text[i], new TNode(i, &leafInd, root, i - sufCount + 1)));
			next->begin += activeLen;
			split->childs.insert(make_pair(text[next->begin], next));

			if (lastNode != nullptr)
				lastNode->sufLink = split;
			lastNode = split;
		}

		sufCount--;
		if (activeNode == root && activeLen > 0) {
			activeLen--;
			activeSuf = i - sufCount + 1;
		}
		else if (activeNode != root)
			activeNode = activeNode->sufLink;
	}
}


void TSufTree::Build(string &text) {
	textLen = text.size();
	activeNode = root;
	for (int i = 0; i < textLen; i++)
		Insert(text, i);
}

void TSufTree::DeleteTree(TNode* node) {
	for (auto it : node->childs)
		DeleteTree(it.second);
	delete node;
}

TSufTree::~TSufTree() {
	DeleteTree(root);
}
