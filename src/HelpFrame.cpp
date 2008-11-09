/**
 * HelpFrame
 * @note        [DONE]
 * @name        HelpFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/html/htmlwin.h>
#include <wx/artprov.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/button.h>

#include "wx/wxhtml.h"
#include "wx/statline.h"


#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

#include "HelpFrame.h"

/**
 * constructor of HelpFrame
 * @param[in]       parent          parent of frame
 * @param[in]       id              id of frame
 */
HelpFrame::HelpFrame(wxWindow* parent, wxWindowID id)
{
	if (wxFileExists(wxT("help/help.html")))
	{
		wxBoxSizer *topsizer;
		wxHtmlWindow *html;
		
		//create modal dialog
		wxDialog dlg(this, wxID_ANY, wxString(_("GNR 3D Raumplaner - Schnellhilfe")));
		dlg.SetIcon(wxICON(GNR_ICON));
		topsizer = new wxBoxSizer(wxVERTICAL);
		
		//create new html window without borders and help.html (content)
		html = new wxHtmlWindow(&dlg, wxID_ANY, wxDefaultPosition, wxSize(600, 400), wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER);
		html->SetBorders(0);
		html->LoadPage(wxT("help/help.html"));
		
		//add topsizer
		topsizer->Add(html, 1, wxALL, 10);
		topsizer->Add(new wxStaticLine(&dlg, wxID_ANY), 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
		
		//create OK button and set default
		wxButton *bu1 = new wxButton(&dlg, wxID_OK, wxT("OK"));
		bu1->SetDefault();
		
		topsizer->Add(bu1, 0, wxALL | wxALIGN_RIGHT, 15);
		
		//set sizer and position
		dlg.SetSizer(topsizer);
		dlg.SetClientSize(wxSize(600, 400));
		dlg.Move(wxPoint(170,75));
		topsizer->Fit(&dlg);
		
		//show diaog
		dlg.ShowModal();
	}
	else
	{
		wxMessageBox(wxT("Die Hilfe scheint wohl gelöscht worden zu sein!"),wxT("Keine Hilfe verfügbar..."));
	}
}

/**
 * destructor of HelpFrame
 */
HelpFrame::~HelpFrame() {}
