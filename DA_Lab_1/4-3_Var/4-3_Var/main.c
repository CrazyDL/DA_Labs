#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int date;
    int valuePos;
    char strDate[11];
} TKey;

TKey* RadixSort(TKey* keys, int curPos, int max) {
    TKey* b = (TKey*)malloc(sizeof(TKey) * curPos);
    TKey* swap;
    int x, r, tmp = max, bits = 0, log = 0, degreeR;
    while (tmp) {
        tmp = tmp >> 1;
        bits++;
    }
    tmp = curPos >> 1;
    while (tmp) {
        tmp = tmp >> 1;
        log++;
    } 
    if (bits < log || log == 0)
        r = bits;
    else
        r = log;
    degreeR = (1u << r) - 1;
    int* c = (int*)malloc(sizeof(int) * (degreeR + 1));
    for (int q = 0; max; q++) {
        for (int i = 0; i <= degreeR; i++)
            c[i] = 0;
        for (int i = 0; i < curPos; i++) {
            x = (keys[i].date & (degreeR << q * r)) >> q * r;
            c[x] = c[x] + 1;
        }
        for (int i = 1; i <= degreeR; i++)
            c[i] = c[i] + c[i-1];
        for (int i = curPos - 1; i >= 0; i--) {
            x = (keys[i].date & (degreeR << q * r)) >> q * r;
            b[c[x] - 1] = keys[i];
            c[x] = c[x] - 1;
        }
        max = max >> r;
        swap = keys;
        keys = b;
        b = swap;
    }
    free(b);
    free(c);
    return keys;
}
    
int main() {
    TKey* keys;
    unsigned long long* values;
    int year, day, month, i = 0, curPos = 0, size = 1, max = 0;
    keys = (TKey*)malloc(sizeof(TKey) * size);
    values = (unsigned long long*)malloc(sizeof(unsigned long long) * size);
    while (scanf("%s\t%llu", keys[curPos].strDate, &values[curPos]) == 2) {
        keys[curPos].valuePos = curPos;
        year = 0; day = 0; month = 0; i = 0;
        while (keys[curPos].strDate[i] != '.') {
            day = day * 10 + keys[curPos].strDate[i] - '0';
            i++;
        }
        i++;
        while (keys[curPos].strDate[i] != '.') {
            month = month * 10 + keys[curPos].strDate[i] - '0';
            i++;
        } 
        i++;
        while (keys[curPos].strDate[i] != '\0') {
            year = year * 10 + keys[curPos].strDate[i] - '0';
            i++;
        }
        keys[curPos].date = year * 10000 + month * 100 + day;
        if (keys[curPos].date > max)
            max = keys[curPos].date;
        curPos++;
        if (curPos >= size){
            size = size * 12;
            keys = (TKey*)realloc(keys, sizeof(TKey) * size);
            values = (unsigned long long*)realloc( values, sizeof(unsigned long long) * size);
        }
    }    
    keys = RadixSort(keys, curPos, max);
    for (i = 0; i < curPos; i++)
        printf("%s\t%llu\n", keys[i].strDate, values[keys[i].valuePos]);
    free(keys);
    free(values);
}







