#ifndef SUFFIXTREE_H_
#define SUFFIXTREE_H_

#include <iostream>
#include <string>
#include <map>

class TSufTree;
class TSufArray;

using namespace std;

class TNode {
public:
	friend class TSufTree;
	friend class TSufArray;
	TNode(int begin, int* end, TNode* root, int sufIndex);
	int SufLen();
	bool Down();
private:
    int begin;
    int* end;
    TNode *sufLink;
    int sufIndex;
    map <char, TNode*> childs;
};

class TSufTree {
public:
	friend class TSufArray;
	TSufTree();
	void Build(string &text);
	~TSufTree();
private:
    TNode* root;
    int textLen;

	void DeleteTree(TNode* node);
	void Insert(string& text, int i);
};

#endif
