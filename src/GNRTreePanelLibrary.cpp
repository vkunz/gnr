/**
 * GNRTreePanelLibrary
 * @name        GNRTreePanelLibrary.cpp
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNREnum.h"
#include "GNRNotifyEvent.h"
#include "GNRTreePanelLibrary.h"

BEGIN_EVENT_TABLE(GNRTreePanelLibrary,wxPanel)
END_EVENT_TABLE()

GNRTreePanelLibrary::GNRTreePanelLibrary(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("TreePanelLibrary"));
	
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRTreePanelLibrary::OnResize);
}

GNRTreePanelLibrary::~GNRTreePanelLibrary()
{
}

void GNRTreePanelLibrary::OnResize(wxSizeEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(PANELSIZE);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
