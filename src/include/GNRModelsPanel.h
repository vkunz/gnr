#ifndef GNRMODELSPANEL_H
#define GNRMODELSPANEL_H

//(*Headers(GNRModelsPanel)
#include <wx/panel.h>
#include <wx/grid.h>
//*)

class GNRModelsPanel: public wxPanel
{
public:

	GNRModelsPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
	virtual ~GNRModelsPanel();
	
	//(*Declarations(GNRModelsPanel)
	wxGrid* Grid1;
	//*)
	
protected:

	//(*Identifiers(GNRModelsPanel)
	static const long ID_GRID1;
	//*)
	
private:

	//(*Handlers(GNRModelsPanel)
	void OnGrid1CellLeftClick(wxGridEvent& event);
	//*)
	
	DECLARE_EVENT_TABLE()
};

#endif
