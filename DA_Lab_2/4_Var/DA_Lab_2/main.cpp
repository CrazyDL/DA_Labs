#include <iostream>
#include <string.h>
#include "TBTree.h"
#include "TNode.h"
#include "TSmartPointer.h"

using namespace std;

void PrintMessage(int msg) {
    switch (msg)
    {
    case OK:
        cout << "OK" << endl;
        break;
    case MEMORY_ERROR:
        cout << "ERROR: Memory not allocated" << endl;
        break;
    case FILE_ERROR:
        cout << "ERROR: File open error" << endl;
        break;
    case DESERIALIZATION_ERROR:
        cout << "ERROR: Deserialization error" << endl;
        break;
    case EXIST:
        cout << "Exist" << endl;
        break;
    case NOT_FOUND:
        cout << "NoSuchWord" << endl;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false); 
    cin.tie(0);
    TSmartPointer<TElem> elem(new TElem);
    TSmartPointer<TBTree> bTree(new TBTree(100));
    char cmd[257];
    while (cin >> cmd) {
        switch (cmd[0])
        {
        case '+':
            cin >> cmd;
            cin >> elem->value;
            elem->key = new char[strlen(cmd) + 1];
            strcpy(elem->key, cmd);
            PrintMessage(bTree->Insert(elem));
            elem = TSmartPointer<TElem>(new TElem);
            break;
        case '-':
            cin >> cmd;
            PrintMessage(bTree->Delete(cmd));
            break;
        case '!':
            cin >> cmd;
            if (cmd[0] == 'S') {
                cin >> cmd;
                PrintMessage(bTree->Serialization(cmd));
            }
            else if(cmd[0] == 'L') {
                cin >> cmd;
                TSmartPointer<TBTree> newBTree(new TBTree(0));
                int buf = newBTree->DeSerialization(cmd);
                PrintMessage(buf);
                if (!buf) bTree = newBTree;
            }
            break;
        default:
            PrintMessage(bTree->Search(bTree->GetRoot(), cmd));
            break;
        }
    }
}
