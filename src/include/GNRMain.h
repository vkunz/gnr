/***************************************************************
 * Name:      GNRMain.h
 * Purpose:   Defines Application Frame
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#ifndef GNRMAIN_H
#define GNRMAIN_H

#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
#include <wx/splitter.h>
#include <wx/glcanvas.h>
#include <wx/toolbar.h>

#include "TestCanvas.h"
#include "GNRGL2DCanvas.h"
#include "GNRGL3DCanvas.h"
#include "GNRTreePanel.h"
#include "GNRModelsPanel.h"

class GNRFrame: public wxFrame
{
public:

	GNRFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRFrame();
	
private:
	GNRGL2DCanvas* m_UpperCanvas;
	GNRGL3DCanvas* m_BottomCanvas;
	GNRTreePanel* m_TreePanel;
	GNRModelsPanel* m_ModelsPanel;
	wxSplitterWindow* m_HorizontalSplitter_left;
	wxSplitterWindow* m_HorizontalSplitter_right;
	wxSplitterWindow* m_VerticalSplitter;
	wxGLContext* m_glContext;
	
	//(*Handlers(GNRFrame)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	
#if defined(__WXDEBUG__)
	void OnLoad(wxCommandEvent& event);
#endif
	void OnScrolledWindow1Paint(wxPaintEvent& event);
	//*)
	
	//(*Identifiers(GNRFrame)
	static const long idMenuLoad;
	static const long idMenuSave;
	static const long idMenuQuit;
	static const long idMenuHelp;
	static const long idMenuAbout;
	static const long ID_StatusBar;
	static const long btn_room_new;
	static const long btn_room_open;
	static const long btn_room_save;
	static const long btn_undo;
	static const long btn_redo;
	static const long btn_move_xy;
	static const long btn_move_xz;
	static const long btn_rotate_xy;
	static const long ID_TOOLBAR1;
	//*)
	
	//(*Declarations(GNRFrame)
	wxToolBarToolBase* ToolBarItem4;
	wxToolBar* ToolBar1;
	wxToolBarToolBase* ToolBarItem3;
	wxMenuItem* MenuItem5;
	wxToolBarToolBase* ToolBarItem6;
	wxToolBarToolBase* ToolBarItem1;
	wxMenuItem* MenuItem3;
	wxStatusBar* StatusBar1;
	wxToolBarToolBase* ToolBarItem5;
	wxToolBarToolBase* ToolBarItem8;
	wxToolBarToolBase* ToolBarItem2;
	wxToolBarToolBase* ToolBarItem7;
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMAIN_H
