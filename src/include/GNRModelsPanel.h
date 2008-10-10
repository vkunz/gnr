/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRModelsPanel
 * @name        GNRModelsPanel.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRMODELSPANEL_H
#define GNRMODELSPANEL_H

//(*Headers(GNRModelsPanel)
#include <wx/panel.h>
//*)

class GNRModelsPanel: public wxPanel
{
public:

	GNRModelsPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
	virtual ~GNRModelsPanel();
	
	//(*Declarations(GNRModelsPanel)
	//*)
	
protected:

	//(*Identifiers(GNRModelsPanel)
	//*)
	
private:

	//(*Handlers(GNRModelsPanel)
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
