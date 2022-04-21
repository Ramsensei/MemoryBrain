#ifndef GUI_H
#define GUI_H
#include <wx/wx.h>
#include "client.cpp"
#include "LinkedList.cpp"


class GUI : public wxFrame
{
private:
    wxButton* btnCambio;
    wxBitmapButton* btnImg;
    Client* client;
    LinkedList buttons;
    LinkedList lastButtons;
    int message;
public:
    GUI(const wxString& title);
    void changeImg(wxCommandEvent & event);
    void OnClick(wxCommandEvent & event);
    void handleMessage();
};

const int ID_BTNIMG = 20;

#endif