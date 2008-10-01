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
#include <wx/wx.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
	short_f, long_f
};

// just a comment

wxString wxbuildinfo(wxbuildinfoformat format)
{
	wxString wxbuild(wxVERSION_STRING);

	if (format == long_f)
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
const long GNRFrame::idMenuLoad = wxNewId();
const long GNRFrame::idMenuSave = wxNewId();
const long GNRFrame::idMenuQuit = wxNewId();
const long GNRFrame::idMenuHelp = wxNewId();
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
	wxMenuItem* MenuItem4;
	wxMenuBar* MenuBar1;
	wxMenu* Menu1;
	wxMenu* Menu2;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(690,311));
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuSave, _("&Speichern\tAlt-S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&Datei"));
	Menu2 = new wxMenu();
	MenuItem5 = new wxMenuItem(Menu2, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	Menu2->Append(MenuItem5);
	MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&Über\tAlt-F1"), _("Informationen über GNR..."), wxITEM_NORMAL);
	Menu2->Append(MenuItem2);
	MenuBar1->Append(Menu2, _("&Hilfe"));
	SetMenuBar(MenuBar1);
	StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar1);

	m_canvas = new TestCanvas(this, wxID_ANY, wxDefaultPosition,
        wxSize(300, 300), wxSUNKEN_BORDER);

	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnAbout);
	Connect(idMenuLoad,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnFileOpen);
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
	wxMessageBox(msg, _("GNR"));
	wxMessageBox(msg, _("BlaBlub"));
}


void GNRFrame::OnRadioBox1Select(wxCommandEvent& event)
{
}
void GNRFrame::OnFileOpen(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT(".obj-datei oeffnen"), wxT(""), wxT(""), wxT(""), wxT("DXF Drawing (*.dxf)|*.dxf)|All files (*.*)|*.*"), wxFD_OPEN);

    wxChar* m_char = new char[filename.length() + 1];
    strcpy(m_char, filename.wc_str());

    wxMessageBox(m_char);

    //m_canvas->pmodel =  glmReadOBJ(filename.c_str());
	wxMessageBox(filename, _("Bla"));
}
