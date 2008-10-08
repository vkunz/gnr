/***************************************************************
 * Name:      GNRMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#include <wx/msgdlg.h>
#include <wx/intl.h>
#include <wx/string.h>

#include "GNRMain.h"

//helper functions
enum wxbuildinfoformat
{
	short_f, long_f
};

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
const long GNRFrame::ID_StatusBar = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRFrame,wxFrame)
	//(*EventTable(GNRFrame)
	//*)
END_EVENT_TABLE()

GNRFrame::GNRFrame(wxWindow* parent, wxWindowID id)
{
	//(*Initialize(GNRFrame)
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem1;
	wxMenuItem* MenuItem4;
	wxMenu* Menu1;
	wxMenuBar* MenuBar1;
	wxMenu* Menu2;
	
	Create(parent, wxID_ANY, _("GNR - 3D Einrichtungsplaner"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(800,600));
	SetMinSize(wxSize(640,480));
	SetFocus();
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem3 = new wxMenuItem(Menu1, idMenuLoad, _("&Öffnen\tAlt-O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuSave, _("&Speichern\tAlt-S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("&Schließen\tAlt-F4"), _("GNR schließen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&Datei"));
	Menu2 = new wxMenu();
	MenuItem5 = new wxMenuItem(Menu2, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	Menu2->Append(MenuItem5);
	MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&Über\tAlt-F1"), _("Informationen über GNR..."), wxITEM_NORMAL);
	Menu2->Append(MenuItem2);
	MenuBar1->Append(Menu2, _("&Hilfe"));
	SetMenuBar(MenuBar1);
	StatusBar1 = new wxStatusBar(this, ID_StatusBar, 0, _T("ID_StatusBar"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar1);
	Center();
	
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnAbout);
	//*)
	
	this->m_VerticalSplitter = new wxSplitterWindow(this, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	this->m_VerticalSplitter->SetMinimumPaneSize(200);
	
	this->m_Panel = new GNRTreePanel(m_VerticalSplitter, wxID_ANY);
	
	this->m_HorizontalSplitter = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	this->m_HorizontalSplitter->SetMinimumPaneSize(200);
	
	this->m_VerticalSplitter->SplitVertically(m_Panel, m_HorizontalSplitter);
	
	this->m_BottomCanvas = new TestCanvas(m_HorizontalSplitter, -1);
	//this->m_glContext = m_BottomCanvas->GetContext();
	this->m_UpperCanvas = new TestCanvas(m_HorizontalSplitter, -1);
	
	this->m_HorizontalSplitter->Initialize(m_UpperCanvas);
	this->m_HorizontalSplitter->Initialize(m_BottomCanvas);
	this->m_HorizontalSplitter->SplitHorizontally(m_UpperCanvas, m_BottomCanvas);
	
#if defined(__WXDEBUG__)
	Connect(idMenuLoad, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&GNRFrame::OnLoad);
#endif
	
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
}

#if defined(__WXDEBUG__)
#include <wx/log.h>
#include <wx/filedlg.h>
#include <string.h>

#include "md5.h"
#include "GNRObjectFile.h"

void GNRFrame::OnLoad(wxCommandEvent& event)
{
	//wxMessageBox(wxT("This is like a new main(), I know it isnt, but I need a place where to test new Code!!!"));
	wxString filename = wxFileSelector(wxT("Select OBJ-File..."), wxT(""), wxT(""), wxT(""), wxT("OBJ-Files (*.obj)|*.obj"));
	
	GNRObjectFile bla(filename);
}
#endif
