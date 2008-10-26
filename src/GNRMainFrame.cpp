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

#include "wx/wx.h"
#include "math.h"
#include "GNRObjectImport.h"
#include "GNRMainFrame.h"

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
#include "resources/button-snap-to-grid.xpm"

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
const long GNRMainFrame::idMenuNewRoom = wxNewId();
const long GNRMainFrame::idMenuOpxOpen = wxNewId();
const long GNRMainFrame::idMenuOpxSave = wxNewId();
const long GNRMainFrame::idMenuOaxImport = wxNewId();
const long GNRMainFrame::idMenuOaxExport = wxNewId();
const long GNRMainFrame::idMenuObjImport = wxNewId();
const long GNRMainFrame::idMenuObjExport = wxNewId();
const long GNRMainFrame::idMenuQuit = wxNewId();
const long GNRMainFrame::idMenuSnapToGrid = wxNewId();
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
const long GNRMainFrame::btn_snap_to_grid = wxNewId();

const long GNRMainFrame::ID_ToolBar = wxNewId();

const long GNRMainFrame::ID_SPINCTRL_TRANS  = wxNewId();
const long GNRMainFrame::ID_SPINCTRL_ROTATE = wxNewId();
const long GNRMainFrame::ID_STATICTEXT1 = wxNewId();
const long GNRMainFrame::ID_STATICTEXT2 = wxNewId();

BEGIN_EVENT_TABLE(GNRMainFrame,wxFrame)
	EVT_MENU(btn_move_xz, GNRMainFrame::OnToolbarMoveXZ)
	EVT_MENU(btn_move_xy, GNRMainFrame::OnToolbarMoveXY)
	EVT_MENU(btn_rotate_xz, GNRMainFrame::OnToolbarRotateXZ)
	EVT_MENU(btn_rotate_xy, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(btn_camera_reset, GNRMainFrame::OnCameraReset)
	EVT_MENU(btn_snap_to_grid, GNRMainFrame::OnSnapToGridBtn)
	EVT_MENU(btn_room_new, GNRMainFrame::OnMenuNewRoom)
	EVT_SPINCTRL(ID_SPINCTRL_ROTATE, GNRMainFrame::OnSnapToGridCtrl)
	EVT_SPINCTRL(ID_SPINCTRL_TRANS, GNRMainFrame::OnSnapToGridCtrl)
	EVT_MENU(btn_quit, GNRMainFrame::OnMenuQuit)
END_EVENT_TABLE()

GNRMainFrame::GNRMainFrame(wxWindow* parent, wxWindowID WXUNUSED(id))
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
	
	Create(parent, wxID_ANY, _("GNR - 3D Einrichtungsplaner"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(800,550));
	Move(wxPoint(0,0));
	SetMinSize(wxSize(800,480));
	SetFocus();
	MenuBar1 = new wxMenuBar();
	Menu1 = new wxMenu();
	MenuItem8 = new wxMenuItem(Menu1, idMenuNewRoom, _("&Neuer Raum\tAlt-N"), _("Raum leeren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem8);
	Menu1->AppendSeparator();
	MenuItem3 = new wxMenuItem(Menu1, idMenuOpxOpen, _("OPX &Öffnen\tAlt-O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuOpxSave, _("OPX &Speichern\tAlt-S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	Menu1->AppendSeparator();
	MenuItem10 = new wxMenuItem(Menu1, idMenuOaxImport, _("OAX Importieren"), _("OAX Importieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem10);
	MenuItem11 = new wxMenuItem(Menu1, idMenuOaxExport, _("OAX Exportieren"), _("OAX Exportieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem11);
	Menu1->AppendSeparator();
	MenuItem6 = new wxMenuItem(Menu1, idMenuObjImport, _("OBJ &Importieren\tAlt-I"), _("Object-Datei importieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem6);
	MenuItem7 = new wxMenuItem(Menu1, idMenuObjExport, _("OBJ E&xportieren\tAlt-X"), _("Object-Datei exportieren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem7);
	Menu1->AppendSeparator();
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("GNR Schließen\tAlt-F4"), _("GNR beenden..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&Datei"));
	Menu3 = new wxMenu();
	MenuItem9 = new wxMenuItem(Menu3, idMenuSnapToGrid, _("Ein&rasten aktivieren\tALT-R"), _("Einrasten aktivieren"), wxITEM_CHECK);
	Menu3->Append(MenuItem9);
	MenuBar1->Append(Menu3, _("&Einstellungen"));
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
	
	Connect(idMenuNewRoom,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuNewRoom);
	Connect(idMenuOpxOpen,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOpxOpen);
	Connect(idMenuOpxSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOpxSave);
	Connect(idMenuOaxImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOaxImport);
	Connect(idMenuOaxExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOaxExport);
	Connect(idMenuObjImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuObjImport);
	Connect(idMenuObjExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuObjExport);
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuQuit);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuAbout);
	//*)
	
	//generate toolbar and buttons
	ToolBar1 = new wxToolBar(this, ID_ToolBar, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(24,24));
	ToolBarItem1 = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxBitmap(wxIcon(button_room_new_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen"), _("Raum erstellen"));
	ToolBarItem2 = ToolBar1->AddTool(btn_room_open, _("Raum öffnen"), wxBitmap(wxIcon(button_room_open_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum öffnen"), _("Raum öffnen"));
	ToolBarItem3 = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxBitmap(wxIcon(button_room_save_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBarItem4 = ToolBar1->AddTool(btn_room_save_as, _("Raum speichern unter"), wxBitmap(wxIcon(button_room_save_as_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern unter"), _("Raum speichern unter"));
	ToolBar1->AddSeparator();
	ToolBarItem5 = ToolBar1->AddTool(btn_undo, _("Rückgängig"), wxBitmap(wxIcon(button_undo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Rückgängig"), _("Rückgängig"));
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
	ToolBarItem14 = ToolBar1->AddTool(btn_camera_reset, _("Kamera zurücksetzen"), wxBitmap(wxIcon(button_reset_camera_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Kamera in 3D zurücksetzen"), _("Kamera in 3D zurücksetzen"));
	ToolBar1->AddSeparator();
	
	//toggle button for snap to grid function
	ToolBarItem15 = ToolBar1->AddTool(btn_snap_to_grid, _("Einrasten aktivieren"), wxBitmap(wxIcon(button_snap_to_grid_xpm)), wxNullBitmap, wxITEM_CHECK, _("Einrasten aktivieren"), _("Einrasten aktivieren"));
	ToolBar1->AddSeparator();
	
	//build input for grid snapping
	SpinCtrlTranslate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_TRANS, _T("100"), wxPoint(0,0), wxSize(60,20), 0, 1, 1000, 10, _T("ID_SPINCTRL_TRANS"));
	StaticText1       = new wxStaticText(ToolBar1, ID_STATICTEXT1, _(" mm"), wxPoint(3,13), wxSize(20,12), 0, _T("Schrittweite in mm"));
	SpinCtrlTranslate->SetValue(_T("100"));
	ToolBarItem16 = ToolBar1->AddControl(SpinCtrlTranslate);
	ToolBarItem17 = ToolBar1->AddControl(StaticText1);
	ToolBar1->AddSeparator();
	
	//build input for rotation snapping
	SpinCtrlRotate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_ROTATE, _T("15"), wxPoint(0,0), wxSize(60,20), 0, 0, 90, 10, _T("ID_SPINCTRL_ROTATE"));
	StaticText2    = new wxStaticText(ToolBar1, ID_STATICTEXT2, _(" Grad"), wxPoint(3,13), wxSize(30,12), 0, _T("Schrittweite in Grad"));
	SpinCtrlRotate->SetValue(_T("15"));
	ToolBarItem18 = ToolBar1->AddControl(SpinCtrlRotate);
	ToolBarItem19 = ToolBar1->AddControl(StaticText2);
	ToolBar1->AddSeparator();
	
	//build exit button at the end
	ToolBarItem99 = ToolBar1->AddTool(btn_quit, _("GNR beenden"), wxBitmap(wxIcon(button_exit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("GNR beenden"), _("GNR beenden"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	//Center();
}

GNRMainFrame::~GNRMainFrame()
{
	//(*Destroy(GNRMainFrame)
	//*)
}

void GNRMainFrame::OnMenuNewRoom(wxCommandEvent& event)
{
	wxMessageBox(wxT("I'll tidy up your room!"));
	
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(NEWROOM);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnMenuOpxOpen(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OPXOPEN);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOpxSave(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OPXSAVE);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOaxImport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOaxExport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuObjImport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("ObjDatei (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuObjExport(wxCommandEvent& event)
{
	wxString filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("ObjDatei (*.obj)|*.obj"));
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuQuit(wxCommandEvent& event)
{
	Close();
}

void GNRMainFrame::OnMenuAbout(wxCommandEvent& event)
{
	wxString msg = wxbuildinfo(long_f);
	wxMessageBox(msg, _("GNR"));
}

void GNRMainFrame::OnToolbarMoveXZ(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarMoveXY(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXZ(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXY(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnCameraReset(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETCAMERA);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnSnapToGridBtn(wxCommandEvent& WXUNUSED(event))
{
	OnSnapToGrid();
}

void GNRMainFrame::OnSnapToGridCtrl(wxSpinEvent& WXUNUSED(event))
{
	OnSnapToGrid();
}

void GNRMainFrame::OnSnapToGrid()
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SNAPTOGRID);
	
	int snapGrid  = SpinCtrlTranslate->GetValue();
	int snapAngle = SpinCtrlRotate->GetValue();
	
	if (!ToolBarItem15->IsToggled())
	{
		snapAngle = 1;
		snapGrid  = 1;
	}
	
	gnrevent.setSnapToGrid(snapGrid);
	gnrevent.setSnapToAngle(snapAngle);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
