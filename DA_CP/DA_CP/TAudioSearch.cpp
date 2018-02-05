#include "TAudioSearch.h"

std::unordered_map<int64_t, std::list<DataPoint>> TAudioSearch::hashMap;
std::vector<std::string> TAudioSearch::songs;

int32_t TAudioSearch::CreateMusicBase(mpg123_handle* mh, std::string input, std::string output) {
    searchMode = false;
    std::ifstream fin(input);
    if (!fin)
        return AS_CANT_OPEN_FILE;
    while (std::getline(fin, songName)) {
        songId = songs.size();
        songs.push_back(songName);
        if (DecodeAudioFile(mh) != AS_OK) {
            std::cerr << "Error in file " << songName << std::endl;
            songs.pop_back();
        }
    }
    fin.close();
    if (hashMap.empty())
        std::cerr << "Base empty" << std::endl;
    return Serialization(output);
}

int32_t TAudioSearch::FindSongInBase(mpg123_handle* mh, std::string base, std::string input, std::string output) {
    searchMode = true;
    int32_t stat = Deserialization(base);
    if (stat != AS_OK)
        return stat;
    std::ifstream fin(input);
    std::ofstream fout(output);
    while (std::getline(fin, songName)) {
        if (DecodeAudioFile(mh) != AS_OK) {
            std::cerr << "Error in file '" << songName << "'" << std::endl;
            continue;
        }
        int32_t bestCount = 0;
        int32_t bestSong = -1;
        for (int32_t id = songs.size() - 1; id >= 0; id--) {
            auto tmpMap = matchMap.find(id);
            int32_t bestCountForSong = 0;
            if (tmpMap == matchMap.end())
                continue;
            for (auto entry : tmpMap->second) {
                if (entry.second > bestCountForSong)
                    bestCountForSong = entry.second;
            }

            if (bestCountForSong > bestCount) {
                bestCount = bestCountForSong;
                bestSong = id;
            }
        }
        if (bestSong == -1 || (bestCount / (float)songLen) * 100 < 10)
            fout << "! NOT FOUND " << std::endl;
        else
            fout << songs[bestSong] << std::endl;
    }
    fout.close();
    fin.close();
    return AS_OK;
}

int32_t TAudioSearch::Serialization(std::string output) {
    std::ofstream fout(output);
    if (!fout)
        return AS_CANT_OPEN_FILE;
    if (songs.empty()) {
        std::cerr << "Base empty" << std::endl;
        fout << 0;
    }
    else {
        fout << songs.size() << ' ';
        for (std::string i : songs)
            fout << i << std::endl;
        fout << hashMap.size() << ' ';
        for (auto i : hashMap) {
            fout << i.first << ' ';
            fout << i.second.size() << ' ';
            for (auto list : i.second) {
                fout << list.songId << ' ' << list.time << ' ';
            }
        }
    }
    fout.close();
    return AS_OK;
}

int32_t TAudioSearch::Deserialization(std::string input) {
    std::ifstream fin(input);
    if (!fin)
        return AS_CANT_OPEN_FILE;
    std::string str;
    size_t size, sizeList;
    int64_t hash;
    int32_t songId, time;
    std::list<DataPoint> buflist;
    fin >> size;
    if (!size) 
        std::cerr << "Base empty" << std::endl;
    else {
        songs.resize(size);
        fin.get();
        for (size_t i = 0; i < size; i++)
            std::getline(fin, songs[i]);
        fin >> size;
        hashMap.reserve(size);
        for (size_t i = 0; i < size; i++) {
            fin >> hash;
            fin >> sizeList;
            for (size_t j = 0; j < sizeList; j++) {
                fin >> songId >> time;
                buflist.push_back({ songId, time });
            }
            hashMap.insert(std::make_pair(hash, buflist));
            buflist.clear();
        }
    }
    fin.close();
    return AS_OK;
}

void TAudioSearch::Fft(CArray& x) {
    size_t N = x.size(), k = N, n;
    float thetaT = (float)M_PI / N;
    Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
    while (k > 1) {
        n = k;
        k >>= 1;
        phiT = phiT * phiT;
        T = 1.0L;
        for (size_t l = 0; l < k; l++) {
            for (size_t a = l; a < N; a += n) {
                size_t b = a + k;
                Complex t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    size_t m = (size_t)log2(N);
    for (size_t a = 0; a < N; a++) {
        size_t b = a;
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            Complex t = x[a];
            x[a] = x[b];
            x[b] = t;
        }
    }
}

int32_t TAudioSearch::DecodeAudioFile(mpg123_handle* mh) {
    size_t done;
    int channels, encoding;
    long rate;
    size_t bufferSize = mpg123_outblock(mh);
    unsigned char* ucBuffer = new unsigned char[bufferSize];
    if (mpg123_open(mh, songName.c_str()) != MPG123_OK)
        return AS_CANT_OPEN_FILE;
    mpg123_getformat(mh, &rate, &channels, &encoding);
    std::vector<float> data;
    size_t doubleSize = sizeof(float);
    float RC = 1.0f / (2000 * 2 * (float)M_PI);
    float dt = 1.0f / 44100;
    float alpha = dt / (RC + dt);
    for (int totalBtyes = 0; mpg123_read(mh, ucBuffer, bufferSize, &done) == MPG123_OK; ) {
        float* dBuffer = reinterpret_cast<float*>(ucBuffer);
        size_t dataSize = bufferSize / doubleSize;
        for (size_t i = 1; i < dataSize; i++)
            dBuffer[i] = dBuffer[i - 1] + (alpha*(dBuffer[i] - dBuffer[i - 1]));
        size_t i = 0;
        for (; i + 4 <= dataSize; i += 4)
            data.push_back((dBuffer[i] + dBuffer[i + 1] + dBuffer[i + 2] + dBuffer[i + 3]) / 4);
        if (i > dataSize) {
            i -= 4;
            while (i < dataSize) {
                data.push_back(dBuffer[i]);
                i++;
            }
        }
        totalBtyes += done;
    }
   
    delete[] ucBuffer;
    mpg123_close(mh);
    return MakeSpectrum(data);
}

int32_t TAudioSearch::MakeSpectrum(std::vector<float>& data) {
    const size_t ONE_CHANK_SIZE = 1024;
    size_t totalSize = data.size();
    size_t amountPossible = totalSize / ONE_CHANK_SIZE;

    std::vector<CArray> result(amountPossible, CArray(ONE_CHANK_SIZE));

    for (size_t times = 0; times < amountPossible; times++) {
        for (size_t i = 0; i < ONE_CHANK_SIZE; i++) 
            result[times][i] = data[(times * ONE_CHANK_SIZE) + i];
        Fft(result[times]);
        break;
    }
    data.clear();
    return DetermineKeyPoints(result);
}

size_t TAudioSearch::GetIndex(int32_t freq) {
    size_t i = 0;
    while (RANGE[i] < freq) i++;
    return i;
}

int64_t TAudioSearch::Hash(int64_t p1, int64_t p2, int64_t p3, int64_t p4) {
    return (p4 - (p4 % FUZ_FACTOR)) * 100000000 
         + (p3 - (p3 % FUZ_FACTOR)) * 100000
         + (p2 - (p2 % FUZ_FACTOR)) * 100
         + (p1 - (p1 % FUZ_FACTOR));
}

int32_t TAudioSearch::DetermineKeyPoints(std::vector<CArray>& result) {
    songLen = result.size();
    std::vector<std::vector<float>> highscores(songLen, std::vector<float>(5, 0));
    std::vector<std::vector<int64_t>> points(songLen, std::vector<int64_t>(5, 0));
    matchMap.clear();
    for (size_t t = 0; t < songLen; t++) {
        for (int freq = LOWER_LIMIT; freq < UPPER_LIMIT - 1; freq++) {
            float mag = log(std::abs(result[t][freq]) + 1);
            size_t index = GetIndex(freq);

            if (mag > highscores[t][index]) {
                highscores[t][index] = mag;
                points[t][index] = freq;
            }
        }

        int64_t h = Hash(points[t][0], points[t][1], points[t][2], points[t][3]);

        if (searchMode) {
            auto listPoints = hashMap.find(h);
            if (listPoints != hashMap.end()) {
                for (DataPoint& dP : listPoints->second) {
                    int32_t offset = abs(dP.time - (int32_t)t);
                    auto it2 = matchMap.find(dP.songId);
                    if (it2 == matchMap.end()) {
                        std::map<int32_t, int32_t> tmpMap;
                        tmpMap.insert(std::make_pair(offset, 1));
                        matchMap.insert(std::make_pair(dP.songId, tmpMap));
                    }
                    else {
                        auto tmp = it2->second.find(offset);
                        if (tmp == it2->second.end()) {
                            it2->second.insert(std::make_pair(offset, 1));
                        }
                        else {
                            int32_t count = tmp->second + 1;
                            it2->second.erase(offset);
                            it2->second.insert(std::make_pair(offset, count));
                        }
                    }
                }
            }
        }
        else {
            std::list<DataPoint> listPoints;
            auto it = hashMap.find(h);
            if (it == hashMap.end()) {
                listPoints.push_back({ songId, (int32_t)t });
                hashMap.insert(std::make_pair(h, listPoints));
            }
            else
                it->second.push_back({ songId, (int32_t)t });
        }
    }
    return AS_OK;
}
