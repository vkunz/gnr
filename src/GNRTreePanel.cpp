#include "GNRTreePanel.h"

//(*InternalHeaders(GNRTreePanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GNRTreePanel)
//*)

BEGIN_EVENT_TABLE(GNRTreePanel,wxPanel)
	//(*EventTable(GNRTreePanel)
	//*)
END_EVENT_TABLE()

GNRTreePanel::GNRTreePanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(GNRTreePanel)
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("id"));
	//*)
}

GNRTreePanel::~GNRTreePanel()
{
	//(*Destroy(GNRTreePanel)
	//*)
}

