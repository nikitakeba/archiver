#include <cstring>
#include <iostream>
#include <vector>
#include "Parser.h"
#include "encode.h"
#include "decode.h"

void Parse(int argc, char* argv[]) {
    if (std::strcmp(argv[1], "-h") == 0) {
        std::cout << "Enter archiver -c archive_name file1 [file2 ...] to encode files and save them into archive\n"
                     "Enter archiver -d archive_name to decode files from archive and save them into current directory\n"
                     "Enter archiver -h for help\n";
    }
    else if (std::strcmp(argv[1], "-c") == 0) {
        std::vector <std::string> file_names;
        std::string archive_name = argv[2];
        for (int i = 3; i < argc; i++) {
            file_names.push_back(argv[i]);
        }
        Encode(archive_name, file_names);
    }
    else {
        std::string archive_name = argv[2];
        Decode(archive_name);
    }
}
