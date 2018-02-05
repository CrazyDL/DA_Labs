#include <iostream>
#include <algorithm>
#include <ctime>
#include <string.h>
#include "TVector.cpp"
#include "Element.h"
#include "BucketSort.cpp"

using namespace std;

bool CheckOrder(TVector<Element*>& data) {
    for (size_t idx = 1; idx < data.Size(); ++idx) {
        if (data[idx - 1]->Key > data[idx]->Key) {
            return false;
        }
    }
    return true;
}

void StdSort(TVector<Element*>& data) {
    sort(&data[0], &data[data.Size()], [](Element* x, Element* y) { return x->Key < y->Key; });
}

void RunSort(TVector<Element*>& data, string type) {
    time_t start = clock();
    if (type == "bucket")
        BucketSort(data);
    else if (type == "std")
        StdSort(data);
    time_t end = clock();
    if (!CheckOrder(data)) return;
    cout << "Time of working " << type << ": " << (end - start)/1000.0 << endl;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main() {
    system("pause");
    srand(time(0));
    size_t size = 1000000;
    Element* elem = new Element();
    TVector<Element*> data(size);
    for (size_t idx = 0; idx < size; ++idx) {
        elem->Key = fRand(-100,100);
        elem->Value = new char[15];
        strcpy(elem->Value, "Test String");
        data.Push(elem);
        elem = new Element();
    }
    TVector<Element*> dataCopy(data);
    RunSort(data, "bucket");
    RunSort(dataCopy, "std");
    return 0;
}
