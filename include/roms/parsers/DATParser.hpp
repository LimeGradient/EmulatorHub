#pragma once

#include <string>
#include <map>
#include <vector>

#include <roms/types/DATGame.hpp>
#include <roms/types/ConsoleTypes.hpp>

namespace EmuHub {
    class DATParser {
    public:
        static DATParser* get() {
            static DATParser instance;
            return &instance;
        }

        void init();
        void loadFile(std::string path, ConsoleType type);

        std::map<ConsoleType, std::vector<DATGame>> getDATGames() {
            return datGames;
        }
    
    private:
        std::map<ConsoleType, std::vector<DATGame>> datGames;
    };
}