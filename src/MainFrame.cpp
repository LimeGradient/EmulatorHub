#include <MainFrame.hpp>

namespace EmuHub {
    MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Emulator Hub") {
        SetSize(1280, 720);

        // Set Menu Bar
        wxMenu* menuFile = new wxMenu;
        menuFile->Append(wxID_EXIT, "Exit...\tCmd+Q", "Exits the program");
        
        wxMenuBar* menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");

        SetMenuBar(menuBar);
        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");

        Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

        // Other GUI

    }

    void MainFrame::OnExit(wxCommandEvent& event) {
        Close(true);
    }
}