#pragma once
#include "TVector.h"

template <typename T>
TVector<T>::TVector() : TVector(0) {}

template <typename T>
TVector<T>::TVector(size_t vSize) {
    size = 0;
    cap = vSize;
    body = new T[cap];
}

template <typename T>
TVector<T>::TVector(size_t vSize, T value) {
    size = vSize;
    cap = vSize;
    body = new T[cap];
    for (int i = 0; i < size; i++)
        body[i] = value;
}

template <typename T>
TVector<T>::TVector(const TVector& orig) {
    size = orig.size;
    cap = orig.cap;
    body = new T[cap];
    for (int i = 0; i < size; i++)
        body[i] = orig.body[i];
}

template <typename T>
void TVector<T>::Resize(size_t vSize) {
    if (!vSize) Clear();
    else if (vSize == cap) return;
    else if (vSize > cap)
        while (vSize > cap)
            cap = cap*1.5 + 1;
    else
        while (vSize <= cap / 1.5)
            cap /= 1.5;
    T* result = new T[cap];
    for (int i = 0; i < cap && i < size - 1; i++)
        result[i] = body[i];
    if (body) delete[] body;
    body = result;
}

template <typename T>
bool TVector<T>::Empty() {
    return size == 0;
}

template <typename T>
size_t TVector<T>::Size() {
    return size;
}

template <typename T>
void TVector<T>::Clear() {
    if (cap)
        delete[] body;
    size = 0;
    cap = 0;
    body = nullptr;
}

template <typename T>
void TVector<T>::Push(T value) {
    size++;
    if (size > cap)
        Resize(size);
    body[size - 1] = value;
}

template <typename T>
void TVector<T>::Insert(size_t index, T value) {
    if (index < 0 || index > size) return;
    size++;
    if (size > cap)
        Resize(size);
    for (int i = size - 1; i > index; i--) {
        body[i] = body[i - 1];
    }
    body[index] = value;
}

template <typename T>
T TVector<T>::Pop() {
    if (!size) return NULL;
    size--;
    if (size < cap / 2)
        Resize(size);
    return body[size];
}

template <typename T>
T TVector<T>::Erase(size_t index) {
    if (index < 0 || index > size - 1) return NULL;
    size--;
    for (int i = index; i < size; i++)
        body[i] = body[i + 1];
    if (size < cap / 2)
        Resize(size);
    return body[size];
}

template <typename T>
void TVector<T>::Replace(size_t index, T value) {
    body[index] = value;
}

template <typename T>
TVector<T>::~TVector() {
    delete[] body;
    body = nullptr;
}

template <typename T>
T& TVector<T>::operator [](size_t index) {
    return body[index];
}

template <typename T>
void TVector<T>::operator=(const TVector& other) {
    size = other.size;
    cap = other.cap;
    body = new T[cap];
    for (int i = 0; i < size; i++)
        body[i] = other.body[i];
}
