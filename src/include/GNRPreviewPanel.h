/**
 * GNRPreviewPanel
 * @name        GNRPreviewPanel.h
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRPREVIEWPANEL_H_
#define _GNRPREVIEWPANEL_H_

#include <wx/panel.h>

class GNRPreviewPanel : public wxPanel
{
public:
	// ctor
	GNRPreviewPanel(wxWindow* parent, wxWindowID id = wxID_ANY);
	
	// dtor
	virtual ~GNRPreviewPanel();
	
protected:

private:

};

#endif // _GNRPREVIEWPANEL_H_
