#pragma once

#include <wx/wx.h>

#include <MainFrame.hpp>

namespace EmuHub {
    class MainWindow : public wxApp {
    public:
        bool OnInit() override;
    
    private:
        MainFrame* frame;
    };
}