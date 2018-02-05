#pragma once 
#define _USE_MATH_DEFINES
#include <iostream>
#include <string.h>
#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <map>
#include <list>
#include <valarray>  
#include "mpg123.h"


enum TErrorCode {
    AS_OK,
    AS_CANT_OPEN_FILE,
    AS_FILE_CORRUPT,
    AS_INITIALIZE_ERROR,
    AS_ALLOCATE_ERROR, 
    AS_NOT_FOUND
};

typedef std::complex<float> Complex;
typedef std::valarray<Complex> CArray;
const int32_t FUZ_FACTOR = 2;
const int32_t UPPER_LIMIT = 300;
const int32_t LOWER_LIMIT = 40;
const int32_t RANGE[] = { LOWER_LIMIT, 80, 120, 180, UPPER_LIMIT + 1 };

struct DataPoint {
    int32_t songId;
    int32_t time;
};

class TAudioSearch {
    static std::unordered_map<int64_t, std::list<DataPoint>> hashMap;
    static std::vector<std::string> songs;
public:
    int32_t CreateMusicBase(mpg123_handle* mh, std::string input, std::string output);
    int32_t FindSongInBase(mpg123_handle* mh, std::string base, std::string intput, std::string output);

private:
    std::string songName;
    bool searchMode;
    int32_t songId;
    size_t songLen;
    std::unordered_map<int32_t, std::map<int32_t, int32_t>> matchMap;

    int32_t DecodeAudioFile(mpg123_handle* mh);
    int32_t MakeSpectrum(std::vector<float>& data);
    int32_t DetermineKeyPoints(std::vector<CArray>& result);

    int32_t Serialization(std::string output);
    int32_t Deserialization(std::string input);
    
    void Fft(CArray& x);
    int64_t Hash(int64_t p1, int64_t p2, int64_t p3, int64_t p4);
    size_t GetIndex(int32_t freq);
};
