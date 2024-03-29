//
// Created by leobellaera on 20/9/19.
//

#include "BlocksProcessor.h"
#include <vector>

#define REFERENCE_SIZE 4
#define SUCCESS 0
#define EOF_REACHED 1
#define NO_BLOCK_TO_READ -1

BlocksProcessor::BlocksProcessor(BlockingQueue* queue,
        FileReader &fr, int n, int slot, int block_size) :
    queue(queue),
    file_reader(fr),
    block_compressor(block_size),
    processors_amount(n),
    slot(slot),
    block_size(block_size) {}

void BlocksProcessor::run() {
    int state = SUCCESS;
    int block_to_read = slot;
    while (state == SUCCESS) {
        state = process_block(block_to_read);
        block_to_read += processors_amount;
    }
    return;
}

int BlocksProcessor::process_block(int block_to_read) {
    std::vector<uint32_t> numbs;
    int state = file_reader.readBlock(numbs, block_to_read);
    if (state == NO_BLOCK_TO_READ) {
        queue->close();
        return NO_BLOCK_TO_READ;
    }
    Block block(numbs, block_size);
    std::vector<uint8_t> compressed_block(REFERENCE_SIZE);
    block_compressor.compressBlock(block, compressed_block);
    queue->push(compressed_block);
    if (state == EOF_REACHED) {
        queue->close();
    }
    return state;
}

BlocksProcessor::~BlocksProcessor() {}
