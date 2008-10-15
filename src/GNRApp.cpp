/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * code for application class
 * @name        GNRApp.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/image.h>

#include "GNRApp.h"

BEGIN_EVENT_TABLE(GNRApp, wxApp)
	//EVT_FONT_SELECTION_CHANGED( 2457, GNRApp::OnDrawEvent )
	EVT_GL_NOTIFY(0, GNRApp::OnGLEvent)
	EVT_CLOSE(GNRApp::OnClose)
END_EVENT_TABLE()

void GNRApp::OnClose(wxCloseEvent &event)
{
	wxLogMessage(_("Close"));
	delete controller;
}

void GNRApp::OnGLEvent(GNRGLNotifyEvent& event)
{
	wxLogMessage(_("Event"));
}


IMPLEMENT_APP(GNRApp);

bool GNRApp::OnInit()
{
	// AppInitialize
	bool wxsOK = true;
	
	wxInitAllImageHandlers();
	
	if (wxsOK)
	{
		//create maincontroller
		controller = new GNRController();
	}
	
	return wxsOK;
}

int GNRApp::OnExit()
{
	//delete controller;
	return 0;
}

// Code unser im Repo,
// bugfrei seien Deine Quellen.
// Dein Commit komme.
// Dein Bild geschehe,
// wie im Repo, so auch lokal.
// Unser taegliches Bild gib uns heute,
// Und vergib uns unsere Fehler,
// wie auch wir vergeben dem Compiler.
// Und fuehre uns nicht in Versuchung,
// sondern erloese uns vom Proprietary.
