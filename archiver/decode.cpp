#include <string>
#include <vector>
#include <map>
#include "decode.h"

uint16_t GetSymbol(Reader& in, Node* current_node) {
    while (!current_node->is_leave) {
        bool c = in.GetBit();
        if (!c) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }
    return current_node->c;
}

void Decode(std::string& archive_name) {
    Reader in(archive_name);
    uint16_t symbols_count = in.GetNewCntBits();
    std::vector<uint16_t> symbols;
    for (size_t i = 0; i < symbols_count; i++) {
        uint16_t c = in.GetNewCntBits();
        symbols.push_back(c);
    }
    uint16_t cnt = 0;
    int len = 1;
    std::map<int, int> mp;
    while (cnt < symbols.size()) {
        uint16_t c = in.GetNewCntBits();
        mp[len] = c;
        cnt += c;
        len++;
    }
    std::vector<size_t> lens;
    int id = 1;
    for (size_t i = 0; i < symbols.size(); i++) {
        while (mp[id] == 0) {
            id++;
        }
        lens.push_back(id);
        mp[id]--;
    }

    std::map<uint16_t, size_t> s;

    for (size_t i = 0; i < symbols.size(); i++) {
        s.insert({symbols[i], lens[i]});
    }

    std::map<uint16_t, std::vector<bool>> codes = GetCanonicalCodes(s);

    Node* root = BuildTrieByCodes(codes);

    while (true) {
        std::string filename;
        while (true) {
            uint16_t c = GetSymbol(in, root);
            if (c == FILENAME_END) {
                break;
            } else {
                filename += static_cast<char>(c);
            }
        }
        bool f = true;
        std::ofstream out(filename.data());
        while (true) {
            uint16_t c = GetSymbol(in, root);
            if (c == ARCHIVE_END) {
                f = false;
                break;
            }
            if (c == ONE_MORE_FILE) {
                break;
            }
            out.put(c);
        }
        if (!f) {
            break;
        }
    }
    if (root) {
        delete root;
    }
}
