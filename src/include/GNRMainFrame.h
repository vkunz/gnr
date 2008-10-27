/* vim: set expandtab sw=4 ts=4 sts=4: */
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
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>

#include "GNRGLCanvas2D.h"
#include "GNRGLCanvas3D.h"
#include "GNRTreePanelLibrary.h"
#include "GNRTreePanelMyScene.h"
#include "GNRAssembly.h"
#include "GNREnum.h"

class GNRMainFrame: public wxFrame
{
public:

	GNRMainFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRMainFrame();
	
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
	void OnToolbarMoveXZ(wxCommandEvent& event);
	void OnToolbarMoveXY(wxCommandEvent& event);
	void OnToolbarRotateXZ(wxCommandEvent& event);
	void OnToolbarRotateXY(wxCommandEvent& event);
	void OnCameraReset(wxCommandEvent& event);
	void OnSnapToGridBtn(wxCommandEvent& event);
	void OnSnapToGridCtrl(wxSpinEvent& event);
	void OnSnapToGridMenu(wxCommandEvent& event);
	//global set snap to grid
	void OnSnapToGrid();
	
	//(*Identifiers(GNRMainFrame)
	static const long idMenuNewRoom;
	static const long idMenuOpxOpen;
	static const long idMenuOpxSave;
	static const long idMenuOaxImport;
	static const long idMenuOaxExport;
	static const long idMenuObjImport;
	static const long idMenuObjExport;
	static const long idMenuQuit;
	static const long idMenuSnapToGrid;
	static const long idMenuMoveXZ;
	static const long idMenuMoveXY;
	static const long idMenuRotateXZ;
	static const long idMenuRotateXY;
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
	static const long btn_camera_reset;
	static const long btn_snap_to_grid;
	static const long btn_draw_walls;
	
	static const long ID_ToolBar;
	
	static const long ID_SPINCTRL_TRANS;
	static const long ID_SPINCTRL_ROTATE;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	
	//(*Declarations(GNRMainFrame)
	wxMenuBar* MenuBar1;
	wxMenu* Menu1;
	wxMenu* Menu2;
	wxMenu* Menu3;
	wxMenuItem* MenuItem1;
	wxMenuItem* MenuItem2;
	wxMenuItem* MenuItem3;
	wxMenuItem* MenuItem4;
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem6;
	wxMenuItem* MenuItem7;
	wxMenuItem* MenuItem8;
	wxMenuItem* MenuItem9;
	wxMenuItem* MenuItem10;
	wxMenuItem* MenuItem11;
	wxMenuItem* MenuItem12;
	wxMenuItem* MenuItem13;
	wxMenuItem* MenuItem14;
	wxMenuItem* MenuItem15;
	wxStatusBar* StatusBar1;
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
