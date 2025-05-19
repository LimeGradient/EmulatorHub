#pragma once

#include <string>
#include <vector>

namespace EmuHub {
    struct ConfigFile {
        std::vector<std::string> romPaths;
    };

    class ApplicationConfig {
    public:
        static ApplicationConfig* get() {
            static ApplicationConfig instance;
            return &instance;
        }

        std::string version = "0.1.0";
        ConfigFile configFile = ConfigFile();
    };
}