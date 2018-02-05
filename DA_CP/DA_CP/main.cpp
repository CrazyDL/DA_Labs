#include "TAudioSearch.h"

void PrintUsage(const char* cProgName) {
    std::cerr << "USAGE:" << cProgName << " index --input <input file> --output <index file>" << std::endl;
    std::cerr << cProgName << " search --index <index file> --input <input file> --output <output file>" << std::endl;
}

void PrintError(int32_t errorCode) {
    switch (errorCode) {
    case AS_OK:
        break;
    case AS_CANT_OPEN_FILE:
        std::cerr << "Could not open file" << std::endl;
        break;
    case AS_FILE_CORRUPT:
        std::cerr << "File corrupt" << std::endl;
        break;
    case AS_INITIALIZE_ERROR:
        std::cerr << "Resampler has not been properly initialized" << std::endl;
        break;
    case AS_ALLOCATE_ERROR:
        std::cerr << "Could not allocate the frame" << std::endl;
        break;
    case AS_NOT_FOUND:
        std::cerr << "Song not found" << std::endl;
        break;
    default:
        std::cerr << "Unknown error" << std::endl;
        break;
    }
}

int main(int argc, char *argv[]) {
    bool searchMode = false;
    if (argc == 1) {
        PrintUsage(argv[0]);
        return 1;
    }
    else if (!strcmp(argv[1], "index")) {
        if (argc < 6 || strcmp(argv[2], "--input") || strcmp(argv[4], "--output")) {
            std::cerr << "Wrong parameters for 'index'" << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
    }
    else if (!strcmp(argv[1], "search")) {
        if (argc < 8 || strcmp(argv[2], "--index") || strcmp(argv[4], "--input") || strcmp(argv[6], "--output")) {
            std::cerr << "Wrong parameters for 'search'" << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
        searchMode = true;
    }
    else {
        std::cerr << "Wrong mode" << std::endl;
        PrintUsage(argv[0]);
        return 1;
    }
    TAudioSearch as;
    mpg123_handle* mh = nullptr;
    int32_t err = mpg123_init();
    if (err != MPG123_OK || (mh = mpg123_new(nullptr, &err)) == nullptr){
        PrintError(AS_INITIALIZE_ERROR);
        return AS_INITIALIZE_ERROR;
    }
    long flags = MPG123_MONO_MIX | MPG123_QUIET | MPG123_FORCE_FLOAT;
    if (mpg123_param(mh, MPG123_FLAGS, flags, 0) != MPG123_OK) {
        PrintError(AS_INITIALIZE_ERROR);
        return AS_INITIALIZE_ERROR;
    }
    mpg123_format_none(mh);
    if (mpg123_format(mh, 44100, MPG123_MONO, MPG123_ENC_FLOAT) != MPG123_OK) {
        PrintError(AS_INITIALIZE_ERROR);
        return AS_INITIALIZE_ERROR;
    }
    PrintError(searchMode ? as.FindSongInBase(mh, argv[3], argv[5], argv[7]) : as.CreateMusicBase(mh, argv[3], argv[5]));
    mpg123_delete(mh);
    mpg123_exit();
    return 0;
}