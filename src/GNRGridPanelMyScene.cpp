/**
 * GNRGridPanelMyScene
 * @name        GNRGridPanelMyScene.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNREnum.h"
#include "GNRNotifyEvent.h"
#include "GNRGridPanelMyScene.h"

BEGIN_EVENT_TABLE(GNRGridPanelMyScene,wxPanel)
END_EVENT_TABLE()

GNRGridPanelMyScene::GNRGridPanelMyScene(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("GNRGridPanelMyScene"));
	
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRGridPanelMyScene::OnResize);
}

GNRGridPanelMyScene::~GNRGridPanelMyScene()
{
}

void GNRGridPanelMyScene::OnResize(wxSizeEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(PANELSIZE);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
