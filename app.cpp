#include "app.h"
#include "gui.cpp"



IMPLEMENT_APP(ClientApp)

bool ClientApp::OnInit()
{
    GUI *gui = new GUI(wxT("Simple"));
    gui->Show(true);

    return true;
}