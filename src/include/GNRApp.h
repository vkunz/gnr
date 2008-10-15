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
#include "GNRController.h"

class GNRApp : public wxApp
{
private:
	GNRController* controller;
	
public:
	virtual bool OnInit();
};

#endif // GNRAPP_H
