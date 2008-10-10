/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRModelsPanel
 * @name        GNRModelsPanel.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRModelsPanel.h"

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

