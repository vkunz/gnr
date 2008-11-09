/**
 * TreePanelMyScene
 * @name        TreePanelMyScene.h
 * @date        2008-11-03
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef TreePanelMyScene_H
#define TreePanelMyScene_H

#include <wx/panel.h>

class TreePanelMyScene: public wxPanel
{
public:

	TreePanelMyScene(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~TreePanelMyScene();
	
protected:

private:

	void OnResize(wxSizeEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif
