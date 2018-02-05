#include <iostream>
#include <string>

#include "TSufTree.h"
#include "TSufArray.h"

using namespace std;

int main() {
    TSufTree tree;
	string str;
	cin >> str;
	str += '$';
	string pat;
	tree.Build(str);
	TSufArray sufArray(&tree);
	int numLine = 1;
	while (cin >> pat) {
        sufArray.Search(str, pat, numLine);
		numLine++;
	}

}