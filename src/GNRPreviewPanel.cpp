/**
 * GNRPreviewPanel
 * @name        GNRPreviewPanel.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRPreviewPanel.h"

// ctor
GNRPreviewPanel::GNRPreviewPanel(wxWindow* parent, wxWindowID id)
{
	Create(parent, id, wxPoint(50,50), wxSize(200,200), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, wxT("PreviewPanel"));
}

// dtor
GNRPreviewPanel::~GNRPreviewPanel()
{
	// do nothing
}
