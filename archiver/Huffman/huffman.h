#include <vector>
#include <queue>
#include <cstdint>
#include <string>
#include <map>

#include "trie.h"
#include "minheap.h"

Node *Build(std::vector<uint16_t> &symbols, std::vector<int> &frequency);

std::map<uint16_t, size_t> GetLengths(std::vector<uint16_t> &symbols, std::vector<int> &frequency);

std::map<uint16_t, std::vector<bool>> GetCanonicalCodes(std::map<uint16_t, size_t> &mp);


Node* BuildTrieByCodes(std::map<uint16_t, std::vector<bool>>& codes);
void Add(Node* node, size_t pos, std::vector<bool>& code, uint16_t c);

std::map<uint16_t, std::vector<bool>> GetCanonicalCodesBySymbols(std::vector<uint16_t>& symbols, std::vector<int>& frequency);
