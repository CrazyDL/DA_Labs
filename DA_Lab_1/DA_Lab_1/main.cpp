#include <iostream>
#include <string.h>
#include "TVector.cpp"
#include "Element.h"
#include "BucketSort.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    TVector<Element*> vect;
    Element* elem = new Element();
    const int MAX_LINE_LENGHT = 2049;
    char buffer[MAX_LINE_LENGHT];
    while (cin >> elem->Key) {
        cin.get();
        cin.getline(buffer, MAX_LINE_LENGHT, '\n');
        elem->Value = new char[strlen(buffer) + 1];
        strcpy(elem->Value, buffer);
        vect.Push(elem);
        elem = new Element();
    }
    BucketSort(vect);
    cout.setf(ios::fixed);
    cout.precision(6);
    for (int i = 0; i < vect.Size(); i++)
        cout << vect[i]->Key << '\t' << vect[i]->Value << endl;
}
