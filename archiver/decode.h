#ifndef DECODE
#define DECODE

#include "io/reader.h"
#include "consts.h"
#include "huffman/huffman.h"

class Decoder {
public:
    static void Decode(std::string& archive_name);
};
#endif
