/**
 * GNRMainFrame
 * @name        GNRMainFrame.h
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRMainFrame_H
#define GNRMainFrame_H

#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>

class GNRMainFrame: public wxFrame
{
public:

	GNRMainFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRMainFrame();
	void setUndoEnabled(bool enabled);
	void setRedoEnabled(bool enabled);
	
	wxStatusBar* getStatusbar();
	
private:

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
	void OnShowHidden(wxCommandEvent& WXUNUSED(event));
	void OnInsertCopy(wxCommandEvent& WXUNUSED(event));
	void OnCutSelected(wxCommandEvent& WXUNUSED(event));
	
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
	static const long idMenuShowObject;
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
	
	wxMenuBar* MenuBar;
	
	wxMenuItem* MenuItem31;
	wxMenuItem* MenuItem26;
	wxMenuItem* MenuItem25;
	wxMenuItem* MenuItem14;
	wxMenuItem* MenuItem11;
	wxMenuItem* MenuItem29;
	wxMenuItem* MenuItem15;
	wxMenuItem* MenuItem22;
	wxMenuItem* MenuItem32;
	wxMenuItem* MenuItem17;
	wxMenuItem* MenuItem13;
	wxMenuItem* MenuItem10;
	wxMenuItem* MenuItem12;
	wxMenuItem* MenuItem24;
	wxMenuItem* MenuItem27;
	wxMenuItem* MenuItem20;
	wxMenuItem* MenuItem28;
	wxMenuItem* MenuItem23;
	wxMenuItem* MenuItem21;
	wxMenuItem* MenuItem16;
	wxMenuItem* MenuItem18;
	wxMenuItem* MenuItem30;
	wxMenuItem* MenuItem19;
	wxMenuItem* MenuItem33;
	wxMenuItem* MenuItem1;
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem3;
	wxMenuItem* MenuItem4;
	wxMenuItem* MenuItem6;
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem7;
	wxMenuItem* MenuItem8;
	wxMenuItem* MenuItem9;
	
	wxStatusBar* StatusBar;
	
	wxSpinCtrl* SpinCtrlTranslate;
	wxSpinCtrl* SpinCtrlRotate;
	
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	
	wxToolBar* ToolBar1;
	wxToolBarToolBase* ToolBarItem[30];
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMainFrame_H
