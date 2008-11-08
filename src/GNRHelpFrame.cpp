/**
 * GNRHelpFrame
 * @name        GNRHelpFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/html/htmlwin.h>
#include <wx/artprov.h>
#include <wx/msgdlg.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

#include "GNRHelpFrame.h"

GNRHelpFrame::GNRHelpFrame(wxWindow* parent, wxWindowID id)
{
	if (wxFileExists(wxT("help/help.html")))
	{
		Create(parent, id, wxT("GNR - Hilfe"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, wxT("ObjOaxConverter"));
		SetClientSize(wxSize(700, 450));
		Move(wxPoint(50,50));
		SetIcon(wxICON(GNR_ICON));
		
		m_window = new wxHtmlWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_DEFAULT_STYLE, wxT("HTML - Hilfe"));
		m_window->LoadPage(wxT("help/help.html"));
	}
	else
	{
		wxMessageBox(wxT("Die Hilfe scheint wohl gel�scht worden zu sein!"),wxT("Keine Hilfe verf�gbar..."));
	}
}

GNRHelpFrame::~GNRHelpFrame()
{
}
