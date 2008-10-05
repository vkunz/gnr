#ifndef GNRTREEPANEL_H
#define GNRTREEPANEL_H

//(*Headers(GNRTreePanel)
#include <wx/panel.h>
//*)

class GNRTreePanel: public wxPanel
{
public:

	GNRTreePanel(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanel();
	
	//(*Declarations(GNRTreePanel)
	//*)
	
protected:

	//(*Identifiers(GNRTreePanel)
	//*)
	
private:

	//(*Handlers(GNRTreePanel)
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
