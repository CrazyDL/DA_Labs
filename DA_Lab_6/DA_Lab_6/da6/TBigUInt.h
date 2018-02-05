#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class TBigUInt {
public:
    TBigUInt ();
    TBigUInt (int64_t num);
    void Clear();
    friend istream& operator >> (istream &is, TBigUInt &bui);
    friend ostream& operator << (ostream &os, const TBigUInt &bui);
    bool operator == (const TBigUInt& bui) const;
    bool operator != (const TBigUInt& bui) const;
    bool operator > (const TBigUInt& bui) const;
    bool operator < (const TBigUInt& bui) const;
    bool operator >= (const TBigUInt& bui) const;
    bool operator <= (const TBigUInt& bui) const;
    TBigUInt& operator = (const TBigUInt& bui);
    TBigUInt operator + (const TBigUInt& bui);
    TBigUInt operator - (const TBigUInt& bui);
    TBigUInt operator * (const TBigUInt& bui);
    TBigUInt operator / (const TBigUInt& bui);
    TBigUInt operator ^ (const TBigUInt& bui);

    TBigUInt operator * (const int64_t& num);
    TBigUInt operator / (const int64_t& num);
    TBigUInt operator ^ (const int64_t& num);
private:
    vector<int64_t> number;
    size_t size;

    static const int64_t BASE = 1000000000;
    static const size_t NUM_SIZE = 9;

    int64_t Get(size_t i) const;
    void FixZero();
};


