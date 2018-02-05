#include <stdio.h>
#include "TAVLtree.h"
#include <iostream>

using namespace std;

int main(int argv, char **argc) {
    char answer;
    unsigned long long value;
    char key[257];
    int len;
    TAVLtree* tree = new TAVLtree();
    while (cin >> key) {  
        switch(key[0]) {
            case '+' :
                cin >> key;
                len = strlen(key);
                for (int i = 0; i < len; i++)
                    key[i] = tolower(key[i]);
                cin >> value;
                tree->Insert(key, value);
                break;
            case '-':
                cin >> key;
                len = strlen(key);
                for (int i = 0; i < len; i++)
                    key[i] = tolower(key[i]);
                tree->DeleteNode(key);
                break;
            case '!':
                cin >> key;
                if(key[0] == 'S') {
                    cin >> key;
                    tree->Serialization(key);
                }
                else if(key[0] == 'L') {
                    cin >> key;
                    TAVLtree* newTree = new TAVLtree();
                    answer = newTree->DeSerialization(key);
                    switch (answer) {
                        case 0:
                            printf("OK\n");
                            delete tree;
                            tree = newTree;
                            break;
                        case -2:
                            printf("ERROR: Can't create file\n");
                            break;
                        case -1:
                            printf("ERROR: Deserialization error\n");
                            break;
                    }
                    
                }
                break;
            default:
                len = strlen(key);
                for (int i = 0; i < len; i++)
                    key[i] = tolower(key[i]);
                tree->Search(key);
                break;
        }
    }
    delete tree;
}































