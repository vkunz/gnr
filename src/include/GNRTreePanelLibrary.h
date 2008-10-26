/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreePanelLibrary
 * @name        GNRTreePanelLibrary.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRTreePanelLibrary_H
#define GNRTreePanelLibrary_H

#include <wx/panel.h>
class wxTreeCtrl;
class wxTreeEvent;

class GNRTreePanelLibrary: public wxPanel
{
public:

	GNRTreePanelLibrary(wxWindow* parent,wxWindowID id=wxID_ANY);
	virtual ~GNRTreePanelLibrary();
	
protected:

	static const long ID_TREECTRL;
	
private:

	void OnResize(wxSizeEvent& event);
	
	DECLARE_EVENT_TABLE()
};

#endif
