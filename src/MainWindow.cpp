#include <MainWindow.hpp>

#include <spdlog/spdlog.h>

#include <roms/parsers/DATParser.hpp>
#include <roms/ROMManager.hpp>

namespace EmuHub {
    bool MainWindow::OnInit() {
        DATParser::get()->loadFile("./ds.dat", ConsoleType::NintendoDS);
        auto isROM = ROMManager::get()->checkROMHash("./diamond.nds");

        frame = new MainFrame();
        frame->Show();
        return true;
    }
}