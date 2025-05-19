#pragma once

#include <wx/wx.h>

#include <roms/ROMManager.hpp>

namespace EmuHub {
    class MainFrame : public wxFrame {
    public:
        MainFrame();

    private:
        void OnClose(wxCloseEvent& event);
        void OnExit(wxCommandEvent& event); 
        void OnAddROMPath(wxCommandEvent& event);

        enum {
            ID_AddROMPath
        };

        ROMManager* romManager;
    };
}