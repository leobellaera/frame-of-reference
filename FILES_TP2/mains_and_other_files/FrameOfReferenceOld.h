//
// Created by leobellaera on 15/9/19.
//

#ifndef FRAME_OF_REFERENCE_H
#define FRAME_OF_REFERENCE_H

#include "BlockCompressor.h"
#include "FileReader.h"
#include <fstream>


class FrameOfReference {
    private:
        int block_size;
        FileReader file_reader;
        std::ofstream output; //HARCODEO
        //FileWriter file_writer;
        BlockCompressor block_compressor;
        int compressBlock(int block_to_read);
    public:
        FrameOfReference(int block_size, char* infile_path, char* outfile_path);
        void compressFile();
        ~FrameOfReference();
};

#endif //FRAME_OF_REFERENCE_H
