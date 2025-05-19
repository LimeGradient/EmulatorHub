#pragma once

#include <wx/wx.h>

namespace EmuHub {
    class GameList : public wxScrolledWindow {
    public:
        GameList(wxWindow* parent, wxWindowID id);
    };
}