/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * main application is creating the main controller starting the program
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
	EVT_GNR_NOTIFY(0, GNRApp::OnGNREvent)
	EVT_GL_NOTIFY(0, GNRApp::OnGLEvent)
END_EVENT_TABLE()

void GNRApp::OnGNREvent(GNRNotifyEvent& event)
{
	// controller not yet initialized
	if (m_controllerInit == false)
		return;
		
	if (event.getGNREventType() == GLRefresh2D)
	{
#if defined(__ATHOS_DEBUG__)
		wxLogMessage(_("GNRApp::OnGNREvent-GLRefresh"));
#endif
		controller->glRefresh2D();
	}
	else if (event.getGNREventType() == GLRefresh3D)
	{
		controller->glRefresh3D();
	}
}

void GNRApp::OnGLEvent(GNRGLNotifyEvent& event)
{
#if defined(__ATHOS_DEBUG__)
	wxLogMessage(_("GNRApp::OnGLEvent"));
#endif
	//controller->glRefresh(); //may be highlight (assemblypointer) ??? TODO
}

IMPLEMENT_APP(GNRApp);

bool GNRApp::OnInit()
{
	bool wxsOK = true;
	
	wxInitAllImageHandlers();
	
	if (wxsOK)
	{
		m_controllerInit = false;
		controller = new GNRController();
		m_controllerInit = true;
	}
	
	return wxsOK;
}

int GNRApp::OnExit()
{

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
