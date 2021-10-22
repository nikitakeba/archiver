#ifndef HUFFMAN
#define HUFFMAN

#include <vector>
#include <queue>
#include <cstdint>
#include <string>
#include <map>
#include <algorithm>
#include <memory>

#include "trie.h"
#include "minheap.h"

class Huffman {
public:
    static std::map<uint16_t, std::vector<bool>> GetCanonicalCodes(std::map<uint16_t, size_t>& mp);

    static std::unique_ptr<Node> BuildTrieByCodes(std::map<uint16_t, std::vector<bool>>& codes);

    static std::map<uint16_t, std::vector<bool>> GetCanonicalCodesBySymbols(std::vector<uint16_t>& symbols,
                                                                            std::vector<int>& frequency);
};
#endif
