/**
 * MainFrame
 * @name        MainFrame.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef MainFrame_H
#define MainFrame_H

#include <map>

#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>

using std::map;

class MainFrame: public wxFrame
{
public:

	MainFrame(wxWindow* parent);
	virtual ~MainFrame();
	void setUndoEnabled(bool enabled);
	void setRedoEnabled(bool enabled);
	void setTranslationXZ();
	void setTranslationXY();
	
	wxStatusBar* getStatusbar();
	
private:

#if defined(__ATHOS_DEBUG__)
	static const long idMenuItemDebug1;
	static const long idMenuItemDebug2;
	static const long idMenuItemDebug3;
	
	void OnMenuItemDebug1(wxCommandEvent& WXUNUSED(event));
	void OnMenuItemDebug2(wxCommandEvent& WXUNUSED(event));
	void OnMenuItemDebug3(wxCommandEvent& WXUNUSED(event));
	
	wxMenu* ParentMenu_Debug;
	wxMenuItem* MenuItemDebug1;
	wxMenuItem* MenuItemDebug2;
	wxMenuItem* MenuItemDebug3;
#endif
	void OnPaint(wxPaintEvent& event);
	
	void OnMenuNewRoom(wxCommandEvent& WXUNUSED(event));
	void OnMenuOaxImport(wxCommandEvent& WXUNUSED(event));
	void OnMenuOaxExport(wxCommandEvent& WXUNUSED(event));
	void OnMenuOpxOpen(wxCommandEvent& WXUNUSED(event));
	void OnMenuOpxSave(wxCommandEvent& WXUNUSED(event));
	void OnMenuObjImport(wxCommandEvent& WXUNUSED(event));
	void OnMenuObjExport(wxCommandEvent& WXUNUSED(event));
	void OnMenuQuit(wxCommandEvent& WXUNUSED(event));
	void OnMenuAbout(wxCommandEvent& WXUNUSED(event));
	void OnMenuHelp(wxCommandEvent& WXUNUSED(event));
	
	//ToolBar Button Events
	void OnToolbarUndo(wxCommandEvent& WXUNUSED(event));
	void OnToolbarRedo(wxCommandEvent& WXUNUSED(event));
	void OnToolbarMoveXZ(wxCommandEvent& WXUNUSED(event));
	void OnToolbarMoveXY(wxCommandEvent& WXUNUSED(event));
	void OnToolbarRotateXZ(wxCommandEvent& WXUNUSED(event));
	void OnToolbarRotateXY(wxCommandEvent& WXUNUSED(event));
	void OnToolbarDrawWall(wxCommandEvent& WXUNUSED(event));
	void OnCreateScreenshot(wxCommandEvent& WXUNUSED(event));
	void OnCameraReset(wxCommandEvent& WXUNUSED(event));
	void OnResetObject(wxCommandEvent& WXUNUSED(event));
	void OnZoomIn(wxCommandEvent& WXUNUSED(event));
	void OnZoomOut(wxCommandEvent& WXUNUSED(event));
	void OnSnapToGridBtn(wxCommandEvent& WXUNUSED(event));
	void OnSnapToGridCtrl(wxSpinEvent& WXUNUSED(event));
	void OnSnapToGridMenu(wxCommandEvent& WXUNUSED(event));
	void OnShadowsMenu(wxCommandEvent& WXUNUSED(event));
	void OnGroupCreate(wxCommandEvent& WXUNUSED(event));
	void OnGroupModify(wxCommandEvent& WXUNUSED(event));
	void OnDeleteSelected(wxCommandEvent& WXUNUSED(event));
	void OnCloneSelected(wxCommandEvent& WXUNUSED(event));
	void OnCopySelected(wxCommandEvent& WXUNUSED(event));
	void OnHideSelected(wxCommandEvent& WXUNUSED(event));
	void OnInsertCopy(wxCommandEvent& WXUNUSED(event));
	void OnCutSelected(wxCommandEvent& WXUNUSED(event));
	void OnMenuCreateCone(wxCommandEvent& WXUNUSED(event));
	void OnMenuCreateSphere(wxCommandEvent& WXUNUSED(event));
	void OnMenuCreateCuboid(wxCommandEvent& WXUNUSED(event));
	void OnMenuCreateCylinder(wxCommandEvent& WXUNUSED(event));
	void OnMenuCreatePyramide(wxCommandEvent& WXUNUSED(event));
	
	//global set snap to grid
	void OnSnapToGrid();
	
	//global wheel simulation
	void simulateMouseWheel(int direction);
	
	static const long idMenuNewRoom;
	static const long idMenuOpxOpen;
	static const long idMenuOpxSave;
	static const long idMenuQuit;
	static const long idMenuUndo;
	static const long idMenuRedo;
	static const long idMenuDeleteObject;
	static const long idMenuCutObject;
	static const long idMenuInsertObject;
	static const long idMenuCopyObject;
	static const long idMenuCloneObject;
	static const long idMenuHideObject;
	static const long idMenuObjExport;
	static const long idMenuOaxExport;
	static const long idMenuOnScreenshot;
	static const long idMenuObjImport;
	static const long idMenuOaxImport;
	static const long idMenuZoomIn;
	static const long idMenuZoomOut;
	static const long idMenuCameraReset;
	static const long idMenuSnapToGrid;
	static const long idMenuMoveXZ;
	static const long idMenuMoveXY;
	static const long idMenuRotateXZ;
	static const long idMenuRotateXY;
	static const long idMenuDrawWall;
	static const long idMenuShadows;
	static const long idMenuGroup;
	static const long idMenuUngroup;
	static const long idMenuHelp;
	static const long idMenuAbout;
	static const long idMenuCreateCuboid;
	static const long idMenuCreateSphere;
	static const long idMenuCreatePyramide;
	static const long idMenuCreateCone;
	static const long idMenuCreateCylinder;
	static const long idMenuResetObject;
	//ToolBar Buttons
	static const long btn_room_new;
	static const long btn_room_open;
	static const long btn_room_save;
	static const long btn_quit;
	static const long btn_undo;
	static const long btn_redo;
	static const long btn_zoom_in;
	static const long btn_zoom_out;
	static const long btn_move_xy;
	static const long btn_move_xz;
	static const long btn_rotate_xy;
	static const long btn_rotate_xz;
	static const long btn_draw_walls;
	static const long btn_reset_object;
	static const long btn_create_screenshot;
	static const long btn_camera_reset;
	static const long btn_snap_to_grid;
	static const long ID_TOOLBAR;
	static const long ID_SPINCTRL_TRANS;
	static const long ID_SPINCTRL_ROTATE;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	static const long ID_STATUSBAR;
	
	wxMenu* ParentMenu_File;
	wxMenu* ParentMenu_Help;
	wxMenu* ParentMenu_Settings;
	wxMenu* ParentMenu_Edit;
	wxMenu* ParentMenu_Export;
	wxMenu* ParentMenu_Import;
	wxMenu* ParentMenu_Groups;
	wxMenu* ParentMenu_Camera;
	wxMenu* ParentMenu_Create;
	
	wxToolBar*   ToolBar1;
	wxMenuBar*   MenuBar;
	wxStatusBar* StatusBar;
	
	wxSpinCtrl* SpinCtrlTranslate;
	wxSpinCtrl* SpinCtrlRotate;
	
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	
	
	map<long, wxToolBarToolBase*> m_ToolBarItem;
	map<long, wxMenuItem*> m_MenuItem;
	
	DECLARE_EVENT_TABLE()
};

#endif // MainFrame_H
