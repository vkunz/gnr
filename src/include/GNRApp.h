/***************************************************************
 * Name:      GNRApp.h
 * Purpose:   Defines Application Class
 * Author:    Patrick Kracht (patrick.kracht@googlemail.com)
 * Created:   2008-09-30
 * Copyright: Patrick Kracht (http://www.omega2k.de)
 * License:
 **************************************************************/

#ifndef GNRAPP_H
#define GNRAPP_H

#include <wx/app.h>

#if defined(__WXDEBUG__)
#include <wx/log.h>

#include "GNRDebugFrame.h"
#endif

class GNRApp : public wxApp
{
public:
	virtual bool OnInit();
	
#if defined(__WXDEBUG__)
	GNRDebugFrame* m_DebugFrame;
	wxLog* m_Log;
#endif
	
};

#endif // GNRAPP_H
