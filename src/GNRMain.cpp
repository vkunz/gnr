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
#include <wx/artprov.h>
#include <wx/image.h>

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
const long GNRFrame::btn_room_new = wxNewId();
const long GNRFrame::btn_room_open = wxNewId();
const long GNRFrame::btn_room_save = wxNewId();
const long GNRFrame::btn_undo = wxNewId();
const long GNRFrame::btn_redo = wxNewId();
const long GNRFrame::btn_move_xy = wxNewId();
const long GNRFrame::btn_move_xz = wxNewId();
const long GNRFrame::btn_rotate_xy = wxNewId();
const long GNRFrame::ID_TOOLBAR1 = wxNewId();
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
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBarItem1 = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen"), _("Raum erstellen"));
	ToolBarItem2 = ToolBar1->AddTool(btn_room_open, _("Raum öffnen"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FOLDER_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Raum öffnen"), _("Raum öffnen"));
	ToolBarItem3 = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBar1->AddSeparator();
	ToolBarItem4 = ToolBar1->AddTool(btn_undo, _("Rückgängig"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_UNDO")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Rückgängig"), _("Rückgängig"));
	ToolBarItem5 = ToolBar1->AddTool(btn_redo, _("Wiederherstellen"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Wiederherstellen"), _("Wiederherstellen"));
	ToolBar1->AddSeparator();
	ToolBarItem6 = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxImage(_T("src/resources/buttons/lc_arrowshapes.quad-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Verschieben in X-Y-Richtung"), _("Verschieben in X-Y-Richtung"));
	ToolBarItem7 = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxImage(_T("src/resources/buttons/lc_arrowshapes.up-right-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Verschieben in X-Z-Richtung"), _("Verschieben in X-Z-Richtung"));
	ToolBarItem8 = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxImage(_T("src/resources/buttons/lc_arrowshapes.circular-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Rotieren auf X-Y-Achsen"), _("Rotieren auf X-Y-Achsen"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	Center();
	
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRFrame::OnAbout);
	//*)
	
	//main splitter window
	this->m_VerticalSplitter = new wxSplitterWindow(this, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	this->m_VerticalSplitter->SetMinimumPaneSize(200);
	
	//create splitter for left panel with tree and models
	this->m_HorizontalSplitter_left = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	this->m_HorizontalSplitter_left->SetMinimumPaneSize(200);
	
	//create tree and models panel
	this->m_TreePanel   = new GNRTreePanel(m_HorizontalSplitter_left, wxID_ANY);
	this->m_ModelsPanel = new GNRModelsPanel(m_HorizontalSplitter_left, wxID_ANY);
	
	//initialize tree (top) and models (bottom)
	this->m_HorizontalSplitter_left->Initialize(m_TreePanel);
	this->m_HorizontalSplitter_left->Initialize(m_ModelsPanel);
	this->m_HorizontalSplitter_left->SplitHorizontally(m_TreePanel, m_ModelsPanel);
	
	//create splitter for right panel with two canvas
	this->m_HorizontalSplitter_right = new wxSplitterWindow(m_VerticalSplitter, -1, wxPoint(0,0), wxDefaultSize, wxSP_3D|wxRAISED_BORDER);
	this->m_HorizontalSplitter_right->SetMinimumPaneSize(200);
	
	//split left and right splitters
	this->m_VerticalSplitter->SplitVertically(m_HorizontalSplitter_left, m_HorizontalSplitter_right);
	
	//create two canvas panels
	this->m_BottomCanvas = new TestCanvas(m_HorizontalSplitter_right, -1);
	this->m_UpperCanvas  = new TestCanvas(m_HorizontalSplitter_right, -1);
	
	//initialize top an bottom canvas
	this->m_HorizontalSplitter_right->Initialize(m_UpperCanvas);
	this->m_HorizontalSplitter_right->Initialize(m_BottomCanvas);
	this->m_HorizontalSplitter_right->SplitHorizontally(m_UpperCanvas, m_BottomCanvas);
	
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
#include "GNRObjectImport.h"

void GNRFrame::OnLoad(wxCommandEvent& event)
{
	//wxMessageBox(wxT("This is like a new main(), I know it isnt, but I need a place where to test new Code!!!"));
	wxString filename = wxFileSelector(wxT("Select OBJ-File..."), wxT(""), wxT(""), wxT(""), wxT("OBJ-Files (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		GNRObjectImport object_importer(filename);
	}
}
#endif
