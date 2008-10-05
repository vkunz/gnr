/***************************************************************
 * Name:      GNRApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#include <wx/image.h>

#include "GNRApp.h"
#include "GNRMain.h"
#include "TestCanvas.h"

IMPLEMENT_APP(GNRApp);

bool GNRApp::OnInit()
{
	// AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if (wxsOK)
	{
		//create new GNRFrame
		GNRFrame* Frame = new GNRFrame(0);
		
		//show frame
		Frame->Show(TRUE);
		SetTopWindow(Frame);
	}
	//
	return wxsOK;
	
}
