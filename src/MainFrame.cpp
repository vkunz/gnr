/**
 * MainFrame
 * @name        MainFrame.cpp
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

#include "Enum.h"
#include "GlobalDefine.h"
#include "MainFrame.h"
#include "HelpFrame.h"
#include "GLNotifyEvent.h"
#include "NotifyEvent.h"

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
	wxbuild << _T("#if defined(ENTWICKLER)\n");
	wxbuild << _T(" #include \"Konstantin_Balabin.h\"\n");
	wxbuild << _T(" #include \"Patrick_Kracht.h\"\n");
	wxbuild << _T(" #include \"Thorsten_Moll.h\"\n");
	wxbuild << _T(" #include \"Valentin_Kunz.h\"\n");
	wxbuild << _T("#endif");
	
	return wxbuild;
}

#if defined(__ATHOS_DEBUG__)
const long MainFrame::idMenuItemDebug1 = wxNewId();
const long MainFrame::idMenuItemDebug2 = wxNewId();
const long MainFrame::idMenuItemDebug3 = wxNewId();
#endif
const long MainFrame::idMenuNewRoom = wxNewId();
const long MainFrame::idMenuOpxOpen = wxNewId();
const long MainFrame::idMenuOpxSave = wxNewId();
const long MainFrame::idMenuQuit = wxNewId();
const long MainFrame::idMenuUndo = wxNewId();
const long MainFrame::idMenuRedo = wxNewId();
const long MainFrame::idMenuDeleteObject = wxNewId();
const long MainFrame::idMenuCutObject = wxNewId();
const long MainFrame::idMenuInsertObject = wxNewId();
const long MainFrame::idMenuCopyObject = wxNewId();
const long MainFrame::idMenuCloneObject = wxNewId();
const long MainFrame::idMenuHideObject = wxNewId();
const long MainFrame::idMenuObjExport = wxNewId();
const long MainFrame::idMenuOaxExport = wxNewId();
const long MainFrame::idMenuOnScreenshot = wxNewId();
const long MainFrame::idMenuObjImport = wxNewId();
const long MainFrame::idMenuOaxImport = wxNewId();
const long MainFrame::idMenuZoomIn = wxNewId();
const long MainFrame::idMenuZoomOut = wxNewId();
const long MainFrame::idMenuCameraReset = wxNewId();
const long MainFrame::idMenuSnapToGrid = wxNewId();
const long MainFrame::idMenuMoveXZ = wxNewId();
const long MainFrame::idMenuMoveXY = wxNewId();
const long MainFrame::idMenuRotateXZ = wxNewId();
const long MainFrame::idMenuRotateXY = wxNewId();
const long MainFrame::idMenuDrawWall = wxNewId();
const long MainFrame::idMenuShadows = wxNewId();
const long MainFrame::idMenuGroup = wxNewId();
const long MainFrame::idMenuUngroup = wxNewId();
const long MainFrame::idMenuHelp = wxNewId();
const long MainFrame::idMenuAbout = wxNewId();
const long MainFrame::idMenuCreateCylinder = wxNewId();
const long MainFrame::idMenuCreateCone = wxNewId();
const long MainFrame::idMenuCreateCuboid = wxNewId();
const long MainFrame::idMenuCreateSphere = wxNewId();
const long MainFrame::idMenuCreatePyramide = wxNewId();
const long MainFrame::idMenuResetObject = wxNewId();
const long MainFrame::ID_STATUSBAR = wxNewId();
const long MainFrame::btn_room_new = wxNewId();
const long MainFrame::btn_room_open = wxNewId();
const long MainFrame::btn_room_save = wxNewId();
const long MainFrame::btn_quit = wxNewId();
const long MainFrame::btn_undo = wxNewId();
const long MainFrame::btn_redo = wxNewId();
const long MainFrame::btn_zoom_in = wxNewId();
const long MainFrame::btn_zoom_out = wxNewId();
const long MainFrame::btn_camera_reset = wxNewId();
const long MainFrame::btn_move_xy = wxNewId();
const long MainFrame::btn_move_xz = wxNewId();
const long MainFrame::btn_rotate_xy = wxNewId();
const long MainFrame::btn_rotate_xz = wxNewId();
const long MainFrame::btn_snap_to_grid = wxNewId();
const long MainFrame::btn_draw_walls = wxNewId();
const long MainFrame::btn_reset_object = wxNewId();
const long MainFrame::ID_TOOLBAR = wxNewId();
const long MainFrame::ID_SPINCTRL_TRANS  = wxNewId();
const long MainFrame::ID_SPINCTRL_ROTATE = wxNewId();
const long MainFrame::ID_STATICTEXT1 = wxNewId();
const long MainFrame::ID_STATICTEXT2 = wxNewId();

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
	#if defined(__ATHOS_DEBUG__)
	EVT_MENU(idMenuItemDebug1, MainFrame::OnMenuItemDebug1)
	EVT_MENU(idMenuItemDebug2, MainFrame::OnMenuItemDebug2)
	EVT_MENU(idMenuItemDebug3, MainFrame::OnMenuItemDebug3)
	#endif
	//toolbar buttons
	EVT_MENU(btn_room_new, MainFrame::OnMenuNewRoom)         //button new room
	EVT_MENU(btn_room_open, MainFrame::OnMenuOpxOpen)        //button open
	EVT_MENU(btn_room_save, MainFrame::OnMenuOpxSave)        //button save
	EVT_MENU(btn_undo, MainFrame::OnToolbarUndo)             //button undo
	EVT_MENU(btn_redo, MainFrame::OnToolbarRedo)             //button redo
	EVT_MENU(btn_move_xz, MainFrame::OnToolbarMoveXZ)        //button move xy
	EVT_MENU(btn_move_xy, MainFrame::OnToolbarMoveXY)        //button move xz
	EVT_MENU(btn_rotate_xz, MainFrame::OnToolbarRotateXZ)    //button rotate xy
	EVT_MENU(btn_rotate_xy, MainFrame::OnToolbarRotateXY)    //button rotate xz
	EVT_MENU(btn_draw_walls, MainFrame::OnToolbarDrawWall)   //button draw wall
	EVT_MENU(btn_reset_object, MainFrame::OnResetObject)     //button reset object
	EVT_MENU(btn_zoom_in, MainFrame::OnZoomIn)               //button zoom in
	EVT_MENU(btn_zoom_out, MainFrame::OnZoomOut)             //button zoom out
	EVT_MENU(btn_camera_reset, MainFrame::OnCameraReset)     //button reset camera
	EVT_MENU(btn_snap_to_grid, MainFrame::OnSnapToGridBtn)   //button toggle snap
	EVT_MENU(btn_quit, MainFrame::OnMenuQuit)                //button quit
	//menu file
	EVT_MENU(idMenuNewRoom, MainFrame::OnMenuNewRoom)
	EVT_MENU(idMenuOpxOpen, MainFrame::OnMenuOpxOpen)
	EVT_MENU(idMenuOpxSave, MainFrame::OnMenuOpxSave)
	EVT_MENU(idMenuQuit, MainFrame::OnMenuQuit)
	//menu edit
	EVT_MENU(idMenuUndo, MainFrame::OnToolbarUndo)
	EVT_MENU(idMenuRedo, MainFrame::OnToolbarRedo)
	EVT_MENU(idMenuDeleteObject, MainFrame::OnDeleteSelected)
	EVT_MENU(idMenuCutObject, MainFrame::OnCutSelected)
	EVT_MENU(idMenuInsertObject, MainFrame::OnInsertCopy)
	EVT_MENU(idMenuCopyObject, MainFrame::OnCopySelected)
	EVT_MENU(idMenuCloneObject, MainFrame::OnCloneSelected)
	EVT_MENU(idMenuHideObject, MainFrame::OnHideSelected)
	//menu export
	EVT_MENU(idMenuObjExport, MainFrame::OnMenuObjExport)
	EVT_MENU(idMenuOaxExport, MainFrame::OnMenuOaxExport)
	EVT_MENU(idMenuOnScreenshot, MainFrame::OnCreateScreenshot)
	//menu import
	EVT_MENU(idMenuObjImport, MainFrame::OnMenuObjImport)
	EVT_MENU(idMenuOaxImport, MainFrame::OnMenuOaxImport)
	//menu camera
	EVT_MENU(idMenuZoomIn, MainFrame::OnZoomIn)
	EVT_MENU(idMenuZoomOut, MainFrame::OnZoomOut)
	EVT_MENU(idMenuCameraReset, MainFrame::OnCameraReset)
	//menu settings
	EVT_MENU(idMenuSnapToGrid, MainFrame::OnSnapToGridMenu)
	EVT_MENU(idMenuMoveXZ, MainFrame::OnToolbarMoveXZ)
	EVT_MENU(idMenuMoveXY, MainFrame::OnToolbarMoveXY)
	EVT_MENU(idMenuRotateXZ, MainFrame::OnToolbarRotateXZ)
	EVT_MENU(idMenuRotateXY, MainFrame::OnToolbarRotateXY)
	EVT_MENU(idMenuDrawWall, MainFrame::OnToolbarDrawWall)
	EVT_MENU(idMenuShadows, MainFrame::OnShadowsMenu)
	EVT_MENU(idMenuResetObject, MainFrame::OnResetObject)
	//create primitves
	EVT_MENU(idMenuCreateCuboid, MainFrame::OnMenuCreateCuboid)
	EVT_MENU(idMenuCreateSphere, MainFrame::OnMenuCreateSphere)
	EVT_MENU(idMenuCreateCone, MainFrame::OnMenuCreateCone)
	EVT_MENU(idMenuCreateCylinder, MainFrame::OnMenuCreateCylinder)
	EVT_MENU(idMenuCreatePyramide, MainFrame::OnMenuCreatePyramide)
	//menu group
	EVT_MENU(idMenuGroup, MainFrame::OnGroupCreate)
	EVT_MENU(idMenuUngroup, MainFrame::OnGroupModify)
	//menu help
	EVT_MENU(idMenuHelp, MainFrame::OnMenuHelp)
	EVT_MENU(idMenuAbout, MainFrame::OnMenuAbout)
	//set snap to grid on spinctrl change
	EVT_SPINCTRL(ID_SPINCTRL_ROTATE, MainFrame::OnSnapToGridCtrl)
	EVT_SPINCTRL(ID_SPINCTRL_TRANS, MainFrame::OnSnapToGridCtrl)
END_EVENT_TABLE()

/**
 * constructor of MainFrame
 * @param[in]       parent          Parent-Window
 */
MainFrame::MainFrame(wxWindow* parent)
{
	int width  = SOFTWARE_WIN_WIDTH;
	int height = SOFTWARE_WIN_HEIGHT;
	
	//build title from define
	wxString title;
	title << wxT(SOFTWARE_TITLE) << wxT(" [Version ") << wxT(SOFTWARE_VERSION) << wxT("]");
	
	//create main frame and set size
	Create(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	Move(wxPoint(0,0));
	SetClientSize(wxSize(width-8,height-27));
	SetMinSize(wxSize(width,height));
	SetFocus();
	SetIcon(wxICON(gnr_icon));
	
	//build menu bar
	MenuBar                     = new wxMenuBar();
	
	//build file menu
	ParentMenu_File             = new wxMenu();
	m_MenuItem[idMenuNewRoom]   = new wxMenuItem(ParentMenu_File, idMenuNewRoom, _("&Neuer leerer Raum\tCTRL+N"), _("Raum leeren..."), wxITEM_NORMAL);
	ParentMenu_File->Append(m_MenuItem[idMenuNewRoom]);
	ParentMenu_File->AppendSeparator();
	
	m_MenuItem[idMenuOpxOpen]   = new wxMenuItem(ParentMenu_File, idMenuOpxOpen, _("OPX &Öffnen\tCTRL+O"), _("vorhandene Datei öffnen..."), wxITEM_NORMAL);
	ParentMenu_File->Append(m_MenuItem[idMenuOpxOpen]);
	m_MenuItem[idMenuOpxSave]   = new wxMenuItem(ParentMenu_File, idMenuOpxSave, _("OPX &Speichern\tCTRL+S"), _("Datei speichern..."), wxITEM_NORMAL);
	ParentMenu_File->Append(m_MenuItem[idMenuOpxSave]);
	ParentMenu_File->AppendSeparator();
	
	m_MenuItem[idMenuQuit]      = new wxMenuItem(ParentMenu_File, idMenuQuit, _(" Schließen\tALT+F4"), _(" beenden..."), wxITEM_NORMAL);
	ParentMenu_File->Append(m_MenuItem[idMenuQuit]);
	MenuBar->Append(ParentMenu_File, _("&Datei"));
	
	//build edit menu
	ParentMenu_Edit = new wxMenu();
	m_MenuItem[idMenuUndo] = new wxMenuItem(ParentMenu_Edit, idMenuUndo, _("&Rückgänig\tCTRL+Z"), _("Aktion rückgänig machen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuUndo]);
	m_MenuItem[idMenuRedo] = new wxMenuItem(ParentMenu_Edit, idMenuRedo, _("&Wiederherstellen\tCTRL+Y"), _("Aktion wiederherstellen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuRedo]);
	ParentMenu_Edit->AppendSeparator();
	
	m_MenuItem[idMenuDeleteObject] = new wxMenuItem(ParentMenu_Edit, idMenuDeleteObject, _("Objekte ent&fernen\tDEL"), _("Objekte entfernen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuDeleteObject]);
	m_MenuItem[idMenuCutObject] = new wxMenuItem(ParentMenu_Edit, idMenuCutObject, _("Objekte &ausschneiden\tCTRL+X"), _("Objekte ausschneiden..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuCutObject]);
	m_MenuItem[idMenuInsertObject] = new wxMenuItem(ParentMenu_Edit, idMenuInsertObject, _("Objekte &einfügen\tCTRL+V"), _("Objekte einfügen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuInsertObject]);
	m_MenuItem[idMenuCopyObject] = new wxMenuItem(ParentMenu_Edit, idMenuCopyObject, _("Objekte k&opieren\tCTRL+C"), _("Objekte kopieren..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuCopyObject]);
	m_MenuItem[idMenuCloneObject] = new wxMenuItem(ParentMenu_Edit, idMenuCloneObject, _("Objekte &klonen\tCTRL+D"), _("Objekte klonen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuCloneObject]);
	ParentMenu_Edit->AppendSeparator();
	
	m_MenuItem[idMenuHideObject] = new wxMenuItem(ParentMenu_Edit, idMenuHideObject, _("Objekte &verstecken\tCTRL+H"), _("Objekte verstecken..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuHideObject]);
	m_MenuItem[idMenuResetObject] = new wxMenuItem(ParentMenu_Edit, idMenuResetObject, _("Objekte &zurücksetzen\tCTRL+R"), _("Objekte zurücksetzen..."), wxITEM_NORMAL);
	ParentMenu_Edit->Append(m_MenuItem[idMenuResetObject]);
	MenuBar->Append(ParentMenu_Edit, _("&Bearbeiten"));
	
	//build export menu
	ParentMenu_Export = new wxMenu();
	m_MenuItem[idMenuObjExport] = new wxMenuItem(ParentMenu_Export, idMenuObjExport, _("OBJ E&xportieren\tALT+O"), _("Object-Datei exportieren..."), wxITEM_NORMAL);
	ParentMenu_Export->Append(m_MenuItem[idMenuObjExport]);
	m_MenuItem[idMenuOnScreenshot] = new wxMenuItem(ParentMenu_Export, idMenuOnScreenshot, _("&Screenshot erstellen\tF12"), _("Screenshot der 3D-Szene erstellen..."), wxITEM_NORMAL);
	ParentMenu_Export->Append(m_MenuItem[idMenuOnScreenshot]);
	MenuBar->Append(ParentMenu_Export, _("E&xportieren"));
	
	//build import menu
	ParentMenu_Import = new wxMenu();
	m_MenuItem[idMenuObjImport] = new wxMenuItem(ParentMenu_Import, idMenuObjImport, _("OBJ &Importieren\tALT+I"), _("Object-Datei importieren..."), wxITEM_NORMAL);
	ParentMenu_Import->Append(m_MenuItem[idMenuObjImport]);
	m_MenuItem[idMenuOaxImport] = new wxMenuItem(ParentMenu_Import, idMenuOaxImport, _("OAX I&mportieren\tCTRL+I"), _("OAX Importieren..."), wxITEM_NORMAL);
	ParentMenu_Import->Append(m_MenuItem[idMenuOaxImport]);
	MenuBar->Append(ParentMenu_Import, _("&Importieren"));
	
	//build camera menu
	ParentMenu_Camera = new wxMenu();
	m_MenuItem[idMenuZoomIn] = new wxMenuItem(ParentMenu_Camera, idMenuZoomIn, _("&Einzoomen\tPGUP"), _("In die 2D Ansicht hereinzoomen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(m_MenuItem[idMenuZoomIn]);
	m_MenuItem[idMenuZoomOut] = new wxMenuItem(ParentMenu_Camera, idMenuZoomOut, _("&Auszoomen\tPGDN"), _("Aus der 2D Ansicht herauszoomen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(m_MenuItem[idMenuZoomOut]);
	ParentMenu_Camera->AppendSeparator();
	
	m_MenuItem[idMenuCameraReset] = new wxMenuItem(ParentMenu_Camera, idMenuCameraReset, _("Aus&ganszustand\tHOME"), _("Kamera in Ausganszustand zurücksetzen..."), wxITEM_NORMAL);
	ParentMenu_Camera->Append(m_MenuItem[idMenuCameraReset]);
	MenuBar->Append(ParentMenu_Camera, _("&Kamera"));
	
	//build settings menu
	ParentMenu_Settings = new wxMenu();
	m_MenuItem[idMenuSnapToGrid] = new wxMenuItem(ParentMenu_Settings, idMenuSnapToGrid, _("Ein&rasten aktivieren\tF4"), _("Einrasten aktivieren..."), wxITEM_CHECK);
	ParentMenu_Settings->Append(m_MenuItem[idMenuSnapToGrid]);
	ParentMenu_Settings->AppendSeparator();
	
	m_MenuItem[idMenuMoveXZ] = new wxMenuItem(ParentMenu_Settings, idMenuMoveXZ, _("Verschieben X&Z\tF5"), _("Objekt verschieben entlang X- und Z-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(m_MenuItem[idMenuMoveXZ]);
	m_MenuItem[idMenuMoveXY] = new wxMenuItem(ParentMenu_Settings, idMenuMoveXY, _("Verschieben X&Y\tF6"), _("Objekt verschieben entlang X- und Y-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(m_MenuItem[idMenuMoveXY]);
	m_MenuItem[idMenuRotateXZ] = new wxMenuItem(ParentMenu_Settings, idMenuRotateXZ, _("Ro&tieren XZ\tF7"), _("Objekt rotieren an X- und Z-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(m_MenuItem[idMenuRotateXZ]);
	m_MenuItem[idMenuRotateXY] = new wxMenuItem(ParentMenu_Settings, idMenuRotateXY, _("R&otieren XY\tF8"), _("Objekt rotieren an X- und Y-Achse..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(m_MenuItem[idMenuRotateXY]);
	m_MenuItem[idMenuDrawWall] = new wxMenuItem(ParentMenu_Settings, idMenuDrawWall, _("&Wände erstellen\tF9"), _("Wände im 2D-Modus erstellen..."), wxITEM_RADIO);
	ParentMenu_Settings->Append(m_MenuItem[idMenuDrawWall]);
	ParentMenu_Settings->AppendSeparator();
	
	m_MenuItem[idMenuShadows] = new wxMenuItem(ParentMenu_Settings, idMenuShadows, _("&Schatten aktivieren\tF10"), _("Schatten aktivieren..."), wxITEM_CHECK);
	ParentMenu_Settings->Append(m_MenuItem[idMenuShadows]);
	MenuBar->Append(ParentMenu_Settings, _("&Einstellungen"));
	
	//build groups menu
	ParentMenu_Groups = new wxMenu();
	m_MenuItem[idMenuGroup] = new wxMenuItem(ParentMenu_Groups, idMenuGroup, _("&Gruppe erstellen\tCTRL+G"), _("Neue Gruppe erstellen..."), wxITEM_NORMAL);
	ParentMenu_Groups->Append(m_MenuItem[idMenuGroup]);
	m_MenuItem[idMenuUngroup] = new wxMenuItem(ParentMenu_Groups, idMenuUngroup, _("Gruppe &auflösen\tCTRL+F"), _("Gruppe auflösen..."), wxITEM_NORMAL);
	ParentMenu_Groups->Append(m_MenuItem[idMenuUngroup]);
	MenuBar->Append(ParentMenu_Groups, _("Gr&uppen"));
	
	//build create menu
	ParentMenu_Create = new wxMenu();
	m_MenuItem[idMenuCreateCone] = new wxMenuItem(ParentMenu_Create, idMenuCreateCone, _("Kegel erstellen\tCTRL+1"), _("Kegel erstellen..."), wxITEM_NORMAL);
	ParentMenu_Create->Append(m_MenuItem[idMenuCreateCone]);
	m_MenuItem[idMenuCreateCylinder] = new wxMenuItem(ParentMenu_Create, idMenuCreateCylinder, _("Zylinder erstellen\tCTRL+2"), _("Zylinder erstellen..."), wxITEM_NORMAL);
	ParentMenu_Create->Append(m_MenuItem[idMenuCreateCylinder]);
	m_MenuItem[idMenuCreateCuboid] = new wxMenuItem(ParentMenu_Create, idMenuCreateCuboid, _("Kubus erstellen\tCTRL+3"), _("Kubus erstellen..."), wxITEM_NORMAL);
	ParentMenu_Create->Append(m_MenuItem[idMenuCreateCuboid]);
	m_MenuItem[idMenuCreatePyramide] = new wxMenuItem(ParentMenu_Create, idMenuCreatePyramide, _("Pyramide erstellen\tCTRL+4"), _("Pyramide erstellen..."), wxITEM_NORMAL);
	ParentMenu_Create->Append(m_MenuItem[idMenuCreatePyramide]);
	m_MenuItem[idMenuCreateSphere] = new wxMenuItem(ParentMenu_Create, idMenuCreateSphere, _("Kugel erstellen\tCTRL+5"), _("Kugel erstellen..."), wxITEM_NORMAL);
	ParentMenu_Create->Append(m_MenuItem[idMenuCreateSphere]);
	MenuBar->Append(ParentMenu_Create, _("&Primitive"));
	
	//build help menu
	ParentMenu_Help = new wxMenu();
	m_MenuItem[idMenuHelp] = new wxMenuItem(ParentMenu_Help, idMenuHelp, _("&Hilfe\tF1"), _("Hilfe zur Anwendung"), wxITEM_NORMAL);
	ParentMenu_Help->Append(m_MenuItem[idMenuHelp]);
	m_MenuItem[idMenuAbout] = new wxMenuItem(ParentMenu_Help, idMenuAbout, _("&Über\tALT+F1"), _("Informationen über ..."), wxITEM_NORMAL);
	ParentMenu_Help->Append(m_MenuItem[idMenuAbout]);
	MenuBar->Append(ParentMenu_Help, _("&Hilfe"));
	
#if defined(__ATHOS_DEBUG__)
	//build debug menu
	ParentMenu_Debug = new wxMenu();
	MenuItemDebug1 = new wxMenuItem(ParentMenu_Debug, idMenuItemDebug1, _("&Load Test Cubes"), _(""), wxITEM_NORMAL);
	ParentMenu_Debug->Append(MenuItemDebug1);
	MenuItemDebug2 = new wxMenuItem(ParentMenu_Debug, idMenuItemDebug2, _("&Load Test Tie Fighters"), _(""), wxITEM_NORMAL);
	ParentMenu_Debug->Append(MenuItemDebug2);
	MenuItemDebug3 = new wxMenuItem(ParentMenu_Debug, idMenuItemDebug3, _("&Dump World Structure"), _(""), wxITEM_NORMAL);
	ParentMenu_Debug->Append(MenuItemDebug3);
	MenuBar->Append(ParentMenu_Debug, _("&Debug"));
#endif
	
	//set active menu bar
	SetMenuBar(MenuBar);
	
	//build and set status bar
	StatusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
	int __wxStatusBarWidths_1[1] = { -1 };
	int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
	StatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
	StatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
	SetStatusBar(StatusBar);
	
	//generate toolbar and buttons
	ToolBar1 = new wxToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
	ToolBar1->SetToolBitmapSize(wxSize(24,24));
	
	//build toolbar first 3 buttons
	m_ToolBarItem[btn_room_new] = ToolBar1->AddTool(btn_room_new, _("Raum erstellen"), wxBitmap(wxIcon(button_room_new_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum erstellen   [CTRL+N]"), _("Raum erstellen"));
	m_ToolBarItem[btn_room_open] = ToolBar1->AddTool(btn_room_open, _("Raum öffnen"), wxBitmap(wxIcon(button_room_open_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum öffnen"), _("Raum öffnen"));
	m_ToolBarItem[btn_room_save] = ToolBar1->AddTool(btn_room_save, _("Raum speichern"), wxBitmap(wxIcon(button_room_save_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Raum speichern"), _("Raum speichern"));
	ToolBar1->AddSeparator();
	
	//undo & redo buttons
	m_ToolBarItem[btn_undo] = ToolBar1->AddTool(btn_undo, _("Rückgängig"), wxBitmap(wxIcon(button_undo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Rückgängig   [CTRL+Z]"), _("Rückgängig"));
	m_ToolBarItem[btn_undo]->Enable(false);
	m_ToolBarItem[btn_redo] = ToolBar1->AddTool(btn_redo, _("Wiederherstellen"), wxBitmap(wxIcon(button_redo_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Wiederherstellen   [CTRL+Y]"), _("Wiederherstellen"));
	m_ToolBarItem[btn_redo]->Enable(false);
	ToolBar1->AddSeparator();
	
	//object reset
	m_ToolBarItem[btn_reset_object] = ToolBar1->AddTool(btn_reset_object, _("Selektierte Objekte wieder zurücksetzen"), wxBitmap(wxIcon(button_reset_object_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Selektierte Objekte wieder zurücksetzen   [CTRL+R]"), _("Selektierte Objekte wieder zurücksetzen"));
	ToolBar1->AddSeparator();
	
	//move, rotate and wall drawing mode buttons
	m_ToolBarItem[btn_move_xz] = ToolBar1->AddTool(btn_move_xz, _("Verschieben in X-Z-Richtung"), wxBitmap(wxIcon(button_move_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Z-Richtung   [F5]"), _("Verschieben in X-Z-Richtung"));
	m_ToolBarItem[btn_move_xy] = ToolBar1->AddTool(btn_move_xy, _("Verschieben in X-Y-Richtung"), wxBitmap(wxIcon(button_move_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Verschieben in X-Y-Richtung   [F6]"), _("Verschieben in X-Y-Richtung"));
	m_ToolBarItem[btn_rotate_xz] = ToolBar1->AddTool(btn_rotate_xz, _("Rotieren auf X-Z-Achsen"), wxBitmap(wxIcon(button_world_rotate_xz_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Z-Achsen   [F7]"), _("Rotieren auf X-Z-Achsen"));
	m_ToolBarItem[btn_rotate_xy] = ToolBar1->AddTool(btn_rotate_xy, _("Rotieren auf X-Y-Achsen"), wxBitmap(wxIcon(button_world_rotate_xy_xpm)), wxNullBitmap, wxITEM_RADIO, _("Rotieren auf X-Y-Achsen   [F8]"), _("Rotieren auf X-Y-Achsen"));
	m_ToolBarItem[btn_draw_walls] = ToolBar1->AddTool(btn_draw_walls, _("Wände zeichnen"), wxBitmap(wxIcon(button_draw_walls_xpm)), wxNullBitmap, wxITEM_RADIO, _("Wände zeichnen   [F9]"), _("Wände zeichnen"));
	ToolBar1->AddSeparator();
	
	//zoom buttons & camera reset
	m_ToolBarItem[btn_zoom_in] = ToolBar1->AddTool(btn_zoom_in, _("Draufsicht einzoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_in_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht einzoomen   [PGUP]"), _("Draufsicht einzoomen"));
	m_ToolBarItem[btn_zoom_out] = ToolBar1->AddTool(btn_zoom_out, _("Draufsicht auszoomen"), wxBitmap(wxIcon(button_canvas2d_zoom_out_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Draufsicht auszoomen   [PGDN]"), _("Draufsicht auszoomen"));
	m_ToolBarItem[btn_camera_reset] = ToolBar1->AddTool(btn_camera_reset, _("Kamera zurücksetzen"), wxBitmap(wxIcon(button_canvas2d_zoom_fit_xpm)), wxNullBitmap, wxITEM_NORMAL, _("Kamera zurücksetzen   [HOME]"), _("Kamera zurücksetzen"));
	ToolBar1->AddSeparator();
	
	//toggle button for snap to grid function
	m_ToolBarItem[btn_snap_to_grid] = ToolBar1->AddTool(btn_snap_to_grid, _("Einrasten aktivieren"), wxBitmap(wxIcon(button_snap_to_grid_xpm)), wxNullBitmap, wxITEM_CHECK, _("Einrasten aktivieren   [F4]"), _("Einrasten aktivieren"));
	ToolBar1->AddSeparator();
	
	//build input for grid snapping
	SpinCtrlTranslate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_TRANS, _T("Schrittweite in mm"), wxPoint(0,0), wxSize(55,20), 0, SNAP_IN_MINIMUM_UNIT, SNAP_IN_MAXIMUM_UNIT, 10, _T("ID_SPINCTRL_TRANS"));
	StaticText1       = new wxStaticText(ToolBar1, ID_STATICTEXT1, _(" mm"), wxPoint(3,13), wxSize(20,12), 0, _T("Schrittweite in mm"));
	SpinCtrlTranslate->SetValue(_T("500"));
	m_ToolBarItem[ID_SPINCTRL_TRANS] = ToolBar1->AddControl(SpinCtrlTranslate);
	m_ToolBarItem[ID_STATICTEXT1] = ToolBar1->AddControl(StaticText1);
	ToolBar1->AddSeparator();
	
	//build input for rotation snapping
	SpinCtrlRotate = new wxSpinCtrl(ToolBar1, ID_SPINCTRL_ROTATE, _T("Schrittweite in Grad"), wxPoint(0,0), wxSize(44,20), 0, SNAP_IN_MINIMUM_DEGREE, SNAP_IN_MAXIMUM_DEGREE, 10, _T("ID_SPINCTRL_ROTATE"));
	StaticText2    = new wxStaticText(ToolBar1, ID_STATICTEXT2, _(" Grad"), wxPoint(3,13), wxSize(30,12), 0, _T("Schrittweite in Grad"));
	SpinCtrlRotate->SetValue(_T("45"));
	m_ToolBarItem[ID_SPINCTRL_ROTATE] = ToolBar1->AddControl(SpinCtrlRotate);
	m_ToolBarItem[ID_STATICTEXT2] = ToolBar1->AddControl(StaticText2);
	ToolBar1->AddSeparator();
	
	//build exit button at the end
	m_ToolBarItem[btn_quit] = ToolBar1->AddTool(btn_quit, _(" beenden"), wxBitmap(wxIcon(button_exit_xpm)), wxNullBitmap, wxITEM_NORMAL, _(" beenden   [ALT+F4]"), _(" beenden?"));
	ToolBar1->Realize();
	SetToolBar(ToolBar1);
	//Center();
	
	//turn on snapping on menu by default
	ToolBar1->ToggleTool(btn_snap_to_grid,SNAP_TO_GRID_DEFAULT);
	m_MenuItem[idMenuSnapToGrid]->Check(SNAP_TO_GRID_DEFAULT);
	
	//shadows checked?
	m_MenuItem[idMenuShadows]->Check(SHADOWS_DEFAULT);
}

/**
 * destructor of MainFrame
 */
MainFrame::~MainFrame()
{
}

/**
 * catches the button/menu klick for new room
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuNewRoom(wxCommandEvent& WXUNUSED(event))
{
	int answer = wxMessageBox(wxT("Wollen Sie den Raum wirklick leeren?"), wxT("Sind Sie sicher?"), wxYES_NO, this);
	if (answer == wxYES)
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(NEWROOM);
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for opx-open
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuOpxOpen(wxCommandEvent& WXUNUSED(event))
{
	int answer = wxMessageBox(wxT("Wollen Sie den aktuellen Raum wirklick ersetzen?"), wxT("Sind Sie sicher?"), wxYES_NO, this);
	if (answer == wxYES)
	{
		const wxString& filename = wxFileSelector(wxT("Szene als OPX öffnen..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"));
		
		// look if string is not empty
		if (!filename.IsEmpty())
		{
			NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
			gnrevent.setGNREventType(OPXOPEN);
			gnrevent.SetString(filename);
			
			GetEventHandler()->ProcessEvent(gnrevent);
		}
	}
}

/**
 * catches the button/menu klick for opx-save
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuOpxSave(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Szene als OPX speichern..."), wxT(""), wxT(""), wxT(""), wxT("OpxDatei (*.opx)|*.opx"), wxFD_SAVE);
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OPXSAVE);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for oax-import
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuOaxImport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Object als OAX importieren..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for oax-export
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuOaxExport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Object als OAX exportieren..."), wxT(""), wxT(""), wxT(""), wxT("OaxDatei (*.oax)|*.oax"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OAXEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for obj-import
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuObjImport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Object als OBJ importieren..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"));
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJIMPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for obj-export
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuObjExport(wxCommandEvent& WXUNUSED(event))
{
	const wxString& filename = wxFileSelector(wxT("Szene als OBJ exportieren..."), wxT("Datei wählen..."), wxT(""), wxT("Datei wählen..."), wxT("ObjDatei (*.obj)|*.obj"), wxFD_SAVE);
	
	// look if string is not empty
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(OBJEXPORT);
		gnrevent.SetString(filename);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for application-exit
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuQuit(wxCommandEvent& WXUNUSED(event))
{
	int answer = wxMessageBox(wxT("Wollen Sie das Programm wirklich verlassen?"), wxT("Beenden"), wxYES_NO, this);
	if (answer == wxYES)
	{
		Close();
	}
}

/**
 * catches the button/menu klick for about-information
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString msg = wxbuildinfo();
	wxMessageBox(msg, _(""));
}

/**
 * catches the button/menu klick for assembly-move in xz
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarMoveXZ(wxCommandEvent& WXUNUSED(event))
{
	m_MenuItem[idMenuMoveXZ]->Check(true);
	ToolBar1->ToggleTool(btn_move_xz, true);
	
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for assembly-move in xy
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarMoveXY(wxCommandEvent& WXUNUSED(event))
{
	m_MenuItem[idMenuMoveXY]->Check(true);
	ToolBar1->ToggleTool(btn_move_xy, true);
	
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(MOVEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for assembly-rotate in xz
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarRotateXZ(wxCommandEvent& WXUNUSED(event))
{
	m_MenuItem[idMenuRotateXZ]->Check(true);
	ToolBar1->ToggleTool(btn_rotate_xz, true);
	
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXZ);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for assembly-rotate in xy
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarRotateXY(wxCommandEvent& WXUNUSED(event))
{
	m_MenuItem[idMenuRotateXY]->Check(true);
	ToolBar1->ToggleTool(btn_rotate_xy, true);
	
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(ROTATEXY);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for cuboid-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuCreateCuboid(wxCommandEvent& WXUNUSED(event))
{
#warning: "TODO OnMenuCreateCuboid, event ready!"
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.SetEventObject(this);
	myevent.SetInt(CREATECUBOID);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for cone-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuCreateCone(wxCommandEvent& WXUNUSED(event))
{
#warning: "TODO OnMenuCreateCone, event ready!"
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.SetEventObject(this);
	myevent.SetInt(CREATECONE);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for sphere-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuCreateSphere(wxCommandEvent& WXUNUSED(event))
{
#warning: "TODO OnMenuCreateSphere, event ready!"
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.SetEventObject(this);
	myevent.SetInt(CREATESPHERE);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for cylinder-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuCreateCylinder(wxCommandEvent& WXUNUSED(event))
{
#warning: "TODO OnMenuCreateCylinder, event ready!"
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.SetEventObject(this);
	myevent.SetInt(CREATECYLINDER);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for pyramide-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuCreatePyramide(wxCommandEvent& WXUNUSED(event))
{
#warning: "TODO OnMenuCreatePyramide, event ready!"
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.SetEventObject(this);
	myevent.SetInt(CREATEPYRAMIDE);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for wall-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarDrawWall(wxCommandEvent& WXUNUSED(event))
{
	m_MenuItem[idMenuDrawWall]->Check(true);
	ToolBar1->ToggleTool(btn_draw_walls, true);
	
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(TOOLBARCHANGE);
	myevent.SetEventObject(this);
	myevent.SetInt(DRAWWALL);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * catches the button/menu klick for screenshot-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnCreateScreenshot(wxCommandEvent& WXUNUSED(event))
{
	wxString filetypes;
	filetypes << wxT("PNG (*.png)|*.png");
	filetypes << wxT("|JPEG (*.jpg)|*.jpg");
	filetypes << wxT("|BMP (*.bmp)|*.bmp");
	filetypes << wxT("|TIFF (*.tif)|*.tif");
	const wxString& filename = wxFileSelector(wxT("Screenshot speichern unter..."), wxT(""), wxT(""), wxT(""), filetypes, wxFD_SAVE);
	
	if (!filename.IsEmpty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.SetString(filename);
		gnrevent.setGNREventType(SCREENSHOT);
		
		GetEventHandler()->ProcessEvent(gnrevent);
	}
}

/**
 * catches the button/menu klick for camera-reset
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnCameraReset(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETCAMERA);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for new room
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnSnapToGridMenu(wxCommandEvent& WXUNUSED(event))
{
	//sync menu item and toolbar for snapping function
	ToolBar1->ToggleTool(btn_snap_to_grid, m_MenuItem[idMenuSnapToGrid]->IsChecked());
	OnSnapToGrid();
}

/**
 * catches the button/menu klick for shadow-option
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnShadowsMenu(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(TOGGLESHADOWS);
	gnrevent.setBoolean(m_MenuItem[idMenuShadows]->IsChecked());
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for snap-to-grid-option
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnSnapToGridBtn(wxCommandEvent& WXUNUSED(event))
{
	//sync menu item and toolbar for snapping function
	m_MenuItem[idMenuSnapToGrid]->Check(m_ToolBarItem[btn_snap_to_grid]->IsToggled());
	OnSnapToGrid();
}

/**
 * catches the button/menu klick for snap-to-grid-option
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnSnapToGridCtrl(wxSpinEvent& WXUNUSED(event))
{
	OnSnapToGrid();
}

/**
 * performes action for snap-to-grid-change
 */
void MainFrame::OnSnapToGrid()
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SNAPTOGRID);
	
	int snapGrid  = SpinCtrlTranslate->GetValue();
	int snapAngle = SpinCtrlRotate->GetValue();
	
	if (!m_ToolBarItem[btn_snap_to_grid]->IsToggled())
	{
		snapAngle = 1;
		snapGrid  = 1;
	}
	
	gnrevent.setSnapToGrid(snapGrid);
	gnrevent.setSnapToAngle(snapAngle);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for undo
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarUndo(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(UNDO);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for redo
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnToolbarRedo(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(REDO);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for group-creation
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnGroupCreate(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CREATEGROUP);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void MainFrame::OnGroupModify(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(MODIFYGROUP);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for deleting selected
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnDeleteSelected(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DELETESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for cloning selected
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnCloneSelected(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CLONESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for hiding selected
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnHideSelected(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(HIDESELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for coping selected
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnCopySelected(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(COPYSELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for cutting selected
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnCutSelected(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(CUTSELECTED);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for resetting an object
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnResetObject(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(RESETOBJECT);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for pasting copied objects
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnInsertCopy(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(INSERTCOPY);
	GetEventHandler()->ProcessEvent(gnrevent);
}

/**
 * catches the button/menu klick for viewing help-menu
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnMenuHelp(wxCommandEvent& WXUNUSED(event))
{
	HelpFrame* m_frame = new HelpFrame();
	m_frame->Show(true);
}

/**
 * enables/disalbes the undo button
 * @param[in]       enabled         status
 */
void MainFrame::setUndoEnabled(bool enabled)
{
	ToolBar1->EnableTool(btn_undo, enabled);
}

/**
 * enables/disalbes the redo button
 * @param[in]       enabled         status
 */
void MainFrame::setRedoEnabled(bool enabled)
{
	ToolBar1->EnableTool(btn_redo, enabled);
}

/**
 * fetches the zoom-in button/menu klick
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnZoomIn(wxCommandEvent& WXUNUSED(event))
{
	simulateMouseWheel(-10);
}

/**
 * fetches the zoom-out button/menu klick
 * @param[in]       WXUNUSED        unused event of button/menu
 */
void MainFrame::OnZoomOut(wxCommandEvent& WXUNUSED(event))
{
	simulateMouseWheel(10);
}

/**
 * simulates a mouse-wheel-rotation in order to use normal zoom-event
 * @param[in]       direction           direction to turn the mouse-wheel
 */
void MainFrame::simulateMouseWheel(int direction)
{
	wxMouseEvent event(wxEVT_MOUSEWHEEL);
	GLNotifyEvent myevent(wxEVT_COMMAND_GL_NOTIFY);
	event.m_wheelRotation = direction*120;
	myevent.setMouseEvent(event);
	myevent.setCanvasID(CANVAS2D);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
}

/**
 * returns pointer to the statusbar
 * @return      wxStatusbar*        Pointer to statusbar
 */
wxStatusBar* MainFrame::getStatusbar()
{
	return  StatusBar;
}

#if defined(__ATHOS_DEBUG__)
void MainFrame::OnMenuItemDebug1(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DEBUG1);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void MainFrame::OnMenuItemDebug2(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DEBUG2);
	GetEventHandler()->ProcessEvent(gnrevent);
}

void MainFrame::OnMenuItemDebug3(wxCommandEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(DEBUG3);
	GetEventHandler()->ProcessEvent(gnrevent);
}
#endif
