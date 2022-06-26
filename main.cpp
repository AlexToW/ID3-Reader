#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/stat.h>


#define TAG_LEN 3
#define NAME_LEN 30
#define SINGER_LEN 30
#define ALBUM_LEN 30
#define YEAR_LEN 4
#define COMMENT_LEN 28
#define ZERO_BYTE_LEN 1
#define TRACK_NUMBER_LEN 1
#define GENRE_LEN 1


struct MetaData {
    char TAG[TAG_LEN];          // +
    char name[NAME_LEN];        // +
    char singer[SINGER_LEN];    // +
    char album[ALBUM_LEN];      // +
    char year[YEAR_LEN];        // +
    char comment[COMMENT_LEN];  // +
    char zero_byte;             // +
    char track_number;          // +
    char genre;
};


typedef struct MetaData MetaData;


bool is_valid_file(std::string& path);
std::vector<char> GetVectorData(std::string& path);
MetaData ParseMetaData(std::string& path);
std::ostream& operator<<(std::ostream& os, MetaData& data);
void ParseAndPrintAll(std::string& path);



std::vector<char> GetVectorData(std::string& path) {
    // read .mp3 for bytes in vector

    std::vector<char> vec_data;

    std::ifstream fin(path, std::ios::binary);
    if(!fin.is_open()) {
        std::cerr << "Open failed!" << std::endl;
        exit(1);
    }

    char c;
    while(fin.get(c)) {
        vec_data.push_back(c);
    }
    fin.close();
    return vec_data;
}


MetaData ParseMetaData(std::string& path) {
    std::vector<char> vec_data = GetVectorData(path);
    
    if(vec_data.size() < 128) {
        std::cerr << "Wtf bro?" << std::endl;
        exit(1);
    }

    MetaData data;
    memset((void*)(&data), 0, sizeof(data));
    size_t start = vec_data.size() - 128;

    // get TAG
    for(size_t i = 0; i < TAG_LEN; i++) {
        data.TAG[i] = vec_data[start + i];
    }
    start += TAG_LEN;
    
    // get name
    for(size_t i = 0; i < NAME_LEN; i++) {
        data.name[i] = vec_data[start + i];
    }
    start += NAME_LEN;

    // get singer
    for(size_t i = 0; i < SINGER_LEN; i++) {
        data.singer[i] = vec_data[start + i];
    }
    start += SINGER_LEN;

    // get album
    for(size_t i = 0; i < ALBUM_LEN; i++) {
        data.album[i] = vec_data[start + i];
    }
    start += ALBUM_LEN;

    // get year
    for(size_t i = 0; i < YEAR_LEN; i++) {
        data.year[i] = vec_data[start + i];
    }
    start += YEAR_LEN;

    // get comment
    for(size_t i = 0; i < COMMENT_LEN; i++) {
        data.comment[i] = vec_data[start + i];
    }
    start += COMMENT_LEN;

    // get zero byte
    for(size_t i = 0; i < ZERO_BYTE_LEN; i++) {
        data.zero_byte = vec_data[start + i];
    }
    start += ZERO_BYTE_LEN;

    // get track_number
    for(size_t i = 0; i < TRACK_NUMBER_LEN; i++) {
        data.track_number = vec_data[start + i];
    }
    start += TRACK_NUMBER_LEN;

    // get genre
    for(size_t i = 0; i < GENRE_LEN; i++) {
        data.genre = vec_data[start + i];
    }
    start += GENRE_LEN;

    return data;
}



std::ostream& operator<<(std::ostream& os, MetaData& data) {
    os << "Name:\t" << data.name << std::endl;
    os << "Singer:\t" << data.singer << std::endl;
    os << "Album:\t" << data.album << std::endl;
    os << "Year:\t" << data.year << std::endl;
    os << "Comment:\t" << data.comment << std::endl;
    os << "Zero byte:\t" << data.zero_byte << std::endl;
    os << "Track number:\t" << data.track_number << std::endl;
    os << "Genre:\t" << data.genre << std::endl;
    return os;
}

void ParseAndPrintAll(std::string& path) {
    MetaData data = ParseMetaData(path);
    std::cout << data << std::endl;
}


bool is_valid_file(std::string& path) {
    return (path.length() > 4) && (path.substr(path.length() - 3, 3) == "mp3");
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cerr << "Usage: ./id3_reader <filename.mp3>" << std::endl;
        throw std::invalid_argument("");
    }
    std::string path = std::string(argv[1]);
    if(argc == 2 && !is_valid_file(path)) {
        std::cerr << "File " << argv[1] << " have to be valid!" << std::endl;
        throw std::invalid_argument("");
    }
    ParseAndPrintAll(path);
    return 0;
}

