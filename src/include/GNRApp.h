/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRApp
 * @name        GNRApp.cpp
 * @date        2008-09-30
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRAPP_H
#define GNRAPP_H

#include <wx/app.h>
#include "GNRController.h"
#include "GNRNotifyEvent.h"
#include "GNRGLNotifyEvent.h"

class GNRApp : public wxApp
{
private:
	GNRController* controller;
	bool m_controllerInit;
	
	void OnGNREvent(GNRNotifyEvent& event);
	void OnGLEvent(GNRGLNotifyEvent& event);
	
	DECLARE_EVENT_TABLE();
public:
	virtual bool OnInit();
};

#endif // GNRAPP_H
