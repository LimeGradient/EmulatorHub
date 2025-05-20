#pragma once

#include <string>

namespace EmuHub {
    struct DATGame {
        std::string hash;
        std::string name;
        std::string filename;

        DATGame(std::string hash, std::string name, std::string filename) : hash(hash), name(name), filename(filename) {}
    };
}