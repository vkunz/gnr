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

	//(*Handlers(GNRMainFrame)
	void OnMenuNewRoom(wxCommandEvent& event);
	void OnMenuOaxImport(wxCommandEvent& event);
	void OnMenuOaxExport(wxCommandEvent& event);
	void OnMenuOpxOpen(wxCommandEvent& event);
	void OnMenuOpxSave(wxCommandEvent& event);
	void OnMenuObjImport(wxCommandEvent& event);
	void OnMenuObjExport(wxCommandEvent& event);
	void OnMenuQuit(wxCommandEvent& event);
	void OnMenuAbout(wxCommandEvent& event);
	//*)
	
	//ToolBar Button Events
	void OnToolbarUndo(wxCommandEvent& event);
	void OnToolbarRedo(wxCommandEvent& event);
	void OnToolbarMoveXZ(wxCommandEvent& event);
	void OnToolbarMoveXY(wxCommandEvent& event);
	void OnToolbarRotateXZ(wxCommandEvent& event);
	void OnToolbarRotateXY(wxCommandEvent& event);
	void OnToolbarDrawWall(wxCommandEvent& event);
	void OnCreateScreenshot(wxCommandEvent& event);
	void OnCameraReset(wxCommandEvent& event);
	void OnZoomIn(wxCommandEvent& WXUNUSED(event));
	void OnZoomOut(wxCommandEvent& WXUNUSED(event));
	void OnSnapToGridBtn(wxCommandEvent& event);
	void OnSnapToGridCtrl(wxSpinEvent& event);
	void OnSnapToGridMenu(wxCommandEvent& event);
	void OnGroupCreate(wxCommandEvent& WXUNUSED(event));
	void OnGroupModify(wxCommandEvent& WXUNUSED(event));
	void OnDeleteSelected(wxCommandEvent& WXUNUSED(event));
	//global set snap to grid
	void OnSnapToGrid();
	//global wheel simulation
	void simulateMouseWheel(int direction);
	
	//(*Identifiers(GNRMainFrame)
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
	static const long idMenuHideObject;
	static const long idMenuShowObject;
	static const long idMenuObjExport;
	static const long idMenuOaxExport;
	static const long idMenuObjImport;
	static const long idMenuOaxImport;
	static const long idMenuZoomIn;
	static const long idMenuZoomOut;
	static const long idMenuZoomFit;
	static const long idMenuZoomReset;
	static const long idMenuSnapToGrid;
	static const long idMenuMoveXZ;
	static const long idMenuMoveXY;
	static const long idMenuRotateXZ;
	static const long idMenuRotateXY;
	static const long idMenuDrawWall;
	static const long idMenuGroup;
	static const long idMenuUngroup;
	static const long idMenuHelp;
	static const long idMenuAbout;
	static const long ID_StatusBar;
	//*)
	
	//ToolBar Buttons
	static const long btn_room_new;
	static const long btn_room_open;
	static const long btn_room_save;
	static const long btn_room_save_as;
	static const long btn_quit;
	static const long btn_undo;
	static const long btn_redo;
	static const long btn_zoom_in;
	static const long btn_zoom_out;
	static const long btn_zoom_fit;
	static const long btn_move_xy;
	static const long btn_move_xz;
	static const long btn_rotate_xy;
	static const long btn_rotate_xz;
	static const long btn_draw_walls;
	static const long btn_create_screenshot;
	static const long btn_camera_reset;
	static const long btn_snap_to_grid;
	
	static const long ID_ToolBar;
	
	static const long ID_SPINCTRL_TRANS;
	static const long ID_SPINCTRL_ROTATE;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	
	//(*Declarations(GNRMainFrame)
	wxMenuItem* MenuItem26;
	wxMenuItem* MenuItem25;
	wxMenu* Menu3;
	wxMenuItem* MenuItem14;
	wxMenuItem* MenuItem11;
	wxMenuItem* MenuItem29;
	wxMenuItem* MenuItem15;
	wxMenuItem* MenuItem22;
	wxMenuItem* MenuItem17;
	wxMenuItem* MenuItem13;
	wxMenuItem* MenuItem10;
	wxMenuItem* MenuItem12;
	wxMenuItem* MenuItem24;
	wxMenuItem* MenuItem27;
	wxMenuItem* MenuItem20;
	wxMenuItem* MenuItem28;
	wxMenu* Menu7;
	wxStatusBar* StatusBar1;
	wxMenuItem* MenuItem23;
	wxMenuItem* MenuItem21;
	wxMenuItem* MenuItem16;
	wxMenu* Menu8;
	wxMenu* Menu6;
	wxMenuItem* MenuItem9;
	wxMenuItem* MenuItem18;
	wxMenuItem* MenuItem30;
	wxMenu* Menu5;
	wxMenu* Menu4;
	wxMenuItem* MenuItem19;
	//*)
	
	wxSpinCtrl* SpinCtrlTranslate;
	wxSpinCtrl* SpinCtrlRotate;
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	
	wxToolBar* ToolBar1;
	wxToolBarToolBase* ToolBarItem[30];
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMainFrame_H
