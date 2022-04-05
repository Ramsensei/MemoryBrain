#ifndef GUI_H
#define GUI_H
#include <wx/wx.h>
#include "client.cpp"


class GUI : public wxFrame
{
private:
    wxButton* btnCambio;
    wxBitmapButton* btnImg;
    Client* client;
public:
    GUI(const wxString& title);
    void changeImg(wxCommandEvent & event);
};

const int ID_BTNIMG = 20;

#endif