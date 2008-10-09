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
