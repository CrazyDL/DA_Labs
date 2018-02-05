#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "TNode.h"

using namespace std;

int main(int argc, char *argv[])
{
    TNode* root = new TNode();
    vector< pair<int32_t, pair<size_t, size_t> > > text;
    vector<uint32_t> pattern;
    string temp, temp2;
    getline(cin, temp);
    stringstream sStream(temp);
    size_t patLen = 0, maxLen = 0, patCount = 0;
    while (sStream >> temp2) {
        if (temp2 == "?") {
            if (!pattern.size()) patLen++;
            else {
                size_t patSize = pattern.size();
                patLen += patSize;
                addPattern(root, pattern, patLen);
                if (patSize > maxLen) maxLen = patSize;
                pattern.clear();
                patLen++; 
                patCount++;
            }
        }
        else
            pattern.push_back(stoul(temp2));
    }
    if (temp2 != "?") {
        patCount++;
        patLen += pattern.size();
        addPattern(root, pattern, patLen);
        if (pattern.size() > maxLen) maxLen = pattern.size();
    }
    processTrie(root, maxLen);
    printTrie(root, 0);
    size_t position = 1, line = 0;
    while (getline(cin, temp)) {
        line++;
        position = 1;
        if (!temp.size()) continue;
        stringstream sStream(temp);
        while (sStream >> temp2) {
            text.push_back(make_pair(stoul(temp2), make_pair(line, position)));
            position++;
        }
    }
    time_t start = clock();
    Search(root, text, patLen, patCount);
    time_t end = clock();
    cout << "Time of working: " << (end - start) / 1000.0 << endl;
    DeleteTrie(root);
}