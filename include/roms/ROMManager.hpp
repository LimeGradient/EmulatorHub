#pragma once

#include <string>
#include <map>
#include <vector>

#include <config/ApplicationConfig.hpp>
#include <roms/types/ConsoleTypes.hpp>
#include <roms/types/DATGame.hpp>
#include <roms/types/ROM.hpp>

namespace EmuHub {
    class ROMManager {
    public:
        ~ROMManager();

        static ROMManager* get() {
            static ROMManager instance;
            return &instance;
        }

        void init();

        void addROMPath(std::string path);
        bool checkROMHash(std::string romPath);
    
    private:
        ApplicationConfig* config;
        std::vector<std::string> romPaths;
    };
}