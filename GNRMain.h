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

class GNRFrame: public wxFrame
{
public:

	GNRFrame(wxWindow* parent,wxWindowID id = -1);
	virtual ~GNRFrame();
	
private:

	//(*Handlers(GNRFrame)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	//*)
	
	//(*Identifiers(GNRFrame)
	static const long idMenuQuit;
	static const long idMenuAbout;
	static const long ID_STATUSBAR1;
	//*)
	
	//(*Declarations(GNRFrame)
	wxStatusBar* StatusBar1;
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif // GNRMAIN_H
