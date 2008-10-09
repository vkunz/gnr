#include "include/GNRModelsPanel.h"

//(*InternalHeaders(GNRModelsPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GNRModelsPanel)
//*)

BEGIN_EVENT_TABLE(GNRModelsPanel,wxPanel)
	//(*EventTable(GNRModelsPanel)
	//*)
END_EVENT_TABLE()

GNRModelsPanel::GNRModelsPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(GNRModelsPanel)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	//*)
}

GNRModelsPanel::~GNRModelsPanel()
{
	//(*Destroy(GNRModelsPanel)
	//*)
}

