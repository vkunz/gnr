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
	void OnResize(wxMouseEvent& event);
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);
	void OnExport(wxCommandEvent& event);
	void OnLoad(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnScrolledWindow1Paint(wxPaintEvent& event);
	void OnCameraReset(wxCommandEvent& event);
	//*)
	
	//ToolBar Button Events
	void OnToolbarMoveXY(wxCommandEvent& event);
	void OnToolbarMoveXZ(wxCommandEvent& event);
	void OnToolbarRotateXY(wxCommandEvent& event);
	void OnToolbarRotateXZ(wxCommandEvent& event);
	void OnSnapToGrid();
	void OnSnapToGridBtn(wxCommandEvent& event);
	void OnSnapToGridCtrl(wxSpinEvent& event);
	
	//(*Identifiers(GNRMainFrame)
	static const long idMenuNew;
	static const long idMenuLoad;
	static const long idMenuSave;
	static const long idMenuOAXImport;
	static const long idMenuOAXExport;
	static const long idMenuImport;
	static const long idMenuExport;
	static const long idMenuQuit;
	static const long idMenuSnapToGrid;
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
	
	static const long ID_ToolBar;
	
	static const long ID_SPINCTRL_TRANS;
	static const long ID_SPINCTRL_ROTATE;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	
	//(*Declarations(GNRMainFrame)
	wxMenu* Menu3;
	wxMenuItem* MenuItem11;
	wxMenuItem* MenuItem10;
	wxStatusBar* StatusBar1;
	wxMenuItem* MenuItem9;
	//*)
	
	wxSpinCtrl* SpinCtrlTranslate;
	wxSpinCtrl* SpinCtrlRotate;
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	
	wxToolBar* ToolBar1;
	
	wxToolBarToolBase* ToolBarItem1;
	wxToolBarToolBase* ToolBarItem2;
	wxToolBarToolBase* ToolBarItem3;
	wxToolBarToolBase* ToolBarItem4;
	wxToolBarToolBase* ToolBarItem5;
	wxToolBarToolBase* ToolBarItem6;
	wxToolBarToolBase* ToolBarItem7;
	wxToolBarToolBase* ToolBarItem8;
	wxToolBarToolBase* ToolBarItem9;
	wxToolBarToolBase* ToolBarItem10;
	wxToolBarToolBase* ToolBarItem11;
	wxToolBarToolBase* ToolBarItem12;
	wxToolBarToolBase* ToolBarItem13;
	wxToolBarToolBase* ToolBarItem14;
	wxToolBarToolBase* ToolBarItem15;
	wxToolBarToolBase* ToolBarItem16;
	wxToolBarToolBase* ToolBarItem17;
	wxToolBarToolBase* ToolBarItem18;
	wxToolBarToolBase* ToolBarItem19;
	wxToolBarToolBase* ToolBarItem99;
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMainFrame_H
