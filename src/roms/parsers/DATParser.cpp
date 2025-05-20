#include "roms/parsers/DATParser.hpp"

#include <vector>

#include <pugixml.hpp>
#include <spdlog/spdlog.h>

namespace EmuHub {
    void DATParser::loadFile(std::string path, ConsoleType type) {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(path.c_str());
        
        if (result) {
            std::vector<DATGame> games;
            auto datafileNode = doc.child("datafile");
            for (auto game : datafileNode.select_nodes("//game")) {
                auto datGame = DATGame(
                    game.node().child("rom").attribute("sha256").value(), 
                    game.node().child("description").value(),
                    game.node().child("rom").attribute("name").value()
                );
                
                    games.push_back(datGame);
            }

            datGames.insert(std::make_pair(type, games));
        } else {
            spdlog::error("Error opening {} with description: {}", path, result.description());
        }
    }
}