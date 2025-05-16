#pragma once

#include <wx/wx.h>

namespace EmuHub {
    class MainWindow : public wxApp {
    public:
        bool OnInit() override;
    };

    wxIMPLEMENT_APP(MainWindow);
}