/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanel
 * @name        GNRTreePanel.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("id"));
	TreeCtrl1 = new wxTreeCtrl(this, ID_TREECTRL1, wxPoint(0,0), wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
	//*)
}

GNRTreePanel::~GNRTreePanel()
{
	//(*Destroy(GNRTreePanel)
	//*)
}

