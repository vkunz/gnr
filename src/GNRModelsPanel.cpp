#include "include/GNRModelsPanel.h"

//(*InternalHeaders(GNRModelsPanel)
#include <wx/grid.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GNRModelsPanel)
const long GNRModelsPanel::ID_GRID1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRModelsPanel,wxPanel)
	//(*EventTable(GNRModelsPanel)
	//*)
END_EVENT_TABLE()

GNRModelsPanel::GNRModelsPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(GNRModelsPanel)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	//Grid1 = new wxGrid(parent, id, wxPoint(0,0), wxDefaultSize, 0, _T("ID_GRID1"));
	//*)
}

GNRModelsPanel::~GNRModelsPanel()
{
	//(*Destroy(GNRModelsPanel)
	//*)
}

