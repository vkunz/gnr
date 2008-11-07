/**
 * GNRDebugFrame
 * @name        GNRDebugFrame.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRDebugFrame.h"

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/artprov.h>

#include <wx/log.h>

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

//(*IdInit(GNRDebugFrame)
const long GNRDebugFrame::ID_TextCtrl = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRDebugFrame,wxFrame)
	//(*EventTable(GNRDebugFrame)
	//*)
END_EVENT_TABLE()

GNRDebugFrame::GNRDebugFrame(wxWindow* parent,wxWindowID WXUNUSED(id))
{
	//(*Initialize(GNRDebugFrame)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetClientSize(wxSize(700,100));
	Move(wxPoint(0,608));
	SetIcon(wxICON(GNR_ICON));
	TextCtrl = new wxTextCtrl(this, ID_TextCtrl, wxEmptyString, wxPoint(32,80), wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TextCtrl"));
	//*)
}

GNRDebugFrame::~GNRDebugFrame()
{
	//(*Destroy(GNRDebugFrame)
	//*)
}

