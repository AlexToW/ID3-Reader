#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

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
    char TAG[TAG_LEN];
    char name[NAME_LEN];
    char singer[SINGER_LEN];
    char album[ALBUM_LEN];
    char year[YEAR_LEN];
    char comment[COMMENT_LEN];
    char zero_byte;
    char track_number;
    char genre;
};


typedef struct MetaData MetaData;


bool is_good_file(std::string path) {
    return true;
}


std::vector<char> GetVectorData(std::string path) {
     if(!is_good_file(path)) {
        std::cerr << "Bad file!" << std::endl;
        exit(1);
    }

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


MetaData ParseMetaData(std::string path) {
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

    return data;
}



std::ostream& operator<<(std::ostream& os, MetaData& data) {
    os << "Name:\t" << data.name << std::endl;
    os << "Singer:\t" << data.singer << std::endl;
    os << "Album:\t" << data.album << std::endl;
    os << "Year:\t" << data.year << std::endl;
    return os;
}



void test() {
    std::string path = "file.mp3";
    std::ifstream fin(path, std::ios::binary);
    if(!fin.is_open()) {
        std::cout << "Open failed!" << std::endl;
    }

    std::vector<char> v;
    char c;
    while(fin.get(c)) {
        v.push_back(c);
    }
    fin.close();
    std::cout << v.size() << std::endl;
    size_t size = v.size();
    for(size_t i = v.size() - 128; i < size; i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << std::endl;
}

void ParseAll(std::string path) {
    MetaData data = ParseMetaData(path);
    std::cout << data << std::endl;
}


int main(/*int argc, char* argv[]*/) {
    std::string path = "file.mp3";
    ParseAll(path);
    return 0;
}

