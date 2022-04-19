#include "gui.h"

GUI::GUI(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(730, 640))
{
    SetMinSize(wxSize(730, 640));
    SetMaxSize(wxSize(730, 640));
    wxPanel *panel = new wxPanel(this);
    // btnImg = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("assets/1.png"), 
    //     wxBITMAP_TYPE_PNG), wxPoint(20, 20));
    int x = 5, y = 5;
    for(int m = 1; m < 7 ; m++){
        for (int n = 1; n < 7 ; n++){
            wxBitmapButton *btn =new wxBitmapButton(this, m*10 +n , wxBitmap("assets/0.png", wxBITMAP_TYPE_PNG), wxPoint(x, y), wxSize(120,100));
            buttons.append(btn);
            x = x + 120;
            Connect(m*10 +n, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(GUI::OnClick));
        }
        x = 5;
        y = y + 100;
    }
    // Connect(ID_BTNIMG, wxEVT_COMMAND_BUTTON_CLICKED, 
    //     wxCommandEventHandler(GUI::changeImg));
    
    client = new Client(8080);
    Centre();
}

void GUI::changeImg(wxCommandEvent & event){
    client->getSize();
    // client->sendMessage();
    fprintf(stdout, "Mensaje en gui: %d \n", client->packSize->data);
    // btnImg->SetBitmapLabel(client->buff_rx->img);
    
}
void GUI::OnClick(wxCommandEvent & event){
    int id = event.GetId();
    fprintf(stdout, "Boton: %d \n", id);
    fprintf(stdout, "Imagen: %d \n", ((id%8)+1));
    client->setMessage((id%8)+1);
    client->getSize();
    client->getImage();
    buttons.getButton(id)->SetBitmapLabel(wxBitmap("rebuild.png", wxBITMAP_TYPE_PNG));
}