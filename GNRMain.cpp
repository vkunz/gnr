/***************************************************************
 * Name:      GNRMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#include "GNRMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(GNRFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(GNRFrame)
const long GNRFrame::idMenuQuit = wxNewId();
const long GNRFrame::idMenuAbout = wxNewId();
const long GNRFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRFrame,wxFrame)
    //(*EventTable(GNRFrame)
    //*)
END_EVENT_TABLE()

GNRFrame::GNRFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(GNRFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;
    
    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(992,472));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnAbout);
    //*)
}

GNRFrame::~GNRFrame()
{
    //(*Destroy(GNRFrame)
    //*)
}

void GNRFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void GNRFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
