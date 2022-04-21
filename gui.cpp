#include "gui.h"
#include <chrono>
#include <thread>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

GUI::GUI(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(730, 640))
{
    SetMinSize(wxSize(730, 640));
    SetMaxSize(wxSize(730, 640));
    wxPanel *panel = new wxPanel(this);
    message = 0;
    // btnImg = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("assets/1.png"),
    //     wxBITMAP_TYPE_PNG), wxPoint(20, 20));
    int x = 5, y = 5;
    for (int m = 1; m < 7; m++)
    {
        for (int n = 1; n < 7; n++)
        {
            wxBitmapButton *btn = new wxBitmapButton(this, m * 10 + n, wxBitmap("assets/0.png", wxBITMAP_TYPE_PNG), wxPoint(x, y), wxSize(120, 100));
            buttons.append(btn);
            x = x + 120;
            Connect(m * 10 + n, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnClick));
        }
        x = 5;
        y = y + 100;
    }
    // Connect(ID_BTNIMG, wxEVT_COMMAND_BUTTON_CLICKED,
    //     wxCommandEventHandler(GUI::changeImg));

    client = new Client(8080);
    Centre();
}

void GUI::changeImg(wxCommandEvent &event)
{
    client->getSize();
    // client->sendMessage();
    fprintf(stdout, "Mensaje en gui: %d \n", client->packSize->data);
    // btnImg->SetBitmapLabel(client->buff_rx->img);
}
void GUI::OnClick(wxCommandEvent &event)
{
    int id = event.GetId();

    client->setMessage((id % 8) + 1);
    client->getSize();
    message = client->getMessage();

    client->getImage();

    std::cout << "Click" << std::endl;

    buttons.getButton(id)->SetBitmapLabel(wxBitmap("rebuild.png", wxBITMAP_TYPE_PNG));
    buttons.getButton(id)->Enable(false);
    lastButtons.append(buttons.getButton(id));

    handleMessage();
}
void GUI::handleMessage()
{
    switch (message)
    {
    case 1:
        wxMessageBox(wxT("Fallaste"));
        for (int i = 0; i < lastButtons.getSize(); i++)
        {
            std::cout << lastButtons.getIndex(i)->GetId() << std::endl;
            lastButtons.getIndex(i)->SetBitmapLabel(wxBitmap("assets/0.png", wxBITMAP_TYPE_PNG));
            lastButtons.getIndex(i)->Enable(true);
        }
        lastButtons.clear();
        break;
    case 2:
        wxMessageBox(wxT("Bien Hecho"));
        lastButtons.clear();
        break;
    }
}