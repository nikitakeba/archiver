#include <string>
#include <vector>
#include <map>
#include "decode.h"

namespace {

uint16_t GetSymbol(Reader &in, Node *current_node) {
    while (!current_node->is_leave) {
        bool c = in.GetBit();
        if (!c) {
            current_node = current_node->left.get();
        } else {
            current_node = current_node->right.get();
        }
    }
    return current_node->c;
}

std::map<uint16_t, size_t> RestoreLengths(std::vector<uint16_t> &symbols, std::map<int, int> &mp) {
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
    return s;
}

void ReadAdditionalInfo(Reader &in, std::vector<uint16_t> &symbols, std::map<int, int> &mp) {
    uint16_t symbols_count = in.GetNewCntBits();
    for (size_t i = 0; i < symbols_count; i++) {
        uint16_t c = in.GetNewCntBits();
        symbols.push_back(c);
    }
    uint16_t cnt = 0;
    int len = 1;
    while (cnt < symbols.size()) {
        uint16_t c = in.GetNewCntBits();
        mp[len] = c;
        cnt += c;
        len++;
    }
}
}  // namespace

void Decoder::Decode(std::string &archive_name) {
    Reader in(archive_name);
    std::vector<uint16_t> symbols;
    std::map<int, int> mp;

    ReadAdditionalInfo(in, symbols, mp);

    std::map<uint16_t, size_t> s = RestoreLengths(symbols, mp);

    std::map<uint16_t, std::vector<bool>> codes = Huffman::GetCanonicalCodes(s);

    std::unique_ptr<Node> root = Huffman::BuildTrieByCodes(codes);

    while (true) {
        std::string filename;
        while (true) {
            uint16_t c = GetSymbol(in, root.get());
            if (c == FILENAME_END) {
                break;
            } else {
                filename += static_cast<char>(c);
            }
        }
        bool f = true;
        std::ofstream out(filename.data());
        while (true) {
            uint16_t c = GetSymbol(in, root.get());
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
}
