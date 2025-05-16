#include <MainWindow.hpp>
#include <MainFrame.hpp>

namespace EmuHub {
    bool MainWindow::OnInit() {
        MainFrame* frame = new MainFrame();
        frame->Show();
        return true;
    }
}