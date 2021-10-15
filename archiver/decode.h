#include "io/Reader.h"
#include "consts.h"
#include "Huffman/huffman.h"

void Decode(std::string &archive_name);

uint16_t GetSymbol(Node* current_node);
