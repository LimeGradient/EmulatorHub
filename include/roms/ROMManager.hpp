#pragma once

#include <string>

#include <roms/types/DATGame.hpp>

namespace EmuHub {
    class ROMManager {
    public:
        static ROMManager* get() {
            static ROMManager instance;
            return &instance;
        }

        bool checkROMHash(std::string romPath);
    };
}