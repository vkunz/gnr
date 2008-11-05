#include "GNRTreeSceneCtrl.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

BEGIN_EVENT_TABLE(GNRTreeSceneCtrl, wxTreeCtrl)
	EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, GNRTreeSceneCtrl::OnItemRClick)
END_EVENT_TABLE()


GNRTreeSceneCtrl::GNRTreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
                                   const wxValidator &validator, const wxString &name) : wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
	//ctor
}

GNRTreeSceneCtrl::~GNRTreeSceneCtrl()
{
	//dtor
}

void GNRTreeSceneCtrl::OnItemRClick(wxTreeEvent& event)
{

}
