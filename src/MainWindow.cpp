#include <MainWindow.hpp>
#include <MainFrame.hpp>

bool MainWindow::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show();
    return true;
}