/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanelMyScene
 * @name        GNRTreePanelMyScene.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRNotifyEvent.h"
#include "GNRTreePanelMyScene.h"

#include <wx/treectrl.h>
#include <wx/intl.h>
#include <wx/string.h>

const long GNRTreePanelMyScene::ID_TREECTRL = wxNewId();

BEGIN_EVENT_TABLE(GNRTreePanelMyScene,wxPanel)
END_EVENT_TABLE()

GNRTreePanelMyScene::GNRTreePanelMyScene(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("GNRTreePanelMyScene"));
	
	Connect(wxEVT_SIZE, (wxObjectEventFunction)&GNRTreePanelMyScene::OnResize);
}

GNRTreePanelMyScene::~GNRTreePanelMyScene()
{
}

void GNRTreePanelMyScene::OnResize(wxSizeEvent& WXUNUSED(event))
{
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(PANELSIZE);
	
	GetEventHandler()->ProcessEvent(gnrevent);
}
