#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "TTrie.h"

using namespace std;

int main(int argc, char *argv[]) {
    TTrie root;
    vector<int> text;
    vector<pair<int, int>> pos;
    vector<unsigned int> pattern;
    string str, str2;
    getline(cin, str);
    stringstream sStr(str);
    int len = 0, max = 0, count = 0;
    while (sStr >> str2) {
        if (str2 == "?") {
            if (!pattern.empty()) {
                if (pattern.size() > max) max = pattern.size();
                len += pattern.size();
                root.AddPat(pattern, len);
                pattern.clear();
                count++;
            }
            len++;
        }
        else
            pattern.push_back(stoul(str2));
    }
    if (str2 != "?") {
        if (pattern.size() > max) max = pattern.size();
        count++;
        len += pattern.size();
        root.AddPat(pattern, len);
    }
    root.ProcessTrie(max);
    int position = 1, line = 0;
    while (getline(cin, str)) {
        line++;
        position = 1;
        if (str.empty()) continue;
        stringstream sStr(str);
        while (sStr >> str2) {
            text.push_back(stoul(str2));
            pos.push_back(make_pair(line, position));
            position++;
        }
    }
    root.Search(text, pos, len, count);
}