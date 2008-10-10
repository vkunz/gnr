/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanel
 * @name        GNRTreePanel.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRTREEPANEL_H
#define GNRTREEPANEL_H

//(*Headers(GNRTreePanel)
#include <wx/panel.h>
class wxTreeCtrl;
class wxTreeEvent;
//*)

class GNRTreePanel: public wxPanel
{
public:

	GNRTreePanel(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanel();
	
	//(*Declarations(GNRTreePanel)
	wxTreeCtrl* TreeCtrl1;
	//*)
	
protected:

	//(*Identifiers(GNRTreePanel)
	static const long ID_TREECTRL1;
	//*)
	
private:

	//(*Handlers(GNRTreePanel)
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
