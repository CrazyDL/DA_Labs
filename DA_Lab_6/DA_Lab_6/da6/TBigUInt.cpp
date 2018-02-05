#include "TBigUInt.h"

TBigUInt::TBigUInt() : size(0) {}

TBigUInt::TBigUInt(int64_t num) {
    size = 0;
    do {
        number.push_back(num % BASE);
        num /= BASE;
    } while (num);
    FixZero();
}

size_t CountNum(int64_t num) {
    size_t count = 1;
    while (num /= 10)
        count++;
    return count;
}

void TBigUInt::Clear() {
    number.clear();
    size = 0;
}

int64_t TBigUInt::Get(size_t i) const {
    return (i >= number.size() ? 0 : number[i]);
}

void TBigUInt::FixZero() {
    if (number.empty())return;
    while (number.size() > 1 && !number.back())
        number.pop_back();
    size = (number.size() - 1) * NUM_SIZE + CountNum(number.back());
}

istream& operator >> (istream &is, TBigUInt &bui) {
    if(bui.size)
        bui.Clear();
    string str;
    if(!(is >> str)) return is;
    for (int32_t i = str.length(); i > 0; i -= TBigUInt::NUM_SIZE) {
        bui.number.push_back(stoull(i < TBigUInt::NUM_SIZE ? str.substr(0, i) : str.substr(i - TBigUInt::NUM_SIZE, TBigUInt::NUM_SIZE)));
    }
    bui.FixZero();
    return is;
}

ostream& operator << (ostream &os, const TBigUInt &bui) {
    os << bui.number.back();
    os.fill('0');
    for (int32_t i = bui.number.size() - 2; i >= 0; i--)
        os << setw(TBigUInt::NUM_SIZE) << bui.number[i];
    return os;
}

TBigUInt& TBigUInt::operator = (const TBigUInt& bui) {
    if (this == &bui)
        return *this;
    number = bui.number;
    size = bui.size;
    return *this;
}

bool TBigUInt::operator > (const TBigUInt& bui) const {
    if (size > bui.size) return true;
    else if (size < bui.size) return false;
    for (int32_t i = number.size() - 1; i >= 0; i--)
        if (number[i] != bui.number[i]) 
            return number[i] > bui.number[i];
    return false;
}

bool TBigUInt::operator < (const TBigUInt& bui) const {
    return bui > *this;
}

bool TBigUInt::operator >= (const TBigUInt& bui) const {
    if (size > bui.size) return true;
    else if (size < bui.size) return false;
    for (int32_t i = number.size() - 1; i >= 0; i--)
        if (number[i] != bui.number[i])
            return number[i] > bui.number[i];
    return true;
}

bool TBigUInt::operator <= (const TBigUInt& bui) const {
    return bui >= *this;
}

bool TBigUInt::operator == (const TBigUInt& bui) const {
    if (size != bui.size) return false;
    for (int32_t i = number.size() - 1; i >= 0; i--)
        if (number[i] != bui.number[i]) return false;
    return true;
}

bool TBigUInt::operator != (const TBigUInt& bui) const {
    return !(*this == bui);
}

TBigUInt TBigUInt::operator + (const TBigUInt& bui) {
    if (*this == 0) return bui;
    else if (bui == 0) return *this;
    TBigUInt res;
    size_t lentgh = number.size() > bui.number.size() ? number.size() : bui.number.size();
    res.number.resize(lentgh + 1);
    int64_t k = 0;
    for (size_t i = 0; i < lentgh || k; i++) {
        res.number[i] = Get(i) + bui.Get(i) + k;
        if (res.number[i] >= BASE) {
            res.number[i] -= BASE;
            k = 1;
        }
        else
            k = 0;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator - (const TBigUInt& bui) {
    if (bui > *this)
        throw logic_error("Subtracted greatly reduces!");
    if (bui == 0) return *this;
    TBigUInt res = *this;
    size_t lentgh = number.size();
    int64_t k = 0;
    for (size_t i = 0; i < lentgh || k; i++) {
        res.number[i] -= bui.Get(i) + k;
        if((k = (res.number[i] < 0)))
            res.number[i] += BASE;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator * (const int64_t& num) {
    if (*this == 0 || num == 0) return 0;
    if (*this == 1) return num;
    else if (num == 1) return *this;
    TBigUInt res;
    size_t length = number.size();
    res.number.resize(length + 1);
    int64_t k = 0;
    for (size_t i = 0; i < length || k; i++) {
        res.number[i] = Get(i) * num + k;
        k = res.number[i] / BASE;
        res.number[i] -= k * BASE;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator * (const TBigUInt& bui) {
    if (bui.number.size() == 1)
        return *this * bui.number[0];
    if (*this == 0 || bui == 0) return 0;
    if (*this == 1) return bui;
    else if (bui == 1) return *this;
    TBigUInt res;
    size_t lentghA = number.size();
    size_t lentghB = bui.number.size();
    res.number.resize(lentghA + lentghB);
    for (size_t i = 0; i < lentghA; i++) {
        int64_t k = 0;
        for (size_t j = 0; j < lentghB || k; j++) {
            res.number[i + j] += Get(i) * bui.Get(j) + k;
            k = res.number[i + j] / BASE;
            res.number[i + j] -= k * BASE;
        }
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator / (const int64_t& num) {
    if (!num)
        throw logic_error("Division by zero!");
    if (*this == 0) return 0;
    if (num == 1) return *this;
    TBigUInt res = *this;
    int64_t remain = 0;
    for (int32_t i = res.number.size() - 1; i >= 0; i--) {
        int64_t cur = remain * BASE + number[i];
        res.number[i] = cur / num;
        remain = cur % num;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator / (const TBigUInt& bui) {
    if (bui.number.size() == 1)
        return *this / bui.number[0];
    if (bui == 0)
        throw logic_error("Division by zero!");
    if (*this == 0) return 0;
    if (bui == 1) return *this;
    if (*this < bui) return 0;
    int64_t d = BASE / (bui.number.back() + 1);
    TBigUInt u = *this * d;
    TBigUInt v = bui;
    v = v * d;
    TBigUInt res;
    res.number.resize(u.number.size());
    TBigUInt r;
    for (int32_t i = u.number.size() - 1; i >= 0; --i) {
        r = r * BASE;
        r = r + u.number[i];
        int64_t digit1 = r.number.size() <= v.number.size() ? 0 : r.number[v.number.size()];
        int64_t digit2 = r.number.size() <= v.number.size() - 1 ? 0 : r.number[v.number.size() - 1];
        int64_t resDigitTemp = (digit1 * BASE + digit2) / v.number.back();

        TBigUInt temp = v * resDigitTemp;
        while (r < temp) {
            temp = temp - v;
           --resDigitTemp;
        }
        r = r - temp;
        res.number[i] = resDigitTemp;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator ^ (const int64_t& num) {
    if(*this == 0 && num == 0)
        throw logic_error("Zero in pow zero!");
    if (num == 0 || *this == 1) return 1;
    if (*this == 0) return 0;
    if (num == 1) return *this;
    TBigUInt res = 1;
    TBigUInt cur = *this;
    int64_t n = num;
    while (n){
        if (n & 1)
            res = res * cur;
        cur = cur * cur;
        n >>= 1;
    }
    res.FixZero();
    return res;
}

TBigUInt TBigUInt::operator ^ (const TBigUInt& bui) {
    if (*this == 0 && bui == 0)
        throw logic_error("Zero in pow zero!");
    if (bui.number.size() == 1)
        return *this ^ bui.number[0];
    TBigUInt res = 1;
    TBigUInt cur = *this;
    TBigUInt n = bui;
    while (n != 0) {
        if (n.number[0] & 1)
            res = res * cur;
        cur = cur * cur;
        n = n / 2;
    }
    res.FixZero();
    return res;
}