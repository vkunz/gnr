/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRMainFrame
 * @name        GNRMainFrame.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/intl.h>
#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/log.h>
#include <wx/filedlg.h>
#include <string.h>

#include "GNRObjectImport.h"
#include "GNRMainFrame.h"
#include "GNRController.h"

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

//(*IdInit(GNRMainFrame)
const long GNRMainFrame::idMenuLoad = wxNewId();
const long GNRMainFrame::idMenuSave = wxNewId();
const long GNRMainFrame::idMenuImport = wxNewId();
const long GNRMainFrame::idMenuExport = wxNewId();
const long GNRMainFrame::idMenuQuit = wxNewId();
const long GNRMainFrame::idMenuHelp = wxNewId();
const long GNRMainFrame::idMenuAbout = wxNewId();
const long GNRMainFrame::ID_StatusBar = wxNewId();
const long GNRMainFrame::btn_room_new = wxNewId();
const long GNRMainFrame::btn_room_open = wxNewId();
const long GNRMainFrame::btn_room_save = wxNewId();
const long GNRMainFrame::btn_undo = wxNewId();
const long GNRMainFrame::btn_redo = wxNewId();
const long GNRMainFrame::btn_move_xy = wxNewId();
const long GNRMainFrame::btn_move_xz = wxNewId();
const long GNRMainFrame::btn_rotate_xy = wxNewId();
const long GNRMainFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRMainFrame,wxFrame)
	
END_EVENT_TABLE()

GNRMainFrame::GNRMainFrame(wxWindow* parent, wxWindowID id)
{
	//(*Initialize(GNRMainFrame)
	wxMenuItem* MenuItem7;
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem1;
	wxMenuItem* MenuItem4;
	wxMenu* Menu1;
	wxMenuItem* MenuItem6;
	wxMenuBar* MenuBar1;
	wxMenu* Menu2;
	
	Create(parent, wxID_ANY, _("GNR - 3D Einrichtungsplaner"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(800,600));
	SetMinSize(wxSize(640,480));
	SetFocus();
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem3 = new wxMenuItem(Menu1, idMenuLoad, _("XML &Öffnen\tAlt-O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuSave, _("XML &Speichern\tAlt-S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	MenuItem6 = new wxMenuItem(Menu1, idMenuImport, _("OBJ &Importieren\tAlt-I"), _("Object-Datei importieren"), wxITEM_NORMAL);
	Menu1->Append(MenuItem6);
	MenuItem7 = new wxMenuItem(Menu1, idMenuExport, _("OBJ &Exportieren\tAlt-E"), _("Object-Datei exportieren"), wxITEM_NORMAL);
	Menu1->Append(MenuItem7);
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("GNR Schließen\tAlt-F4"), _("GNR schließen..."), wxITEM_NORMAL);
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
	ToolBarItem6 = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxImage(_T("src\\resources\\buttons\\lc_arrowshapes.quad-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Verschieben in X-Y-Richtung"), _("Verschieben in X-Y-Richtung"));
	ToolBarItem7 = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxImage(_T("src\\resources\\buttons\\lc_arrowshapes.up-right-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Verschieben in X-Z-Richtung"), _("Verschieben in X-Z-Richtung"));
	ToolBarItem8 = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxImage(_T("src\\resources\\buttons\\lc_arrowshapes.circular-arrow.png"))), wxNullBitmap, wxITEM_NORMAL, _("Rotieren auf X-Y-Achsen"), _("Rotieren auf X-Y-Achsen"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	Center();
	
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnAbout);
	//*)
	
	Connect(idMenuImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnImport);
	Connect(idMenuExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnExport);
}

GNRMainFrame::~GNRMainFrame()
{
	//(*Destroy(GNRMainFrame)
	//*)
}

void GNRMainFrame::OnQuit(wxCommandEvent& event)
{
	Close();
}

void GNRMainFrame::OnAbout(wxCommandEvent& event)
{
	wxString msg = wxbuildinfo(long_f);
	wxMessageBox(msg, _("GNR"));
}

void GNRMainFrame::OnImport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Select OBJ-File..."), wxT(""), wxT(""), wxT(""), wxT("OBJ-Files (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		// TODO: EVENT_FILE_IMPORT
	}
	
}

void GNRMainFrame::OnExport(wxCommandEvent& event)
{
}
