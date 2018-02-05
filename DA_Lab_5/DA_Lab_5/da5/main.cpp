#include "TSuffixTree.h"

int main(int argc, char *argv[]) {
    string text, pattern;
    cin >> text;
    TSuffixTree suffixTree(text);
    int patNum = 0;
    while (cin >> pattern)
        suffixTree.Search(pattern, ++patNum);
}