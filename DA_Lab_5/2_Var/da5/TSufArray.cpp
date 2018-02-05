#include "TSufArray.h"


TSufArray::TSufArray(TSufTree* tree) {
    textLen = tree->textLen - 1;
    array = new int[textLen];
	int i = 0;
    countArray(tree->root, i);
}

void TSufArray::countArray(TNode* node, int& i) {
	if (!node)return;
	if (node->sufIndex != -1) {
		if (!i) i++;
		else {
			array[i - 1] = node->sufIndex;
			i++;
		}
	}
	for (auto it : node->childs) 
        countArray(it.second, i);
}

int TSufArray::StrComp(string& text, string& pat, int textBegin, int& i) {
	for (; i < pat.size() && pat[i] == text[i + textBegin]; i++);
	if (i == pat.size())
		return 0;
	if (pat[i] < text[i + textBegin]) 
		return 1;
	else 
        return -1;
}

void TSufArray::Search(string& text, string& pat, int numLine) {
	int m, L = 0, R = textLen;
	int result, l = 0, r = 0, minlr, i = 0;
	StrComp(text, pat, array[L], l);
	StrComp(text, pat, array[R - 1], r);
	while (L < R) {
		if (l < r)
			minlr = l;
		else
			minlr = r;
		m = (L + R) / 2;
		i = minlr;
		result = StrComp(text, pat, array[m], i);
		if (result == -1) {
			L = m + 1;
			l = 0;
			StrComp(text, pat, array[L], l);
		}
		else {
			R = m;
			r = 0;
			StrComp(text, pat, array[R], r);
		}
	}

	if (StrComp(text, pat, array[R], i)) return;

    vector<int> ans;
	i = 0;
	while (StrComp(text, pat, array[R], i) == 0 && R < textLen) {
        ans.push_back(array[R]);
		R++;
		i = 0;
	}
    sort(ans.begin(), ans.end());
    printf("%d: ", numLine);
    for (int i = 0; i < ans.size(); i++) {
        printf("%d", ans[i] + 1);
        if (i != ans.size() - 1)
            printf(", ");
    }
    printf("\n");
}


TSufArray::~TSufArray() {
	delete[] array;
}
