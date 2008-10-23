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
#include <wx/statusbr.h>
#include <wx/toolbar.h>

#include "GNRGL2DCanvas.h"
#include "GNRGL3DCanvas.h"
#include "GNRTreePanelLibrary.h"
#include "GNRTreePanelMyScene.h"
#include "GNRAssembly.h"

class GNRMainFrame: public wxFrame
{
public:
	enum { MOVEXZ = 0, MOVEXY, ROTATEXY, ROTATEXZ };
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
	//*)
	//ToolBar Button Events
	void OnToolbarMoveXY(wxCommandEvent& event);
	void OnToolbarMoveXZ(wxCommandEvent& event);
	void OnToolbarRotateXY(wxCommandEvent& event);
	void OnToolbarRotateXZ(wxCommandEvent& event);
	
	//(*Identifiers(GNRMainFrame)
	static const long idMenuNew;
	static const long idMenuLoad;
	static const long idMenuSave;
	static const long idMenuImport;
	static const long idMenuExport;
	static const long idMenuQuit;
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
	static const long ID_ToolBar;
	
	//(*Declarations(GNRMainFrame)
	wxStatusBar* StatusBar1;
	//*)
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
	wxToolBarToolBase* ToolBarItem99;
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMainFrame_H
