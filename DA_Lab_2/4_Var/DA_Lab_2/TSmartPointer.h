#pragma once

template<typename T> struct Object
{
    Object(T* newPtr, size_t n) : ptr(newPtr), ptrCount(n) { }
    T* ptr;
    size_t ptrCount;
};


template <typename T> class TSmartPointer
{
public:
    TSmartPointer();
    TSmartPointer(T* ptr);
    TSmartPointer(const TSmartPointer<T>& sptr);
    TSmartPointer<T>& operator=(const TSmartPointer<T>& sptr);
    T& operator*();
    T* operator->();
    bool operator==(TSmartPointer<T>& sptr);
    operator bool();
    void Reset();
    ~TSmartPointer();
private:
    Object<T>* obj;

    void RemovePtr();
};

template <typename T>
TSmartPointer<T>::TSmartPointer() {
    obj = new Object<T>(nullptr, 0);
}

template <typename T>
TSmartPointer<T>::TSmartPointer(T* newPtr) {
    obj = new Object<T>(newPtr, 1);
}

template <typename T>
TSmartPointer<T>::TSmartPointer(const TSmartPointer<T>& sptr) {
    obj = sptr.obj;
    obj->ptrCount++;
}

template <typename T>
TSmartPointer<T>& TSmartPointer<T>::operator=(const TSmartPointer<T>& sptr) {
    if (this != &sptr) {
        if(obj) RemovePtr();
        obj = sptr.obj;
        obj->ptrCount++;
    }
    return *this;
}

template <typename T>
T& TSmartPointer<T>::operator*() {
    return *obj->ptr;
}

template <typename T>
T* TSmartPointer<T>::operator->() {
    return obj->ptr;
}

template <typename T>
bool TSmartPointer<T>::operator==(TSmartPointer<T>& sptr) {
    return obj->ptr == sptr.obj->ptr;
}

template <typename T>
TSmartPointer<T>::operator bool() {
    return obj->ptr != nullptr;
}

template <typename T>
void TSmartPointer<T>::RemovePtr() {
    if (obj->ptrCount)
        obj->ptrCount--;
    if (!obj->ptrCount){
        delete obj->ptr;
        delete obj;
        obj = nullptr;
    }
}

template <typename T>
void TSmartPointer<T>::Reset() {
    if(obj) RemovePtr();
}

template <typename T>
TSmartPointer<T>::~TSmartPointer() {
    if(obj) RemovePtr();
}

