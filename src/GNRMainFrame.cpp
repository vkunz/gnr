/**
 * GNRMainFrame
 * @name        GNRMainFrame.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/arrstr.h>
#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/string.h>


#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GNREnum.h"
#include "GNRGlobalDefine.h"
#include "GNRMainFrame.h"
#include "GNRHelpFrame.h"
#include "GNRGLNotifyEvent.h"
#include "GNRNotifyEvent.h"

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
#include "resources/button-draw-walls.xpm"
#include "resources/button_screenshot.xpm"

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
const long GNRMainFrame::idMenuQuit = wxNewId();
const long GNRMainFrame::idMenuUndo = wxNewId();
const long GNRMainFrame::idMenuRedo = wxNewId();
const long GNRMainFrame::idMenuDeleteObject = wxNewId();
const long GNRMainFrame::idMenuCutObject = wxNewId();
const long GNRMainFrame::idMenuInsertObject = wxNewId();
const long GNRMainFrame::idMenuCopyObject = wxNewId();
const long GNRMainFrame::idMenuCloneObject = wxNewId();
const long GNRMainFrame::idMenuHideObject = wxNewId();
const long GNRMainFrame::idMenuShowObject = wxNewId();
const long GNRMainFrame::idMenuObjExport = wxNewId();
const long GNRMainFrame::idMenuOaxExport = wxNewId();
const long GNRMainFrame::idMenuObjImport = wxNewId();
const long GNRMainFrame::idMenuOaxImport = wxNewId();
const long GNRMainFrame::idMenuZoomIn = wxNewId();
const long GNRMainFrame::idMenuZoomOut = wxNewId();
const long GNRMainFrame::idMenuZoomFit = wxNewId();
const long GNRMainFrame::idMenuZoomReset = wxNewId();
const long GNRMainFrame::idMenuSnapToGrid = wxNewId();
const long GNRMainFrame::idMenuMoveXZ = wxNewId();
const long GNRMainFrame::idMenuMoveXY = wxNewId();
const long GNRMainFrame::idMenuRotateXZ = wxNewId();
const long GNRMainFrame::idMenuRotateXY = wxNewId();
const long GNRMainFrame::idMenuDrawWall = wxNewId();
const long GNRMainFrame::idMenuShadows = wxNewId();
const long GNRMainFrame::idMenuGroup = wxNewId();
const long GNRMainFrame::idMenuUngroup = wxNewId();
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
const long GNRMainFrame::btn_create_screenshot = wxNewId();
const long GNRMainFrame::btn_camera_reset = wxNewId();
const long GNRMainFrame::btn_snap_to_grid = wxNewId();
const long GNRMainFrame::btn_draw_walls = wxNewId();

const long GNRMainFrame::ID_ToolBar = wxNewId();

const long GNRMainFrame::ID_SPINCTRL_TRANS  = wxNewId();
const long GNRMainFrame::ID_SPINCTRL_ROTATE = wxNewId();
const long GNRMainFrame::ID_STATICTEXT1 = wxNewId();
const long GNRMainFrame::ID_STATICTEXT2 = wxNewId();

BEGIN_EVENT_TABLE(GNRMainFrame,wxFrame)
	EVT_MENU(btn_room_new, GNRMainFrame::OnMenuNewRoom)
	EVT_MENU(btn_undo, GNRMainFrame::OnToolbarUndo)
	EVT_MENU(btn_redo, GNRMainFrame::OnToolbarRedo)
	EVT_MENU(btn_move_xz, GNRMainFrame::OnToolbarMoveXZ)
	EVT_MENU(btn_move_xy, GNRMainFrame::OnToolbarMoveXY)
	EVT_MENU(btn_rotate_xz, GNRMainFrame::OnToolbarRotateXZ)
	EVT_MENU(btn_rotate_xy, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(btn_draw_walls, GNRMainFrame::OnToolbarDrawWall)
	EVT_MENU(btn_create_screenshot, GNRMainFrame::OnCreateScreenshot)
	EVT_MENU(btn_camera_reset, GNRMainFrame::OnCameraReset)
	EVT_MENU(btn_zoom_in, GNRMainFrame::OnZoomIn)
	EVT_MENU(btn_zoom_out, GNRMainFrame::OnZoomOut)
	EVT_MENU(btn_snap_to_grid, GNRMainFrame::OnSnapToGridBtn)
	//functions menu
	EVT_MENU(idMenuGroup, GNRMainFrame::OnGroupCreate)
	EVT_MENU(idMenuUngroup, GNRMainFrame::OnGroupModify)
	EVT_MENU(idMenuDeleteObject, GNRMainFrame::OnDeleteSelected)
	EVT_MENU(idMenuCloneObject, GNRMainFrame::OnCloneSelected)
	EVT_MENU(idMenuCopyObject, GNRMainFrame::OnCopySelected)
	EVT_MENU(idMenuCutObject, GNRMainFrame::OnCutSelected)
	EVT_MENU(idMenuInsertObject, GNRMainFrame::OnInsertCopy)
	EVT_MENU(idMenuHideObject, GNRMainFrame::OnHideSelected)
	EVT_MENU(idMenuShowObject, GNRMainFrame::OnShowHidden)
	EVT_MENU(idMenuUndo, GNRMainFrame::OnToolbarUndo)
	EVT_MENU(idMenuRedo, GNRMainFrame::OnToolbarRedo)
	EVT_MENU(idMenuZoomIn, GNRMainFrame::OnZoomIn)
	EVT_MENU(idMenuZoomOut, GNRMainFrame::OnZoomOut)
	EVT_MENU(idMenuZoomFit, GNRMainFrame::OnCameraReset)
	EVT_MENU(idMenuZoomReset, GNRMainFrame::OnCameraReset)
	EVT_MENU(idMenuHelp, GNRMainFrame::OnMenuHelp)
	//settings menu sync to toolbar
	EVT_MENU(idMenuSnapToGrid, GNRMainFrame::OnSnapToGridMenu)
	EVT_MENU(idMenuShadows, GNRMainFrame::OnShadowsMenu)
	EVT_MENU(idMenuMoveXZ, GNRMainFrame::OnToolbarMoveXZ)
	EVT_MENU(idMenuMoveXY, GNRMainFrame::OnToolbarMoveXY)
	EVT_MENU(idMenuRotateXZ, GNRMainFrame::OnToolbarRotateXZ)
	EVT_MENU(idMenuRotateXY, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(idMenuRotateXY, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(idMenuDrawWall, GNRMainFrame::OnToolbarDrawWall)
	//set snap to grid on spinctrl change
	EVT_SPINCTRL(ID_SPINCTRL_ROTATE, GNRMainFrame::OnSnapToGridCtrl)
	EVT_SPINCTRL(ID_SPINCTRL_TRANS, GNRMainFrame::OnSnapToGridCtrl)
	//quit application
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
	MenuItem8 = new wxMenuItem(Menu1, idMenuNewRoom, _("&Neuer leerer Raum\tCTRL+N"), _("Raum leeren..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem8);
	Menu1->AppendSeparator();
	MenuItem3 = new wxMenuItem(Menu1, idMenuOpxOpen, _("OPX &Öffnen\tCTRL+O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(Menu1, idMenuOpxSave, _("OPX &Speichern\tCTRL+S"), _("Datei speichern..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem4);
	Menu1->AppendSeparator();
	MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("GNR Schließen\tALT+F4"), _("GNR beenden..."), wxITEM_NORMAL);
	Menu1->Append(MenuItem1);
	MenuBar1->Append(Menu1, _("&Datei"));
	Menu4 = new wxMenu();
	MenuItem24 = new wxMenuItem(Menu4, idMenuUndo, _("&Rückgänig\tCTRL+Z"), _("Aktion rückgänig machen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem24);
	MenuItem25 = new wxMenuItem(Menu4, idMenuRedo, _("&Wiederherstellen\tCTRL+Y"), _("Aktion wiederherstellen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem25);
	Menu4->AppendSeparator();
	MenuItem19 = new wxMenuItem(Menu4, idMenuDeleteObject, _("Objekte ent&fernen\tDEL"), _("Objekte entfernen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem19);
	MenuItem30 = new wxMenuItem(Menu4, idMenuCutObject, _("Objekte &ausschneiden\tCTRL+X"), _("Objekte ausschneiden..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem30);
	MenuItem21 = new wxMenuItem(Menu4, idMenuInsertObject, _("Objekte &einfügen\tCTRL+V"), _("Objekte einfügen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem21);
	MenuItem22 = new wxMenuItem(Menu4, idMenuCopyObject, _("Objekte k&opieren\tCTRL+C"), _("Objekte kopieren..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem22);
	MenuItem31 = new wxMenuItem(Menu4, idMenuCloneObject, _("Objekte &klonen\tCTRL+D"), _("Objekte klonen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem31);
	Menu4->AppendSeparator();
	MenuItem20 = new wxMenuItem(Menu4, idMenuHideObject, _("Objekte &verstecken\tCTRL+H"), _("Objekte verstecken..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem20);
	MenuItem23 = new wxMenuItem(Menu4, idMenuShowObject, _("Objekte &anzeigen\tCTRL+J"), _("Objekte anzeigen..."), wxITEM_NORMAL);
	Menu4->Append(MenuItem23);
	MenuBar1->Append(Menu4, _("&Bearbeiten"));
	Menu5 = new wxMenu();
	MenuItem7 = new wxMenuItem(Menu5, idMenuObjExport, _("OBJ E&xportieren\tALT+O"), _("Object-Datei exportieren..."), wxITEM_NORMAL);
	Menu5->Append(MenuItem7);
	MenuItem11 = new wxMenuItem(Menu5, idMenuOaxExport, _("OAX Ex&portieren\tCTRL+O"), _("OAX Exportieren..."), wxITEM_NORMAL);
	Menu5->Append(MenuItem11);
	MenuBar1->Append(Menu5, _("E&xportieren"));
	Menu6 = new wxMenu();
	MenuItem6 = new wxMenuItem(Menu6, idMenuObjImport, _("OBJ &Importieren\tALT+I"), _("Object-Datei importieren..."), wxITEM_NORMAL);
	Menu6->Append(MenuItem6);
	MenuItem10 = new wxMenuItem(Menu6, idMenuOaxImport, _("OAX I&mportieren\tCTRL+I"), _("OAX Importieren..."), wxITEM_NORMAL);
	Menu6->Append(MenuItem10);
	MenuBar1->Append(Menu6, _("&Importieren"));
	Menu8 = new wxMenu();
	MenuItem26 = new wxMenuItem(Menu8, idMenuZoomIn, _("&Einzoomen\tPGUP"), _("In die 2D Ansicht hereinzoomen..."), wxITEM_NORMAL);
	Menu8->Append(MenuItem26);
	MenuItem27 = new wxMenuItem(Menu8, idMenuZoomOut, _("&Auszoomen\tPGDN"), _("Aus der 2D Ansicht herauszoomen..."), wxITEM_NORMAL);
	Menu8->Append(MenuItem27);
	Menu8->AppendSeparator();
	MenuItem28 = new wxMenuItem(Menu8, idMenuZoomFit, _("Au&tomatisch\tCTRL+Z"), _("Ansicht an Bildschirm anpassen..."), wxITEM_NORMAL);
	Menu8->Append(MenuItem28);
	MenuItem29 = new wxMenuItem(Menu8, idMenuZoomReset, _("Aus&ganszustand\tHOME"), _("Kamera in Ausganszustand zurücksetzen..."), wxITEM_NORMAL);
	Menu8->Append(MenuItem29);
	MenuBar1->Append(Menu8, _("&Kamera"));
	Menu3 = new wxMenu();
	MenuItem9 = new wxMenuItem(Menu3, idMenuSnapToGrid, _("Ein&rasten aktivieren\tF4"), _("Einrasten aktivieren..."), wxITEM_CHECK);
	Menu3->Append(MenuItem9);
	Menu3->AppendSeparator();
	MenuItem12 = new wxMenuItem(Menu3, idMenuMoveXZ, _("Verschieben X&Z\tF5"), _("Objekt verschieben entlang X- und Z-Achse..."), wxITEM_RADIO);
	Menu3->Append(MenuItem12);
	MenuItem13 = new wxMenuItem(Menu3, idMenuMoveXY, _("Verschieben X&Y\tF6"), _("Objekt verschieben entlang X- und Y-Achse..."), wxITEM_RADIO);
	Menu3->Append(MenuItem13);
	MenuItem14 = new wxMenuItem(Menu3, idMenuRotateXZ, _("Ro&tieren XZ\tF7"), _("Objekt rotieren an X- und Z-Achse..."), wxITEM_RADIO);
	Menu3->Append(MenuItem14);
	MenuItem15 = new wxMenuItem(Menu3, idMenuRotateXY, _("R&otieren XY\tF8"), _("Objekt rotieren an X- und Y-Achse..."), wxITEM_RADIO);
	Menu3->Append(MenuItem15);
	MenuItem16 = new wxMenuItem(Menu3, idMenuDrawWall, _("&Wände erstellen\tF9"), _("Wände im 2D-Modus erstellen..."), wxITEM_RADIO);
	Menu3->Append(MenuItem16);
	Menu3->AppendSeparator();
	MenuItem32 = new wxMenuItem(Menu3, idMenuShadows, _("&Schatten aktivieren\tF10"), _("Schatten aktivieren..."), wxITEM_CHECK);
	Menu3->Append(MenuItem32);
	MenuBar1->Append(Menu3, _("&Einstellungen"));
	Menu7 = new wxMenu();
	MenuItem17 = new wxMenuItem(Menu7, idMenuGroup, _("&Gruppe erstellen\tCTRL+G"), _("Neue Gruppe erstellen..."), wxITEM_NORMAL);
	Menu7->Append(MenuItem17);
	MenuItem18 = new wxMenuItem(Menu7, idMenuUngroup, _("Gruppe &auflösen\tCTRL+F"), _("Gruppe auflösen..."), wxITEM_NORMAL);
	Menu7->Append(MenuItem18);
	MenuBar1->Append(Menu7, _("Gr&uppen"));
	Menu2 = new wxMenu();
	MenuItem5 = new wxMenuItem(Menu2, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	Menu2->Append(MenuItem5);
	MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&Über\tALT+F1"), _("Informationen über GNR..."), wxITEM_NORMAL);
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
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuQuit);
	Connect(idMenuObjExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuObjExport);
	Connect(idMenuOaxExport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOaxExport);
	Connect(idMenuObjImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuObjImport);
	Connect(idMenuOaxImport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuOaxImport);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GNRMainFrame::OnMenuAbout);
	//*)
	
	//generate toolbar and buttons
	int c = 0;
	ToolBar1 = new wxToolBar(this, ID_ToolBar, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(24,24));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxBitmap(wxIcon(button_room_new_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen   [CTRL+N]"), _("Raum erstellen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_open, _("Raum öffnen"), wxBitmap(wxIcon(button_room_open_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum öffnen"), _("Raum öffnen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxBitmap(wxIcon(button_room_save_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_save_as, _("Raum speichern unter"), wxBitmap(wxIcon(button_room_save_as_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern unter"), _("Raum speichern unter"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_undo, _("Rückgängig"), wxBitmap(wxIcon(button_undo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Rückgängig   [CTRL+Z]"), _("Rückgängig"));
	ToolBarItem[c-1]->Enable(false);
	ToolBarItem[c++] = ToolBar1->AddTool(btn_redo, _("Wiederherstellen"), wxBitmap(wxIcon(button_redo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Wiederherstellen   [CTRL+Y]"), _("Wiederherstellen"));
	ToolBarItem[c-1]->Enable(false);
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxIcon(button_move_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Z-Richtung   [F5]"), _("Verschieben in X-Z-Richtung"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxIcon(button_move_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Y-Richtung   [F6]"), _("Verschieben in X-Y-Richtung"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_rotate_xz, _("Rotieren auf X-Z-Achsen"), wxBitmap(wxIcon(button_world_rotate_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Z-Achsen   [F7]"), _("Rotieren auf X-Z-Achsen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxIcon(button_world_rotate_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Y-Achsen   [F8]"), _("Rotieren auf X-Y-Achsen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_draw_walls, _("Wände zeichnen"), wxBitmap(wxIcon(button_draw_walls_xpm)), wxNullBitmap, wxITEM_RADIO, _("Wände zeichnen   [F9]"), _("Wände zeichnen"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_zoom_in, _("Draufsicht einzoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_in_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht einzoomen   [PGUP]"), _("Draufsicht einzoomen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_zoom_out, _("Draufsicht auszoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_out_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht auszoomen   [PGDN]"), _("Draufsicht auszoomen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_zoom_fit, _("Draufsicht einpassen"), wxBitmap(wxIcon(button_canvas2d_zoom_fit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht in Ansicht einpassen   [CTRL+Z]"), _("Draufsicht in Ansicht einpassen"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_create_screenshot, _("Screenshot erstellen"), wxBitmap(wxIcon(button_screenshot_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Screenshot der 3D-Szene erstellen   [PRINT]"), _("Screenshot der 3D-Szene erstellen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_camera_reset, _("Kamera zurücksetzen"), wxBitmap(wxIcon(button_reset_camera_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Kamera in 3D zurücksetzen   [HOME]"), _("Kamera in 3D zurücksetzen"));
	ToolBar1->AddSeparator();
	
	//toggle button for snap to grid function
	ToolBarItem[c++] = ToolBar1->AddTool(btn_snap_to_grid, _("Einrasten aktivieren"), wxBitmap(wxIcon(button_snap_to_grid_xpm)), wxNullBitmap, wxITEM_CHECK, _("Einrasten aktivieren   [F4]"), _("Einrasten aktivieren"));
	ToolBar1->AddSeparator();
	
	//build input for grid snapping
	SpinCtrlTranslate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_TRANS, _T("Schrittweite in mm"), wxPoint(0,0), wxSize(60,20), 0, SNAP_IN_MINIMUM_UNIT, SNAP_IN_MAXIMUM_UNIT, 10, _T("ID_SPINCTRL_TRANS"));
	StaticText1       = new wxStaticText(ToolBar1, ID_STATICTEXT1, _(" mm"), wxPoint(3,13), wxSize(20,12), 0, _T("Schrittweite in mm"));
	SpinCtrlTranslate->SetValue(_T("500"));
	ToolBarItem[c++] = ToolBar1->AddControl(SpinCtrlTranslate);
	ToolBarItem[c++] = ToolBar1->AddControl(StaticText1);
	ToolBar1->AddSeparator();
	
	//build input for rotation snapping
	SpinCtrlRotate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_ROTATE, _T("Schrittweite in Grad"), wxPoint(0,0), wxSize(60,20), 0, SNAP_IN_MINIMUM_DEGREE, SNAP_IN_MAXIMUM_DEGREE, 10, _T("ID_SPINCTRL_ROTATE"));
	StaticText2    = new wxStaticText(ToolBar1, ID_STATICTEXT2, _(" Grad"), wxPoint(3,13), wxSize(30,12), 0, _T("Schrittweite in Grad"));
	SpinCtrlRotate->SetValue(_T("10"));
	ToolBarItem[c++] = ToolBar1->AddControl(SpinCtrlRotate);
	ToolBarItem[c++] = ToolBar1->AddControl(StaticText2);
	ToolBar1->AddSeparator();
	
	//build exit button at the end
	ToolBarItem[c++] = ToolBar1->AddTool(btn_quit, _("GNR beenden"), wxBitmap(wxIcon(button_exit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("GNR beenden   [ALT+F4]"), _("GNR beenden?"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	//Center();
	
	//turn on snapping on menu by default
	ToolBar1->ToggleTool(btn_snap_to_grid,true);
	MenuItem9->Check(true);
}

GNRMainFrame::~GNRMainFrame()
{
}

void GNRMainFrame::OnMenuNewRoom(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("Ich werde dann mal für Dich aufräumen!"));
	
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(NEWROOM);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnMenuOpxOpen(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OPXOPEN);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOpxSave(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"), wxFD_SAVE);
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OPXSAVE);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOaxImport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuOaxExport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	// look if string is not empty
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
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuObjExport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Datei wählen..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"), wxFD_SAVE);
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuQuit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void GNRMainFrame::OnMenuAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString msg = wxbuildinfo(long_f);
	wxMessageBox(msg, _("GNR"));
}

void GNRMainFrame::OnToolbarMoveXZ(wxCommandEvent& WXUNUSED(event))
{
	MenuItem12->Check(true);
	ToolBar1->ToggleTool(btn_move_xz, true);
	
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarMoveXY(wxCommandEvent& WXUNUSED(event))
{
	MenuItem13->Check(true);
	ToolBar1->ToggleTool(btn_move_xy, true);
	
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXZ(wxCommandEvent& WXUNUSED(event))
{
	MenuItem14->Check(true);
	ToolBar1->ToggleTool(btn_rotate_xz, true);
	
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarRotateXY(wxCommandEvent& WXUNUSED(event))
{
	MenuItem15->Check(true);
	ToolBar1->ToggleTool(btn_rotate_xy, true);
	
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnToolbarDrawWall(wxCommandEvent& WXUNUSED(event))
{
	MenuItem16->Check(true);
	ToolBar1->ToggleTool(btn_draw_walls, true);
	
	GNRNotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(DRAWWALL);
	GetEventHandler()->ProcessEvent(myevent);
}

void GNRMainFrame::OnCreateScreenshot(wxCommandEvent& event)
{
	wxString filetypes;
	filetypes << wxT("PNG (*.png)|*.png");
	filetypes << wxT("|JPEG (*.jpg)|*.jpg");
	filetypes << wxT("|BMP (*.bmp)|*.bmp");
	filetypes << wxT("|TIFF (*.tif)|*.tif");
	const wxString& filename = wxFileSelector(wxT("Bild speichern unter..."), wxT(""), wxT(""), wxT(""), filetypes, wxFD_SAVE);
	
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.SetString(filename);
		gnrevent.setGNREventType(SCREENSHOT);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}


void GNRMainFrame::OnCameraReset(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETCAMERA);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnSnapToGridMenu(wxCommandEvent& WXUNUSED(event))
{
	//sync menu item and toolbar for snapping function
	ToolBar1->ToggleTool(btn_snap_to_grid, MenuItem9->IsChecked());
	OnSnapToGrid();
}

void GNRMainFrame::OnShadowsMenu(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(TOGGLESHADOWS);
	gnrevent.setBoolean(MenuItem32->IsChecked());
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnSnapToGridBtn(wxCommandEvent& WXUNUSED(event))
{
	//sync menu item and toolbar for snapping function
	MenuItem9->Check(ToolBarItem[16]->IsToggled());
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
	
	if (!ToolBarItem[16]->IsToggled())
	{
		snapAngle = 1;
		snapGrid  = 1;
	}
	
	gnrevent.setSnapToGrid(snapGrid);
	gnrevent.setSnapToAngle(snapAngle);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnToolbarUndo(wxCommandEvent& event)
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(UNDO);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnToolbarRedo(wxCommandEvent& event)
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REDO);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnGroupCreate(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CREATEGROUP);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnGroupModify(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(MODIFYGROUP);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnDeleteSelected(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DELETESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnCloneSelected(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CLONESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnHideSelected(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(HIDESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnShowHidden(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SHOWHIDDEN);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnCopySelected(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(COPYSELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnCutSelected(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CUTSELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnInsertCopy(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(INSERTCOPY);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnMenuHelp(wxCommandEvent& WXUNUSED(event))
{
	GNRHelpFrame* m_frame = new GNRHelpFrame(this,0);
	m_frame->Show(true);
}

void GNRMainFrame::setUndoEnabled(bool enabled)
{
	ToolBar1->EnableTool(btn_undo, enabled);
}

void GNRMainFrame::setRedoEnabled(bool enabled)
{
	ToolBar1->EnableTool(btn_redo, enabled);
}

void GNRMainFrame::OnZoomIn(wxCommandEvent& WXUNUSED(event))
{
	simulateMouseWheel(-10);
}

void GNRMainFrame::OnZoomOut(wxCommandEvent& WXUNUSED(event))
{
	simulateMouseWheel(10);
}

void GNRMainFrame::simulateMouseWheel(int direction)
{
	wxMouseEvent event(wxEVT_MOUSEWHEEL);
	GNRGLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	event.m_wheelRotation = direction*120;
	myevent.setMouseEvent(event);
	myevent.setCanvasID(CANVAS2D);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

wxStatusBar* GNRMainFrame::getStatusbar()
{
	return  StatusBar1;
}
