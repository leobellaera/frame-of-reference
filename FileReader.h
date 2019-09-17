//
// Created by leobellaera on 12/9/19.
//

#ifndef TP2_FILE_H
#define TP2_FILE_H

#include <iostream>
#include <fstream>

class FileReader {
    private:
        ifstream stream;
        bool readFromStdin;
        uint32_t numbs_per_block;
        int read(std::istream& stream, uint32_t* block)
    public:
        FileReader(char* path);
        int readBlock(uint32_t* block);
        ~FileReader();

};



#endif //TP2_FILE_H