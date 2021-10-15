#include "Reader.h"
#include "io_consts.h"

Reader::Reader(std::string_view file) : std::ifstream(file.data(), std::ios::binary) {
    file_name_ = file;
    pos_ = 0;
}

bool Reader::GetBit() {
    if (pos_ == 0) {
        c_ = get();
    }

    bool res;

    if (c_ & (1 << (CNT_BITS - 1 - pos_))) {
        res = true;
    } else {
        res = false;
    }
    pos_++;
    if (pos_ == CNT_BITS) {
        pos_ = 0;
    }
    return res;
}

uint16_t Reader::GetNewCntBits() {
    uint16_t ans = 0;
    for (int i = NEW_CNT_BITS - 1; i >= 0; i--) {
        bool cur = GetBit();
        if (cur) {
            ans += (1 << i);
        }
    }
    return ans;
}
