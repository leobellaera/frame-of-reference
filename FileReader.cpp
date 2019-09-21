//
// Created by leobellaera on 12/9/19.
//

#include "FileReader.h"
#include <string.h>
#include <iostream>
#include <cstring>
#include <endian.h>

#define UINT32_SIZE 4
#define SUCCESS 0
#define EOF_REACHED 1
#define NO_BLOCK_TO_READ 2

FileReader::FileReader(char* path, int block_size) :
    block_size(block_size) {
    if (strcmp(path, "-")  != 0) {
        read_from_stdin = false;
        stream.open(path, std::ifstream::binary);
    } else {
        read_from_stdin = true;
    }
}

int FileReader::readBlock(std::vector<uint32_t> &destin, int block_to_read) {
    std::unique_lock<std::mutex> lock(m);
    std::istream& input = read_from_stdin ? std::cin : stream;
    input.seekg(UINT32_SIZE * block_size * block_to_read);
    if (input.fail()) {
        return NO_BLOCK_TO_READ;
    }
    int state = SUCCESS;
    int i = 0;
    while (i < block_size && state == SUCCESS) {
        if (this->readSample(destin, input) == EOF_REACHED && i == 0) {
            return NO_BLOCK_TO_READ;
        }
        i++;
    }
    return state;
}

int FileReader::readSample(std::vector<uint32_t> &destin, std::istream& input){
    char buf[UINT32_SIZE];
    uint32_t numb;
    input.read(buf, UINT32_SIZE);
    if (input.eof()) {
        return EOF_REACHED;
    } else {
        std::memcpy(&numb, buf, UINT32_SIZE);
        numb = be32toh(numb);
        destin.push_back(numb);
        return SUCCESS;
    }
}

FileReader::~FileReader() {}
