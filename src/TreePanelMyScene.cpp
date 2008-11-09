/**
 * TreePanelMyScene
 * @name        TreePanelMyScene.cpp
 * @date        2008-11-03
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Enum.h"
#include "NotifyEvent.h"
#include "TreePanelMyScene.h"

BEGIN_EVENT_TABLE(TreePanelMyScene,wxPanel)
END_EVENT_TABLE()

TreePanelMyScene::TreePanelMyScene(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("TreePanelMyScene"));
	
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&TreePanelMyScene::OnResize);
}

TreePanelMyScene::~TreePanelMyScene()
{
}

void TreePanelMyScene::OnResize(wxSizeEvent& WXUNUSED(event))
{
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(PANELSIZE);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
