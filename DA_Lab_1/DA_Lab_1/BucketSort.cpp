#include "TVector.cpp"
#include "Element.h"
#include <iostream>

void InsertSort(TVector<Element*>& vect) {
    Element* buf;
    int i, j;
    for (i = 1; i < vect.Size(); i++) {
        buf = vect[i];
        for (j = i; j > 0 && vect[j - 1]->Key > buf->Key; j--)
            vect.Replace(j, vect[j - 1]);
        vect.Replace(j, buf);
    }
}

void BucketSort(TVector<Element*>& vect) {
    size_t n = vect.Size();
    TVector<Element*> vElem;
    TVector<TVector<Element*>> bucket(n, vElem);
    int SHIFT_LENGHT = 100;
    int ELEMENT_COUNT = 201;
    for (int i = 1; i <= n; i++)
        bucket[((vect[i - 1]->Key + SHIFT_LENGHT) / ELEMENT_COUNT) * n].Push(vect[i - 1]);
    for (int i = 0; i < n; i++)
        if(bucket[i].Size() > 1)
            InsertSort(bucket[i]);
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < bucket[i].Size(); j++){
            vect.Replace(k, bucket[i][j]);
            k++;
        }
}
