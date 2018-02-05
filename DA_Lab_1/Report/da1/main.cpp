#include <iostream>
#include <algorithm>
#include <string.h>

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

struct Element
{
    double Key;
    char* Value;
};

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


