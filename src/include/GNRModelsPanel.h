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
