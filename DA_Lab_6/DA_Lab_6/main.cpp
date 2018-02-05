#include <iostream>
#include "TBigUInt.h"
using namespace std;

int main() {
    TBigUInt bui, bui2;
    char operation;
    while (cin >> bui >> bui2 >> operation) {
        try {
            switch (operation) {
            case '>':
                cout << (bui > bui2 ? "true" : "false") << endl;
                break;
            case '<':
                cout << (bui < bui2 ? "true" : "false") << endl;
                break;
            case '=':
                cout << (bui == bui2 ? "true" : "false") << endl;
                break;
            case '+':
                cout << (bui + bui2) << endl;
                break;
            case '-':
                cout << (bui - bui2) << endl;
                break;
            case '*':
                cout << (bui * bui2) << endl;
                break;
            case '/':
                cout << (bui / bui2) << endl;
                break;
            case '^':
                cout << (bui ^ bui2) << endl;
                break;
            default:
                break;
            }
        }
        catch (logic_error) {
            cout << "Error" << endl;
        }
    }
    return 0;
}