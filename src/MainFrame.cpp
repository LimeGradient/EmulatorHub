#include <MainFrame.hpp>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <config/ApplicationConfig.hpp>
#include <UI/GameList.hpp>

namespace EmuHub {
    MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Emulator Hub") {
        SetSize(1280, 720);

        romManager = ROMManager::get();

        // Set Menu Bar
        wxMenu* menuFile = new wxMenu;
        menuFile->Append(ID_AddROMPath, "Add ROM Path", "Add a path to search for ROM's");
        menuFile->Append(wxID_EXIT, "Exit...\tAlt+F4", "Exits the program");

        wxMenuBar* menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");

        SetMenuBar(menuBar);
        CreateStatusBar();
        SetStatusText(fmt::format("Welcome to EmulatorHub Version {}", ApplicationConfig::get()->version));

        Bind(wxEVT_MENU, &MainFrame::OnAddROMPath, this, ID_AddROMPath);
        Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

        // Other GUI

        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        
        GameList* gameList = new GameList(this, wxID_ANY);
        sizer->Add(gameList, 1, wxEXPAND);
        this->SetSizer(sizer);
    }

    void MainFrame::OnExit(wxCommandEvent& event) {
        Close(true);
    }

    void MainFrame::OnAddROMPath(wxCommandEvent& WXUNUSED(event)) {
        wxDirDialog* openDialog = new wxDirDialog(this, "Select a folder to add", wxEmptyString);
        if (openDialog->ShowModal() == wxID_OK) {
            romManager->addROMPath(openDialog->GetPath().ToStdString());
        }
    }
}