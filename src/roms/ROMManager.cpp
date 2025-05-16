#include "roms/ROMManager.hpp"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

#include <roms/parsers/DATParser.hpp>

namespace EmuHub {
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
}