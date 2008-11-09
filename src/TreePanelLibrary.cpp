/**
 * TreePanelLibrary
 * @name        TreePanelLibrary.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Enum.h"
#include "NotifyEvent.h"
#include "TreePanelLibrary.h"

BEGIN_EVENT_TABLE(TreePanelLibrary,wxPanel)
END_EVENT_TABLE()

/**
 * constructor
 * @param[in]       	parent		     wxWindow* parent pointer
 * @param[in]       	id  		     wxWindowID id of window
 */
TreePanelLibrary::TreePanelLibrary(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("TreePanelLibrary"));
	
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&TreePanelLibrary::OnResize);
}

/**
 * destructor
 */
TreePanelLibrary::~TreePanelLibrary()
{
}

/**
 * on resize redraw panelsize
 * @param[in]       event
 */
void TreePanelLibrary::OnResize(wxSizeEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(PANELSIZE);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
