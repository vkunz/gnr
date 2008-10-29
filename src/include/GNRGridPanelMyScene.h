/**
 * GNRGridPanelMyScene
 * @name        GNRGridPanelMyScene.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRGridPanelMyScene_H
#define GNRGridPanelMyScene_H

#include <wx/panel.h>

class GNRGridPanelMyScene: public wxPanel
{
public:

	GNRGridPanelMyScene(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRGridPanelMyScene();
	
protected:

private:

	void OnResize(wxSizeEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif
