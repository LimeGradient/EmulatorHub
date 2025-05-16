#pragma once

#include <string>

namespace EmuHub {
    enum TagCategory {
        None,
        Parenthesized,
        Bracketed
    };

    struct RomTag {
        TagCategory category;
        std::string slug;
    };
}