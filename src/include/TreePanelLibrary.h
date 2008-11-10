/**
 * TreePanelLibrary
 * @name        TreePanelLibrary.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef TreePanelLibrary_H
#define TreePanelLibrary_H

#include <wx/panel.h>

class TreePanelLibrary: public wxPanel
{
public:

	TreePanelLibrary(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~TreePanelLibrary();
	
protected:

private:

	void OnResize(wxSizeEvent& WXUNUSED(event));
	
	DECLARE_EVENT_TABLE()
};

#endif
