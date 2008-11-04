/**
 * GNRTreePanelMyScene
 * @name        GNRTreePanelMyScene.h
 * @date        2008-11-03
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRTreePanelMyScene_H
#define GNRTreePanelMyScene_H

#include <wx/panel.h>

class GNRTreePanelMyScene: public wxPanel
{
public:

	GNRTreePanelMyScene(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanelMyScene();
	
protected:

private:

	void OnResize(wxSizeEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif
