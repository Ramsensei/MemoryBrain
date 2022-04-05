#include "gui.h"

GUI::GUI(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 500))
{
    wxPanel *panel = new wxPanel(this);
    btnImg = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("assets/1.png"), 
        wxBITMAP_TYPE_PNG), wxPoint(20, 20));
    
    btnCambio = new wxButton(panel, ID_BTNIMG, wxT("Quit"), wxPoint(140, 20));
    
    Connect(ID_BTNIMG, wxEVT_COMMAND_BUTTON_CLICKED, 
        wxCommandEventHandler(GUI::changeImg));
    
    std::string ip = "192.168.0.39";
    client = new Client(ip, 8080);
    Centre();
}

void GUI::changeImg(wxCommandEvent & event){
    client->sendMessage();
    fprintf(stdout, "Mensaje en gui: %c \n", client->buff_rx->img);
    // btnImg->SetBitmapLabel(client->buff_rx->img);
    
}