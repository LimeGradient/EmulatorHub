#pragma once

#include <string>
#include <vector>

#include <roms/types/DATGame.hpp>

namespace EmuHub {
    struct ROM {
        DATGame game;
        std::string path;
        std::vector<uint8_t> logoBytes;

        ROM (DATGame game) : game(game) {}
    };
}