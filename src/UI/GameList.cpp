#include "UI/GameList.hpp"

#include <roms/ROMManager.hpp>

namespace EmuHub {
    GameList::GameList(wxWindow* parent, wxWindowID id) : wxScrolledWindow(parent, id) {
        auto romPaths = ROMManager::get()->getLoadedROMPaths();

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        for (int w=1; w<=120; w++)
        {
            wxButton* b = new wxButton(this, wxID_ANY, wxString::Format(wxT("Button %i"), w));
            sizer->Add(b, 0, wxALL, 3);
        }

        this->SetSizer(sizer);
        this->FitInside();
        this->SetScrollRate(5, 5);
    }
}