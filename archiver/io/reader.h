#ifndef READER
#define READER

#include <fstream>

class Reader : public std::ifstream {
public:
    Reader(std::string_view file);

    bool GetBit();
    uint16_t GetNewCntBits();

private:
    std::string_view file_name_;
    unsigned char c_;
    size_t pos_ = 0;
};
#endif
