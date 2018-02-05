#pragma once

template <typename T>
class TVector {
public:
    TVector();
    TVector(size_t vSize);
    TVector(size_t vSize, T value);
    TVector(const TVector& orig);
    bool Empty();
    void Clear();
    size_t Size();
    void Push(T value);
    void Insert(size_t index, T value);
    T Pop();
    T Erase(size_t index);
    void Resize(size_t vSize);
    void Replace(size_t index, T value);
    T& operator[](size_t index);
    void operator=(const TVector& other);
    ~TVector();
private:
    T* body;
    size_t size;
    size_t cap;
};
