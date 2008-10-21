/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanel
 * @name        GNRTreePanel.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRTREEPANEL_H
#define GNRTREEPANEL_H

#include <wx/treectrl.h>
#include <wx/panel.h>

class GNRTreePanel: public wxPanel
{
public:

	GNRTreePanel(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanel();
	
	wxTreeCtrl* TreeCtrl;
	
protected:

	static const long ID_TREECTRL;
	
private:

	void OnPaint(wxPaintEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif
