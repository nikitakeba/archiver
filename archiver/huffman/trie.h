#ifndef TRIE
#define TRIE

#include <cstdint>
#include <map>
#include <string>
#include "node.h"

void Traverse(Node* node, int len, std::map<uint16_t, int>& ans);

std::map<uint16_t, size_t> GetCodes(Node* root);
#endif
