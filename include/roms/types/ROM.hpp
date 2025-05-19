#pragma once

#include <string>

#include <roms/types/DATGame.hpp>

namespace EmuHub {
    struct ROM {
        DATGame game;
        std::string path;
    };
}