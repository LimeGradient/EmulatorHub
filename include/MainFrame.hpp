#pragma once

#include <wx/wx.h>

namespace EmuHub {
    class MainFrame : public wxFrame {
    public:
        MainFrame();

    private:
        void OnExit(wxCommandEvent& event);
    };
}