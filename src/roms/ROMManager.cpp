#include "roms/ROMManager.hpp"

#include <fstream>
#include <filesystem>
#include <sstream>
#include <iomanip>

#include <glaze/glaze.hpp>
#include <openssl/sha.h>
#include <spdlog/spdlog.h>

#include <config/ApplicationConfig.hpp>
#include <roms/parsers/DATParser.hpp>

namespace fs = std::filesystem;

namespace EmuHub {
    void ROMManager::init() {
        config = ApplicationConfig::get();

        if (!fs::exists("./config") || !fs::is_directory("./config")) {
            fs::create_directory("./config");
        } else {
            if (fs::exists("./config/config.json")) {
                std::ifstream file("./config/config.json");
                std::stringstream rawFileContents;
                rawFileContents << file.rdbuf();
                std::string fileContents = rawFileContents.str();
                file.close();

                glz::read_json(config->configFile, fileContents);
                romPaths = config->configFile.romPaths;
            } else {
                config->configFile = ConfigFile();
            }
        }
    }


    void ROMManager::addROMPath(std::string path) {
        romPaths.push_back(path);
    }

    bool ROMManager::checkROMHash(std::string romPath) {
        std::ifstream file(romPath, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        std::ifstream fp(romPath, std::ios::in | std::ios::binary);

        if (not fp.good()) {
            std::ostringstream os;
            os << "Cannot open \"" << romPath << "\": " << std::strerror(errno) << ".";
            throw std::runtime_error(os.str());
        }

        constexpr const std::size_t buffer_size { 1 << 12 };
        char buffer[buffer_size];

        unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

        SHA256_CTX ctx;
        SHA256_Init(&ctx);

        while (fp.good()) {
            fp.read(buffer, buffer_size);
            SHA256_Update(&ctx, buffer, fp.gcount());
        }

        SHA256_Final(hash, &ctx);
        fp.close();

        std::ostringstream os;
        os << std::hex << std::setfill('0');

        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            os << std::setw(2) << static_cast<unsigned int>(hash[i]);
        }

        std::string finalHash = os.str();

        auto datParser = DATParser::get();
        auto games = datParser->getDATGames().at(ConsoleType::NintendoDS);
        for (auto game : games) {
            if (game.hash == finalHash) {
                return true;
            }
        }

        return false;
    }

    ROM ROMManager::getROM(std::string romPath) {
        auto datGames = DATParser::get()->getDATGames();
        for (auto [key, value] : datGames) {
            for (auto game : value) {
                
            }
        }
    }

    std::vector<std::string> ROMManager::getLoadedROMPaths() {
        return romPaths;
    }
}