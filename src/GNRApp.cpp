/***************************************************************
 * Name:      GNRApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#include "GNRApp.h"

//(*AppHeaders
#include "GNRMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(GNRApp);

bool GNRApp::OnInit()
{
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if (wxsOK)
	{
		GNRFrame* Frame = new GNRFrame(0);
		Frame->Show(TRUE);
		SetTopWindow(Frame);
		Frame->m_canvas->SetCurrent();
		Frame->m_canvas->DrawGLScene();
	}
	//*)
	return wxsOK;
	
}
