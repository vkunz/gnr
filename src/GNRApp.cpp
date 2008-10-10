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
#include "GNRMain.h"
#include "TestCanvas.h"

#if defined(__WXDEBUG__)
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
#if defined(__WXDEBUG__)
		// Create DebugFrame
		m_DebugFrame = new GNRDebugFrame(0);
		m_DebugFrame->Show(true);
		
		// Create a new Log
		m_Log = new wxLogTextCtrl(m_DebugFrame->TextCtrl);
		
		// Set actuals Log
		m_Log->SetActiveTarget(m_Log);
#endif
		
		//create new GNRFrame
		GNRFrame* Frame = new GNRFrame(0);
		
		SetTopWindow(Frame);
	}
	//
	return wxsOK;
	
}
