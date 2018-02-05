#include "TSuffixTree.h"
#include <ctime>

int main(int argc, char *argv[]) {
    string text, pattern;
    cin >> text;
    time_t start = clock();
    TSuffixTree suffixTree(text);
    int patNum = 0;
    while (cin >> pattern)
        suffixTree.Search(pattern, ++patNum);
    time_t end = clock();
    cout << "Time of working: " << (end - start) / 1000.0 << endl;
}