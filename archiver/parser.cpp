#include <cstring>
#include <iostream>
#include <vector>
#include "parser.h"
#include "encode.h"
#include "decode.h"

void Parse(int argc, char* argv[]) {
    if (argc >= 4 && std::strcmp(argv[1], "-c") == 0) {
        std::vector<std::string> file_names;
        std::string archive_name = argv[2];
        for (int i = 3; i < argc; i++) {
            file_names.push_back(argv[i]);
        }
        Encoder::Encode(archive_name, file_names);
    } else if (argc == 3 && std::strcmp(argv[1], "-d") == 0) {
        std::string archive_name = argv[2];
        Decoder::Decode(archive_name);
    } else {
        std::cout << "Enter -c archive_name file1 [file2 ...] to encode files and save them into archive\n"
                     "Enter -d archive_name to decode files from archive and save them into current directory\n"
                     "Enter -h for help\n";
    }
}
