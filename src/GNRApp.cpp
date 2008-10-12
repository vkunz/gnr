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
#include "GNRController.h"

#if defined(__ATHOS_DEBUG__)
#include "GNRDebugFrame.h"
#endif

IMPLEMENT_APP(GNRApp);

bool GNRApp::OnInit()
{
	// AppInitialize
	bool wxsOK = true;
	
	wxInitAllImageHandlers();
	
	if (wxsOK)
	{
#if defined(__ATHOS_DEBUG__)
		// Create DebugFrame
		m_DebugFrame = new GNRDebugFrame(0);
		m_DebugFrame->Show(true);
		
		// Create a new Log
		m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
		
		// Set actuals Log
		m_Log->SetActiveTarget(m_Log);
#endif
		GNRController* controller = new GNRController;
	}
	//
	return wxsOK;
	
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
