#include <MainWindow.hpp>

#include <spdlog/spdlog.h>

#include <roms/parsers/DATParser.hpp>
#include <roms/ROMManager.hpp>

namespace EmuHub {
    bool MainWindow::OnInit() {
        DATParser::get()->loadFile("./datfiles/ds.dat", ConsoleType::NintendoDS);

        frame = new MainFrame();
        frame->Show();
        return true;
    }
}

wxIMPLEMENT_APP_NO_MAIN(EmuHub::MainWindow);

int main(int argc, char* argv[]) {    
    wxApp::SetInstance(new EmuHub::MainWindow());
    return wxEntry(argc, argv);
}