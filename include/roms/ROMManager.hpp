#pragma once

#include <string>
#include <vector>

#include <config/ApplicationConfig.hpp>
#include <roms/types/ConsoleTypes.hpp>
#include <roms/types/DATGame.hpp>
#include <roms/types/ROM.hpp>

namespace EmuHub {
    class ROMManager {
    public:
        static ROMManager* get() {
            static ROMManager instance;
            return &instance;
        }

        void init();

        void addROMPath(std::string path);
        bool checkROMHash(std::string romPath);

        std::vector<std::string> getLoadedROMPaths();

        ROM getROM(std::string romPath);
    
    private:
        ApplicationConfig* config;
        std::vector<std::string> romPaths;
    };
}