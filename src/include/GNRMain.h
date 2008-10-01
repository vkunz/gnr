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

//(*Headers(GNRFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)




#include "TestCanvas.h"

class GNRFrame: public wxFrame
{
public:

	GNRFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRFrame();
	
	//void SetCanvas( TestGLCanvas *canvas ) { m_canvas = canvas; }
	//TestGLCanvas* GetCanvas() { return m_canvas; }
	
	
private:

	TestCanvas* m_canvas;
	
	//(*Handlers(GNRFrame)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	//*)
	
	//(*Identifiers(GNRFrame)
	static const long idMenuLoad;
	static const long idMenuSave;
	static const long idMenuQuit;
	static const long idMenuHelp;
	static const long idMenuAbout;
	static const long ID_STATUSBAR1;
	//*)
	
	//(*Declarations(GNRFrame)
	wxMenuItem* MenuItem5;
	wxMenuItem* MenuItem3;
	wxStatusBar* StatusBar1;
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMAIN_H
