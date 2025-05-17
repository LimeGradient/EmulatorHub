#pragma once

#include <string>

namespace EmuHub {
    class ApplicationConfig {
    public:
        static ApplicationConfig* get() {
            static ApplicationConfig instance;
            return &instance;
        }

        std::string version = "0.1.0";
    };
}