#ifndef SUFFIXARRAY_H_
#define SUFFIXARRAY_H_

#include <vector>
#include <algorithm>
#include "TSufTree.h"

class TSufArray {
public:
	TSufArray(TSufTree* tree);
	void Search(string& text, string& pat, int numLine);
	~TSufArray();
private:
    int* array;
    int textLen;

	int StrComp(string& text, string& pat, int textBegin, int& i);
	void countArray(TNode* node, int& i);
};

#endif