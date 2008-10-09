#include "GNRTreePanel.h"

//(*InternalHeaders(GNRTreePanel)
#include <wx/treectrl.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(GNRTreePanel)
const long GNRTreePanel::ID_TREECTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRTreePanel,wxPanel)
	//(*EventTable(GNRTreePanel)
	//*)
END_EVENT_TABLE()

GNRTreePanel::GNRTreePanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(GNRTreePanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	//TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL1, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	//*)
}

GNRTreePanel::~GNRTreePanel()
{
	//(*Destroy(GNRTreePanel)
	//*)
}

