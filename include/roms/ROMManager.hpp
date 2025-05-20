#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <config/ApplicationConfig.hpp>
#include <roms/types/ConsoleTypes.hpp>
#include <roms/types/DATGame.hpp>
#include <roms/types/ROM.hpp>

namespace fs = std::filesystem;

namespace EmuHub {
    class ROMManager {
    public:
        static ROMManager* get() {
            static ROMManager instance;
            return &instance;
        }

        void init();

        void addROMPath(std::string path);
        bool checkROMHash(std::string romPath, ConsoleType type);

        std::vector<std::string> getLoadedROMPaths();

        ROM getROM(fs::path romPath);

        std::vector<uint8_t> getROMLogo(fs::path romPath);
    
    private:
        ApplicationConfig* config;
        std::vector<std::string> romPaths;
    };
}