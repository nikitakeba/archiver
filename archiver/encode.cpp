#include <map>
#include "encode.h"
#include "io/Writer.h"
#include "consts.h"
#include "Huffman/huffman.h"

void Encode(std::string &archive_name, std::vector<std::string> &filenames) {
    std::map<uint16_t, int> cnt;
    for (size_t i = 0; i < filenames.size(); i++) {
        for (auto c : filenames[i]) {
            cnt[c]++;
        }
        cnt[FILENAME_END]++;
        std::ifstream in(filenames[i].data());
        unsigned char c = in.get();
        while (in.good()) {
            cnt[c]++;
            c = in.get();
        }
        if (i != filenames.size() - 1) {
            cnt[ONE_MORE_FILE]++;
        }
    }
    cnt[ARCHIVE_END]++;

    std::vector<uint16_t> symbols;
    std::vector<int> frequency;
    for (auto u : cnt) {
        symbols.push_back(u.first);
        frequency.push_back(u.second);
    }

    std::map<uint16_t, std::vector<bool>> code = GetCanonicalCodesBySymbols(symbols, frequency);

    std::vector<std::pair<int, uint16_t>> v;

    std::map<size_t, int> cnt_with_len;

    size_t max_symbol_code_size = 0;

    for (auto u : cnt) {
        v.push_back(std::make_pair(code[u.first].size(), u.first));
        cnt_with_len[code[u.first].size()]++;
        max_symbol_code_size = std::max(max_symbol_code_size, code[u.first].size());
    }

    sort(v.begin(), v.end());

    Writer out(archive_name);

    out.WriteNewCntBits(static_cast<uint16_t>(v.size()));

    for (auto u : v) {
        out.WriteNewCntBits(u.second);
    }

    for (size_t i = 1; i <= max_symbol_code_size; i++) {
        out.WriteNewCntBits(cnt_with_len[i]);
    }

    for (size_t i = 0; i < filenames.size(); i++) {
        for (auto c : filenames[i]) {
            out.WriteCode(code[c]);
        }
        out.WriteCode(code[FILENAME_END]);

        std::ifstream in(filenames[i].data());
        unsigned char c = in.get();
        while (in.good()) {
            out.WriteCode(code[c]);
            c = in.get();
        }

        if (i != filenames.size() - 1) {
            out.WriteCode(code[ONE_MORE_FILE]);
        }
    }

    out.WriteCode(code[ARCHIVE_END]);
    out.close();
}
