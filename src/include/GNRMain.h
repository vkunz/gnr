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

#include "TestCanvas.h"
#include "GNRTreePanel.h"

class GNRFrame: public wxFrame
{
public:

	GNRFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRFrame();
	
private:
	TestCanvas* m_BottomCanvas;
	TestCanvas* m_UpperCanvas;
	GNRTreePanel* m_Panel;
	wxSplitterWindow* m_HorizontalSplitter;
	wxSplitterWindow* m_VerticalSplitter;
	
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
	//*)
	
	//(*Declarations(GNRFrame)
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem3;
	wxStatusBar* StatusBar1;
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMAIN_H
