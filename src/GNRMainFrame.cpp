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

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
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
#include "resources/button-exit.xpm"
#include "resources/button-move-xy.xpm"
#include "resources/button-move-xz.xpm"
#include "resources/button-world-rotate-xy.xpm"
#include "resources/button-world-rotate-xz.xpm"
#include "resources/button-canvas2d-zoom-in.xpm"
#include "resources/button-canvas2d-zoom-out.xpm"
#include "resources/button-canvas2d-zoom-fit.xpm"
#include "resources/button-snap-to-grid.xpm"
#include "resources/button-draw-walls.xpm"
#include "resources/button-reset-object.xpm"

wxString wxbuildinfo()
{
	wxString wxbuild;
	
	wxbuild << _T("< GNR 3D Raumplaner >\n\n");
	wxbuild << _T("#if defined(PROGRAMMIERER)\n");
	wxbuild << _T(" #include \"Konstantin_Balabin.h\"\n");
	wxbuild << _T(" #include \"Patrick_Kracht.h\"\n");
	wxbuild << _T(" #include \"Thorsten_Moll.h\"\n");
	wxbuild << _T(" #include \"Valentin_Kunz.h\"\n");
	wxbuild << _T("#endif");
	
	return wxbuild;
}

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
const long GNRMainFrame::idMenuObjExport = wxNewId();
const long GNRMainFrame::idMenuOaxExport = wxNewId();
const long GNRMainFrame::idMenuOnScreenshot = wxNewId();
const long GNRMainFrame::idMenuObjImport = wxNewId();
const long GNRMainFrame::idMenuOaxImport = wxNewId();
const long GNRMainFrame::idMenuZoomIn = wxNewId();
const long GNRMainFrame::idMenuZoomOut = wxNewId();
const long GNRMainFrame::idMenuCameraReset = wxNewId();
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
const long GNRMainFrame::idMenuResetObject = wxNewId();
const long GNRMainFrame::ID_STATUSBAR = wxNewId();
const long GNRMainFrame::btn_room_new = wxNewId();
const long GNRMainFrame::btn_room_open = wxNewId();
const long GNRMainFrame::btn_room_save = wxNewId();
const long GNRMainFrame::btn_quit = wxNewId();
const long GNRMainFrame::btn_undo = wxNewId();
const long GNRMainFrame::btn_redo = wxNewId();
const long GNRMainFrame::btn_zoom_in = wxNewId();
const long GNRMainFrame::btn_zoom_out = wxNewId();
const long GNRMainFrame::btn_camera_reset = wxNewId();
const long GNRMainFrame::btn_move_xy = wxNewId();
const long GNRMainFrame::btn_move_xz = wxNewId();
const long GNRMainFrame::btn_rotate_xy = wxNewId();
const long GNRMainFrame::btn_rotate_xz = wxNewId();
const long GNRMainFrame::btn_snap_to_grid = wxNewId();
const long GNRMainFrame::btn_draw_walls = wxNewId();
const long GNRMainFrame::btn_reset_object = wxNewId();
const long GNRMainFrame::ID_TOOLBAR = wxNewId();
const long GNRMainFrame::ID_SPINCTRL_TRANS  = wxNewId();
const long GNRMainFrame::ID_SPINCTRL_ROTATE = wxNewId();
const long GNRMainFrame::ID_STATICTEXT1 = wxNewId();
const long GNRMainFrame::ID_STATICTEXT2 = wxNewId();

BEGIN_EVENT_TABLE(GNRMainFrame,wxFrame)
	//toolbar buttons
	EVT_MENU(btn_room_new, GNRMainFrame::OnMenuNewRoom)         //button new room
	EVT_MENU(btn_room_open, GNRMainFrame::OnMenuOpxOpen)        //button open
	EVT_MENU(btn_room_save, GNRMainFrame::OnMenuOpxSave)        //button save
	EVT_MENU(btn_undo, GNRMainFrame::OnToolbarUndo)             //button undo
	EVT_MENU(btn_redo, GNRMainFrame::OnToolbarRedo)             //button redo
	EVT_MENU(btn_move_xz, GNRMainFrame::OnToolbarMoveXZ)        //button move xy
	EVT_MENU(btn_move_xy, GNRMainFrame::OnToolbarMoveXY)        //button move xz
	EVT_MENU(btn_rotate_xz, GNRMainFrame::OnToolbarRotateXZ)    //button rotate xy
	EVT_MENU(btn_rotate_xy, GNRMainFrame::OnToolbarRotateXY)    //button rotate xz
	EVT_MENU(btn_draw_walls, GNRMainFrame::OnToolbarDrawWall)   //button draw wall
	EVT_MENU(btn_reset_object, GNRMainFrame::OnResetObject)     //button reset object
	EVT_MENU(btn_zoom_in, GNRMainFrame::OnZoomIn)               //button zoom in
	EVT_MENU(btn_zoom_out, GNRMainFrame::OnZoomOut)             //button zoom out
	EVT_MENU(btn_camera_reset, GNRMainFrame::OnCameraReset)     //button reset camera
	EVT_MENU(btn_snap_to_grid, GNRMainFrame::OnSnapToGridBtn)   //button toggle snap
	EVT_MENU(btn_quit, GNRMainFrame::OnMenuQuit)                //button quit
	//menu file
	EVT_MENU(idMenuNewRoom, GNRMainFrame::OnMenuNewRoom)
	EVT_MENU(idMenuOpxOpen, GNRMainFrame::OnMenuOpxOpen)
	EVT_MENU(idMenuOpxSave, GNRMainFrame::OnMenuOpxSave)
	EVT_MENU(idMenuQuit, GNRMainFrame::OnMenuQuit)
	//menu edit
	EVT_MENU(idMenuUndo, GNRMainFrame::OnToolbarUndo)
	EVT_MENU(idMenuRedo, GNRMainFrame::OnToolbarRedo)
	EVT_MENU(idMenuDeleteObject, GNRMainFrame::OnDeleteSelected)
	EVT_MENU(idMenuCutObject, GNRMainFrame::OnCutSelected)
	EVT_MENU(idMenuInsertObject, GNRMainFrame::OnInsertCopy)
	EVT_MENU(idMenuCopyObject, GNRMainFrame::OnCopySelected)
	EVT_MENU(idMenuCloneObject, GNRMainFrame::OnCloneSelected)
	EVT_MENU(idMenuHideObject, GNRMainFrame::OnHideSelected)
	//menu export
	EVT_MENU(idMenuObjExport, GNRMainFrame::OnMenuObjExport)
	EVT_MENU(idMenuOaxExport, GNRMainFrame::OnMenuOaxExport)
	EVT_MENU(idMenuOnScreenshot, GNRMainFrame::OnCreateScreenshot)
	//menu import
	EVT_MENU(idMenuObjImport, GNRMainFrame::OnMenuObjImport)
	EVT_MENU(idMenuOaxImport, GNRMainFrame::OnMenuOaxImport)
	//menu camera
	EVT_MENU(idMenuZoomIn, GNRMainFrame::OnZoomIn)
	EVT_MENU(idMenuZoomOut, GNRMainFrame::OnZoomOut)
	EVT_MENU(idMenuCameraReset, GNRMainFrame::OnCameraReset)
	//menu settings
	EVT_MENU(idMenuSnapToGrid, GNRMainFrame::OnSnapToGridMenu)
	EVT_MENU(idMenuMoveXZ, GNRMainFrame::OnToolbarMoveXZ)
	EVT_MENU(idMenuMoveXY, GNRMainFrame::OnToolbarMoveXY)
	EVT_MENU(idMenuRotateXZ, GNRMainFrame::OnToolbarRotateXZ)
	EVT_MENU(idMenuRotateXY, GNRMainFrame::OnToolbarRotateXY)
	EVT_MENU(idMenuDrawWall, GNRMainFrame::OnToolbarDrawWall)
	EVT_MENU(idMenuShadows, GNRMainFrame::OnShadowsMenu)
	EVT_MENU(idMenuResetObject, GNRMainFrame::OnResetObject)
	//menu group
	EVT_MENU(idMenuGroup, GNRMainFrame::OnGroupCreate)
	EVT_MENU(idMenuUngroup, GNRMainFrame::OnGroupModify)
	//menu help
	EVT_MENU(idMenuHelp, GNRMainFrame::OnMenuHelp)
	EVT_MENU(idMenuAbout, GNRMainFrame::OnMenuAbout)
	//set snap to grid on spinctrl change
	EVT_SPINCTRL(ID_SPINCTRL_ROTATE, GNRMainFrame::OnSnapToGridCtrl)
	EVT_SPINCTRL(ID_SPINCTRL_TRANS, GNRMainFrame::OnSnapToGridCtrl)
END_EVENT_TABLE()

GNRMainFrame::GNRMainFrame(wxWindow* parent, wxWindowID WXUNUSED(id))
{
	int width  = SOFTWARE_WIN_WIDTH;
	int height = SOFTWARE_WIN_HEIGHT;
	
	//build title from define
	wxString title;
	title << wxT(SOFTWARE_TITLE) << wxT(" [Version ") << wxT(SOFTWARE_VERSION) << wxT("]");
	
	//create main frame and set size
	Create(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	Move(wxPoint(0,0));
	SetClientSize(wxSize(width,height-19));
	SetMinSize(wxSize(width+8,height+8));
	SetFocus();
	SetIcon(wxICON(GNR_ICON));
	
	//build menu bar
	MenuBar = new wxMenuBar();
	ParentMenu_File = new wxMenu();
	MenuItem8 = new wxMenuItem(ParentMenu_File, idMenuNewRoom, _("&Neuer leerer Raum\tCTRL+N"), _("Raum leeren..."), wxITEM_NORMAL);
	ParentMenu_File->Append(MenuItem8);
	ParentMenu_File->AppendSeparator();
	MenuItem3 = new wxMenuItem(ParentMenu_File, idMenuOpxOpen, _("OPX &Öffnen\tCTRL+O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	ParentMenu_File->Append(MenuItem3);
	MenuItem4 = new wxMenuItem(ParentMenu_File, idMenuOpxSave, _("OPX &Speichern\tCTRL+S"), _("Datei speichern..."), wxITEM_NORMAL);
	ParentMenu_File->Append(MenuItem4);
	ParentMenu_File->AppendSeparator();
	MenuItem1 = new wxMenuItem(ParentMenu_File, idMenuQuit, _("GNR Schließen\tALT+F4"), _("GNR beenden..."), wxITEM_NORMAL);
	ParentMenu_File->Append(MenuItem1);
	MenuBar->Append(ParentMenu_File, _("&Datei"));
	ParentMenu_Edit = new wxMenu();
	MenuItem24 = new wxMenuItem(ParentMenu_Edit, idMenuUndo, _("&Rückgänig\tCTRL+Z"), _("Aktion rückgänig machen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem24);
	MenuItem25 = new wxMenuItem(ParentMenu_Edit, idMenuRedo, _("&Wiederherstellen\tCTRL+Y"), _("Aktion wiederherstellen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem25);
	ParentMenu_Edit->AppendSeparator();
	MenuItem19 = new wxMenuItem(ParentMenu_Edit, idMenuDeleteObject, _("Objekte ent&fernen\tDEL"), _("Objekte entfernen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem19);
	MenuItem30 = new wxMenuItem(ParentMenu_Edit, idMenuCutObject, _("Objekte &ausschneiden\tCTRL+X"), _("Objekte ausschneiden..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem30);
	MenuItem21 = new wxMenuItem(ParentMenu_Edit, idMenuInsertObject, _("Objekte &einfügen\tCTRL+V"), _("Objekte einfügen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem21);
	MenuItem22 = new wxMenuItem(ParentMenu_Edit, idMenuCopyObject, _("Objekte k&opieren\tCTRL+C"), _("Objekte kopieren..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem22);
	MenuItem31 = new wxMenuItem(ParentMenu_Edit, idMenuCloneObject, _("Objekte &klonen\tCTRL+D"), _("Objekte klonen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem31);
	ParentMenu_Edit->AppendSeparator();
	MenuItem20 = new wxMenuItem(ParentMenu_Edit, idMenuHideObject, _("Objekte &verstecken\tCTRL+H"), _("Objekte verstecken..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem20);
	MenuItem34 = new wxMenuItem(ParentMenu_Edit, idMenuResetObject, _("Objekte &zurücksetzen\tCTRL+R"), _("Objekte zurücksetzen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(MenuItem34);
	MenuBar->Append(ParentMenu_Edit, _("&Bearbeiten"));
	ParentMenu_Export = new wxMenu();
	MenuItem7 = new wxMenuItem(ParentMenu_Export, idMenuObjExport, _("OBJ E&xportieren\tALT+O"), _("Object-Datei exportieren..."), wxITEM_NORMAL);
	ParentMenu_Export->Append(MenuItem7);
	MenuItem33 = new wxMenuItem(ParentMenu_Export, idMenuOnScreenshot, _("&Screenshot erstellen\tF12"), _("Screenshot der 3D-Szene erstellen..."), wxITEM_NORMAL);
	ParentMenu_Export->Append(MenuItem33);
	MenuBar->Append(ParentMenu_Export, _("E&xportieren"));
	ParentMenu_Import = new wxMenu();
	MenuItem6 = new wxMenuItem(ParentMenu_Import, idMenuObjImport, _("OBJ &Importieren\tALT+I"), _("Object-Datei importieren..."), wxITEM_NORMAL);
	ParentMenu_Import->Append(MenuItem6);
	MenuItem10 = new wxMenuItem(ParentMenu_Import, idMenuOaxImport, _("OAX I&mportieren\tCTRL+I"), _("OAX Importieren..."), wxITEM_NORMAL);
	ParentMenu_Import->Append(MenuItem10);
	MenuBar->Append(ParentMenu_Import, _("&Importieren"));
	ParentMenu_Camera = new wxMenu();
	MenuItem26 = new wxMenuItem(ParentMenu_Camera, idMenuZoomIn, _("&Einzoomen\tPGUP"), _("In die 2D Ansicht hereinzoomen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(MenuItem26);
	MenuItem27 = new wxMenuItem(ParentMenu_Camera, idMenuZoomOut, _("&Auszoomen\tPGDN"), _("Aus der 2D Ansicht herauszoomen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(MenuItem27);
	ParentMenu_Camera->AppendSeparator();
	MenuItem29 = new wxMenuItem(ParentMenu_Camera, idMenuCameraReset, _("Aus&ganszustand\tHOME"), _("Kamera in Ausganszustand zurücksetzen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(MenuItem29);
	MenuBar->Append(ParentMenu_Camera, _("&Kamera"));
	ParentMenu_Settings = new wxMenu();
	MenuItem9 = new wxMenuItem(ParentMenu_Settings, idMenuSnapToGrid, _("Ein&rasten aktivieren\tF4"), _("Einrasten aktivieren..."), wxITEM_CHECK);
	ParentMenu_Settings->Append(MenuItem9);
	ParentMenu_Settings->AppendSeparator();
	MenuItem12 = new wxMenuItem(ParentMenu_Settings, idMenuMoveXZ, _("Verschieben X&Z\tF5"), _("Objekt verschieben entlang X- und Z-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(MenuItem12);
	MenuItem13 = new wxMenuItem(ParentMenu_Settings, idMenuMoveXY, _("Verschieben X&Y\tF6"), _("Objekt verschieben entlang X- und Y-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(MenuItem13);
	MenuItem14 = new wxMenuItem(ParentMenu_Settings, idMenuRotateXZ, _("Ro&tieren XZ\tF7"), _("Objekt rotieren an X- und Z-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(MenuItem14);
	MenuItem15 = new wxMenuItem(ParentMenu_Settings, idMenuRotateXY, _("R&otieren XY\tF8"), _("Objekt rotieren an X- und Y-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(MenuItem15);
	MenuItem16 = new wxMenuItem(ParentMenu_Settings, idMenuDrawWall, _("&Wände erstellen\tF9"), _("Wände im 2D-Modus erstellen..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(MenuItem16);
	ParentMenu_Settings->AppendSeparator();
	MenuItem32 = new wxMenuItem(ParentMenu_Settings, idMenuShadows, _("&Schatten aktivieren\tF10"), _("Schatten aktivieren..."), wxITEM_CHECK);
	ParentMenu_Settings->Append(MenuItem32);
	MenuBar->Append(ParentMenu_Settings, _("&Einstellungen"));
	ParentMenu_Groups = new wxMenu();
	MenuItem17 = new wxMenuItem(ParentMenu_Groups, idMenuGroup, _("&Gruppe erstellen\tCTRL+G"), _("Neue Gruppe erstellen..."), wxITEM_NORMAL);
	ParentMenu_Groups->Append(MenuItem17);
	MenuItem18 = new wxMenuItem(ParentMenu_Groups, idMenuUngroup, _("Gruppe &auflösen\tCTRL+F"), _("Gruppe auflösen..."), wxITEM_NORMAL);
	ParentMenu_Groups->Append(MenuItem18);
	MenuBar->Append(ParentMenu_Groups, _("Gr&uppen"));
	ParentMenu_Help = new wxMenu();
	MenuItem5 = new wxMenuItem(ParentMenu_Help, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	ParentMenu_Help->Append(MenuItem5);
	MenuItem2 = new wxMenuItem(ParentMenu_Help, idMenuAbout, _("&Über\tALT+F1"), _("Informationen über GNR..."), wxITEM_NORMAL);
	ParentMenu_Help->Append(MenuItem2);
	MenuBar->Append(ParentMenu_Help, _("&Hilfe"));
	SetMenuBar(MenuBar);
	
	//build and set status bar
	StatusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar);
	
	//generate toolbar and buttons
	int c = 0;
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(24,24));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxBitmap(wxIcon(button_room_new_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen   [CTRL+N]"), _("Raum erstellen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_open, _("Raum öffnen"), wxBitmap(wxIcon(button_room_open_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum öffnen"), _("Raum öffnen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxBitmap(wxIcon(button_room_save_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_undo, _("Rückgängig"), wxBitmap(wxIcon(button_undo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Rückgängig   [CTRL+Z]"), _("Rückgängig"));
	ToolBarItem[c-1]->Enable(false);
	ToolBarItem[c++] = ToolBar1->AddTool(btn_redo, _("Wiederherstellen"), wxBitmap(wxIcon(button_redo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Wiederherstellen   [CTRL+Y]"), _("Wiederherstellen"));
	ToolBarItem[c-1]->Enable(false);
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_reset_object, _("Selektierte Objekte wieder zurücksetzen"), wxBitmap(wxIcon(button_reset_object_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Selektierte Objekte wieder zurücksetzen   [CTRL+R]"), _("Selektierte Objekte wieder zurücksetzen"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxIcon(button_move_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Z-Richtung   [F5]"), _("Verschieben in X-Z-Richtung"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxIcon(button_move_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Y-Richtung   [F6]"), _("Verschieben in X-Y-Richtung"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_rotate_xz, _("Rotieren auf X-Z-Achsen"), wxBitmap(wxIcon(button_world_rotate_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Z-Achsen   [F7]"), _("Rotieren auf X-Z-Achsen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxIcon(button_world_rotate_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Y-Achsen   [F8]"), _("Rotieren auf X-Y-Achsen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_draw_walls, _("Wände zeichnen"), wxBitmap(wxIcon(button_draw_walls_xpm)), wxNullBitmap, wxITEM_RADIO, _("Wände zeichnen   [F9]"), _("Wände zeichnen"));
	ToolBar1->AddSeparator();
	ToolBarItem[c++] = ToolBar1->AddTool(btn_zoom_in, _("Draufsicht einzoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_in_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht einzoomen   [PGUP]"), _("Draufsicht einzoomen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_zoom_out, _("Draufsicht auszoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_out_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht auszoomen   [PGDN]"), _("Draufsicht auszoomen"));
	ToolBarItem[c++] = ToolBar1->AddTool(btn_camera_reset, _("Kamera zurücksetzen"), wxBitmap(wxIcon(button_canvas2d_zoom_fit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Kamera zurücksetzen   [HOME]"), _("Kamera zurücksetzen"));
	ToolBar1->AddSeparator();
	
	//toggle button for snap to grid function
	ToolBarItem[c++] = ToolBar1->AddTool(btn_snap_to_grid, _("Einrasten aktivieren"), wxBitmap(wxIcon(button_snap_to_grid_xpm)), wxNullBitmap, wxITEM_CHECK, _("Einrasten aktivieren   [F4]"), _("Einrasten aktivieren"));
	ToolBar1->AddSeparator();
	
	//build input for grid snapping
	SpinCtrlTranslate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_TRANS, _T("Schrittweite in mm"), wxPoint(0,0), wxSize(55,20), 0, SNAP_IN_MINIMUM_UNIT, SNAP_IN_MAXIMUM_UNIT, 10, _T("ID_SPINCTRL_TRANS"));
	StaticText1       = new wxStaticText(ToolBar1, ID_STATICTEXT1, _(" mm"), wxPoint(3,13), wxSize(20,12), 0, _T("Schrittweite in mm"));
	SpinCtrlTranslate->SetValue(_T("500"));
	ToolBarItem[c++] = ToolBar1->AddControl(SpinCtrlTranslate);
	ToolBarItem[c++] = ToolBar1->AddControl(StaticText1);
	ToolBar1->AddSeparator();
	
	//build input for rotation snapping
	SpinCtrlRotate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_ROTATE, _T("Schrittweite in Grad"), wxPoint(0,0), wxSize(44,20), 0, SNAP_IN_MINIMUM_DEGREE, SNAP_IN_MAXIMUM_DEGREE, 10, _T("ID_SPINCTRL_ROTATE"));
	StaticText2    = new wxStaticText(ToolBar1, ID_STATICTEXT2, _(" Grad"), wxPoint(3,13), wxSize(30,12), 0, _T("Schrittweite in Grad"));
	SpinCtrlRotate->SetValue(_T("45"));
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
	MenuItem32->Check(true);
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
	const wxString& filename = wxFileSelector(wxT("Szene als OPX öffnen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"));
	
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
	const wxString& filename = wxFileSelector(wxT("Szene als OPX speichern..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"), wxFD_SAVE);
	
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
	const wxString& filename = wxFileSelector(wxT("Object als OAX importieren..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
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
	const wxString& filename = wxFileSelector(wxT("Object als OAX exportieren..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

void GNRMainFrame::OnMenuObjImport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Object als OBJ importieren..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"));
	
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
	const wxString& filename = wxFileSelector(wxT("Szene als OBJ exportieren..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"), wxFD_SAVE);
	
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
	wxString msg = wxbuildinfo();
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

void GNRMainFrame::OnCreateScreenshot(wxCommandEvent& WXUNUSED(event))
{
	wxString filetypes;
	filetypes << wxT("PNG (*.png)|*.png");
	filetypes << wxT("|JPEG (*.jpg)|*.jpg");
	filetypes << wxT("|BMP (*.bmp)|*.bmp");
	filetypes << wxT("|TIFF (*.tif)|*.tif");
	const wxString& filename = wxFileSelector(wxT("Screenshot speichern unter..."), wxT(""), wxT(""), wxT(""), filetypes, wxFD_SAVE);
	
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
	MenuItem9->Check(ToolBarItem[14]->IsToggled());
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
	
	if (!ToolBarItem[14]->IsToggled())
	{
		snapAngle = 1;
		snapGrid  = 1;
	}
	
	gnrevent.setSnapToGrid(snapGrid);
	gnrevent.setSnapToAngle(snapAngle);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnToolbarUndo(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(UNDO);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRMainFrame::OnToolbarRedo(wxCommandEvent& WXUNUSED(event))
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

void GNRMainFrame::OnResetObject(wxCommandEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETOBJECT);
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
	return  StatusBar;
}
