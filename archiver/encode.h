#ifndef ENCODE
#define ENCODE

#include <vector>
#include <string>

class Encoder {
public:
    static void Encode(std::string &archive_name, std::vector<std::string> &filenames);
};
#endif
