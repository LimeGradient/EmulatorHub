#include "roms/ROMManager.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>

#include <glaze/glaze.hpp>
#include <mz.h>
#include <mz_strm.h>
#include <mz_zip.h>
#include <mz_zip_rw.h>
#include <openssl/sha.h>
#include <spdlog/spdlog.h>

#include <config/ApplicationConfig.hpp>
#include <roms/parsers/DATParser.hpp>

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

    bool ROMManager::checkROMHash(std::string romPath, ConsoleType type) {
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
        auto games = datParser->getDATGames().at(type);
        for (auto game : games) {
            if (game.hash == finalHash) {
                return true;
            }
        }

        return false;
    }

    ROM ROMManager::getROM(fs::path romPath) {
        auto datGames = DATParser::get()->getDATGames();
        for (auto [key, value] : datGames) {
            if (this->checkROMHash(romPath.string(), key)) {
                
            }
        }
    }

    std::vector<uint8_t> ROMManager::getROMLogo(fs::path romPath) {
        std::vector<uint8_t> logo;

        auto zipReader = mz_zip_reader_create();
        if (!zipReader) {
            return logo;
        }

        auto err = mz_zip_reader_open_file(zipReader, romPath.c_str());
        if (err != MZ_OK) {
            mz_zip_reader_delete(&zipReader);
            return logo;
        }

        err = mz_zip_reader_locate_entry(zipReader, "logo.png", 0);
        if (err != MZ_OK) {
            mz_zip_reader_close(zipReader);
            mz_zip_reader_delete(&zipReader);
            return logo;
        }

        mz_zip_file* fileInfo = NULL;
        err = mz_zip_reader_entry_get_info(zipReader, &fileInfo);
        if (err != MZ_OK || fileInfo == NULL) {
            mz_zip_reader_close(zipReader);
            mz_zip_reader_delete(&zipReader);
            return logo;
        }

        uint64_t uncompressedSize = fileInfo->uncompressed_size;
        logo.reserve(uncompressedSize);
        err = mz_zip_reader_entry_open(zipReader);
        if (err != MZ_OK) {
            mz_zip_reader_close(zipReader);
            mz_zip_reader_delete(&zipReader);
            return logo;
        }

        
    }

    std::vector<std::string> ROMManager::getLoadedROMPaths() {
        return romPaths;
    }
}