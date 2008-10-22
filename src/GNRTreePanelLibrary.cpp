/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanelLibrary
 * @name        GNRTreePanelLibrary.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRTreePanelLibrary.h"

#include <wx/treectrl.h>
#include <wx/intl.h>
#include <wx/string.h>

const long GNRTreePanelLibrary::ID_TREECTRL = wxNewId();

BEGIN_EVENT_TABLE(GNRTreePanelLibrary,wxPanel)
END_EVENT_TABLE()

GNRTreePanelLibrary::GNRTreePanelLibrary(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxDefaultPosition, wxSize(640,480), wxTAB_TRAVERSAL, _T("id"));
	TreeCtrl = new wxTreeCtrl(this, ID_TREECTRL, wxPoint(0,0), wxDefaultSize, wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_TREECTRL1"));
}

GNRTreePanelLibrary::~GNRTreePanelLibrary()
{
}

