#include "Writer.h"
#include "io_consts.h"

Writer::Writer(std::string_view file) : std::ofstream(file.data(), std::ios::binary) {
    file_name_ = file;
    pos_ = 0;
}
void Writer::WriteBit(bool x) {
    if (x) {
        c_ |= (1 << (CNT_BITS - 1 - pos_));
    }
    pos_++;
    if (pos_ == CNT_BITS) {
        put(c_);
        c_ = 0;
        pos_ = 0;
    }
}
void Writer::WriteNewCntBits(uint16_t x) {
    for (int i = NEW_CNT_BITS - 1; i >= 0; i--) {
        bool bit = (x & (1 << i));
        if (bit) {
            WriteBit(true);
        }
        else {
            WriteBit(false);
        }
    }
}
void Writer::WriteCode(std::vector<bool>& v) {
    for (auto u : v) {
        WriteBit(u);
    }
}
void Writer::close() {
    put(c_);
    pos_ = 0;
    basic_ofstream::close();
}
