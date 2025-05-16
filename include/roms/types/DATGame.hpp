#pragma once

#include <string>

namespace EmuHub {
    struct DATGame {
        std::string hash;
        std::string name;

        DATGame(std::string hash, std::string name) : hash(hash), name(name) {}
    };
}