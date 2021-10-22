#ifndef WRITER
#define WRITER

#include <fstream>
#include <vector>

class Writer : public std::ofstream{
public:
    Writer(std::string_view file);

    void close();
    void WriteBit(bool x);
    void WriteNewCntBits(uint16_t x);
    void WriteCode(std::vector<bool> &v);

private:
    std::string_view file_name_;
    unsigned char c_ = 0;
    size_t pos_ = 0;
};
#endif
