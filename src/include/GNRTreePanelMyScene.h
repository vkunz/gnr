/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanelMyScene
 * @name        GNRTreePanelMyScene.h
 * @date        2008-10-21
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRTREEPANELMYSCENE_H
#define GNRTREEPANELMYSCENE_H

#include "GNRTreePanel.h"
#include <wx/panel.h>

class wxTreeCtrl;
class wxTreeEvent;

class GNRTreePanelMyScene: public GNRTreePanel
{
public:

	GNRTreePanelMyScene(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanelMyScene();
	
	wxTreeCtrl* TreeCtrl;
	
protected:

	static const long ID_TREECTRL;
	
private:

	DECLARE_EVENT_TABLE()
};

#endif
