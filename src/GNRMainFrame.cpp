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

#include "resources/button-undo.xpm"
#include "resources/button-redo.xpm"
#include "resources/button-room-new.xpm"
#include "resources/button-room-open.xpm"
#include "resources/button-room-save.xpm"
#include "resources/button-room-save-as.xpm"
#include "resources/button-exit.xpm"
#include "resources/button-move-xy.xpm"
#include "resources/button-move-xz.xpm"
#include "resources/button-world-rotate-xy.xpm"
#include "resources/button-world-rotate-xz.xpm"
#include "resources/button-canvas2d-zoom-in.xpm"
#include "resources/button-canvas2d-zoom-out.xpm"
#include "resources/button-canvas2d-zoom-fit.xpm"
#include "resources/button-reset-camera.xpm"

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
const long GNRMainFrame::idMenuNew = wxNewId();
const long GNRMainFrame::idMenuLoad = wxNewId();
const long GNRMainFrame::idMenuSave = wxNewId();
const long GNRMainFrame::idMenuImport = wxNewId();
const long GNRMainFrame::idMenuExport = wxNewId();
const long GNRMainFrame::idMenuQuit = wxNewId();
const long GNRMainFrame::idMenuHelp = wxNewId();
const long GNRMainFrame::idMenuAbout = wxNewId();
const long GNRMainFrame::ID_StatusBar = wxNewId();
//*)
const long GNRMainFrame::btn_room_new = wxNewId();
const long GNRMainFrame::btn_room_open = wxNewId();
const long GNRMainFrame::btn_room_save = wxNewId();
const long GNRMainFrame::btn_room_save_as = wxNewId();
const long GNRMainFrame::btn_quit = wxNewId();
const long GNRMainFrame::btn_undo = wxNewId();
const long GNRMainFrame::btn_redo = wxNewId();
const long GNRMainFrame::btn_zoom_in = wxNewId();
const long GNRMainFrame::btn_zoom_out = wxNewId();
const long GNRMainFrame::btn_zoom_fit = wxNewId();
const long GNRMainFrame::btn_move_xy = wxNewId();
const long GNRMainFrame::btn_move_xz = wxNewId();
const long GNRMainFrame::btn_rotate_xy = wxNewId();
const long GNRMainFrame::btn_rotate_xz = wxNewId();
const long GNRMainFrame::btn_camera_reset = wxNewId();
const long GNRMainFrame::ID_ToolBar = wxNewId();

BEGIN_EVENT_TABLE(GNRMainFrame,wxFrame)
	EVT_MENU(btn_move_xy, GNRMainFrame::OnToolbarMoveXY)
	EVT_MENU(btn_move_xz, GNRMainFrame::OnToolbarMoveXZ)
	EVT_MENU(btn_rotate_xy, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(btn_rotate_xz, GNRMainFrame::OnToolbarRotateXZ)
	EVT_MENU(btn_room_new, GNRMainFrame::OnNew)
	EVT_MENU(btn_camera_reset, GNRMainFrame::OnCameraReset)
	EVT_MENU(btn_quit, GNRMainFrame::OnQuit)
END_EVENT_TABLE()

GNRMainFrame::GNRMainFrame(wxWindow* parent, wxWindowID id)
{
	//(*Initialize(GNRMainFrame)
	wxMenuItem* MenuItem8;
	wxMenuItem* MenuItem7;
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem1;
	wxMenuItem* MenuItem4;
	wxMenu* Menu1;
	wxMenuItem* MenuItem3;
	wxMenuItem* MenuItem6;
	wxMenuBar* MenuBar1;
	wxMenu* Menu2;
	
	Create(parent, wxID_ANY, _("GNR - 3D Einrichtungsplaner"), wxPoint(0,0), wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(800,500));
	SetMinSize(wxSize(640,480));
	SetFocus();
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem8 = new wxMenuItem(Menu1, idMenuNew, _("&Neuer Raum\tAlt-N"), _("Raum leeren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem8);
	Menu1->AppendSeparator();
	MenuItem3 = new wxMenuItem(Menu1, idMenuLoad, _("XML &�ffnen\tAlt-O"), _("vorhandene Datei �ffnen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuSave, _("XML &Speichern\tAlt-S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	Menu1->AppendSeparator();
	MenuItem6 = new wxMenuItem(Menu1, idMenuImport, _("OBJ &Importieren\tAlt-I"), _("Object-Datei importieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem6);
	MenuItem7 = new wxMenuItem(Menu1, idMenuExport, _("OBJ &Exportieren\tAlt-E"), _("Object-Datei exportieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem7);
	Menu1->AppendSeparator();
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("GNR Schlie�en\tAlt-F4"), _("GNR beenden..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&Datei"));
	Menu2 = new wxMenu();
	MenuItem5 = new wxMenuItem(Menu2, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	Menu2->Append(MenuItem5);
	MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&�ber\tAlt-F1"), _("Informationen �ber GNR..."), wxITEM_NORMAL);
	Menu2->Append(MenuItem2);
	MenuBar1->Append(Menu2, _("&Hilfe"));
	SetMenuBar(MenuBar1);
	StatusBar1 = new wxStatusBar(this, ID_StatusBar, 0, _T("ID_StatusBar"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar1);
	//Center();
	
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnAbout);
	//*)
	
	ToolBar1 = new wxToolBar(this, ID_ToolBar, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(24,24));
	ToolBarItem1 = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxBitmap(wxIcon(button_room_new_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen"), _("Raum erstellen"));
	ToolBarItem2 = ToolBar1->AddTool(btn_room_open, _("Raum �ffnen"), wxBitmap(wxIcon(button_room_open_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum �ffnen"), _("Raum �ffnen"));
	ToolBarItem3 = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxBitmap(wxIcon(button_room_save_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBarItem4 = ToolBar1->AddTool(btn_room_save_as, _("Raum speichern unter"), wxBitmap(wxIcon(button_room_save_as_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern unter"), _("Raum speichern unter"));
	ToolBar1->AddSeparator();
	ToolBarItem5 = ToolBar1->AddTool(btn_undo, _("R�ckg�ngig"), wxBitmap(wxIcon(button_undo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("R�ckg�ngig"), _("R�ckg�ngig"));
	ToolBarItem6 = ToolBar1->AddTool(btn_redo, _("Wiederherstellen"), wxBitmap(wxIcon(button_redo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Wiederherstellen"), _("Wiederherstellen"));
	ToolBar1->AddSeparator();
	ToolBarItem7 = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxIcon(button_move_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Z-Richtung"), _("Verschieben in X-Z-Richtung"));
	ToolBarItem8 = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxIcon(button_move_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Y-Richtung"), _("Verschieben in X-Y-Richtung"));
	ToolBarItem9 = ToolBar1->AddTool(btn_rotate_xz, _("Rotieren auf X-Z-Achsen"), wxBitmap(wxIcon(button_world_rotate_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Z-Achsen"), _("Rotieren auf X-Z-Achsen"));
	ToolBarItem10 = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxIcon(button_world_rotate_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Y-Achsen"), _("Rotieren auf X-Y-Achsen"));
	ToolBar1->AddSeparator();
	ToolBarItem11 = ToolBar1->AddTool(btn_zoom_in, _("Draufsicht einzoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_in_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht einzoomen"), _("Draufsicht einzoomen"));
	ToolBarItem12 = ToolBar1->AddTool(btn_zoom_out, _("Draufsicht auszoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_out_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht auszoomen"), _("Draufsicht auszoomen"));
	ToolBarItem13 = ToolBar1->AddTool(btn_zoom_fit, _("Draufsicht einpassen"), wxBitmap(wxIcon(button_canvas2d_zoom_fit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht in Ansicht einpassen"), _("Draufsicht in Ansicht einpassen"));
	ToolBar1->AddSeparator();
	ToolBarItem14 = ToolBar1->AddTool(btn_camera_reset, _("Kamera zur�cksetzen"), wxBitmap(wxIcon(button_reset_camera_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Kamera in 3D zur�cksetzen"), _("Kamera in 3D zur�cksetzen"));
	ToolBar1->AddSeparator();
	ToolBarItem99 = ToolBar1->AddTool(btn_quit, _("GNR beenden"), wxBitmap(wxIcon(button_exit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("GNR beenden"), _("GNR beenden"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	//Center();
	
	//own events on menu selection
	Connect(idMenuImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnImport);
	Connect(idMenuExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnExport);
	Connect(idMenuNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnNew);
	Connect(idMenuLoad,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnLoad);
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

void GNRMainFrame::OnNew(wxCommandEvent& event)
{
	wxMessageBox(wxT("I'll tidy up your room!"));
	
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(NEWROOM);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnAbout(wxCommandEvent& event)
{
	wxString msg = wxbuildinfo(long_f);
	wxMessageBox(msg, _("GNR"));
}

void GNRMainFrame::OnImport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei w�hlen..."), wxT(""), wxT(""), wxT(""), wxT("Obj-Datei (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnExport(wxCommandEvent& event)
{
	wxMessageBox(wxT("Not implemented yet."));
}

void GNRMainFrame::OnLoad(wxCommandEvent& WXUNUSED(event))
{
	wxString filename = wxFileSelector(wxT("Datei w�hlen..."), wxT(""), wxT(""), wxT(""), wxT("OAX-Datei (*.oax)|*.oax|OPXDatei (*.opx)|*.opx"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(XMLOPEN);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnToolbarMoveXY(wxCommandEvent& event)
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarMoveXZ(wxCommandEvent& event)
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXY(wxCommandEvent& event)
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXZ(wxCommandEvent& event)
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnCameraReset(wxCommandEvent& event)
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETCAMERA);
	GetEventHandler()->ProcessEvent(gnrevent);
}
