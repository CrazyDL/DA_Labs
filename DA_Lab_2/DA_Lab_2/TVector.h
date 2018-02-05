#pragma once
#include <cstdlib>

const size_t MIN_VECT_SIZE = 4;

template <typename T>
class TVector {
public:
    TVector();
    TVector(size_t vSize);
    TVector(size_t vSize, T& value);
    TVector(const TVector& orig);
    bool Empty();
    void Clear();
    size_t Size();
    void Push(T& value);
    void Insert(size_t index, T& value);
    T& Pop();
    T& Erase(size_t index);
    void Resize(size_t vSize);
    void Add(TVector& other);
    T& operator[](size_t index);
    void operator=(const TVector& other);
    ~TVector();
private:
    T* body;
    size_t size;
    size_t cap;
};


template <typename T>
TVector<T>::TVector() : TVector(MIN_VECT_SIZE) {}

template <typename T>
TVector<T>::TVector(size_t vSize) {
    size = 0;
    cap = vSize;
    body = new T[cap];
}

template <typename T>
TVector<T>::TVector(size_t vSize, T& value) {
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
    if (vSize == cap) return;
    else if (!vSize) {
        Clear();
        return;
    }
    else if (vSize > cap)
        while (vSize > cap)
            cap = (size_t)(cap*1.5 + 1);
    else {
        cap = vSize;
        if (size > vSize)
            size = vSize;
    }
    T* result = new T[cap];
    for (size_t i = 0; i < size; i++)
        result[i] = body[i];
    delete[] body;
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
    if (cap) delete[] body;
    size = 0;
    cap = MIN_VECT_SIZE;
    body = new T[cap];
}

template <typename T>
void TVector<T>::Push(T& value) {
    if (size + 1 > cap)
        Resize(size + 1);
    body[size] = value;
    size++;

}

template <typename T>
void TVector<T>::Insert(size_t index, T& value) {
    if (index < 0 || index > size) return;
    if (size + 1 > cap)
        Resize(size + 1);
    for (size_t i = size; i > index; i--)
        body[i] = body[i - 1];
    body[index] = value;
    size++;
}

template <typename T>
T& TVector<T>::Pop() {
    size--;
    T& buf = body[size];
    if (size < cap / 2)
        Resize(size);
    return buf;
}

template <typename T>
T& TVector<T>::Erase(size_t index) {
    T& buf = body[index];
    size--;
    for (size_t i = index; i < size; i++)
        body[i] = body[i + 1];
    if (size < cap / 2)
        Resize(size);
    return buf;
}

template <typename T>
TVector<T>::~TVector() {
    delete[] body;
}

template <typename T>
T& TVector<T>::operator [](size_t index) {
    return body[index];
}

template <typename T>
void TVector<T>::Add(TVector& other) {
    for (size_t i = 0; i < other.size; i++)
        Push(other.body[i]);
    other.Clear();
}

template <typename T>
void TVector<T>::operator=(const TVector& other) {
    size = other.size;
    cap = other.cap;
    for (size_t i = 0; i < size; i++)
        body[i] = other.body[i];
}
