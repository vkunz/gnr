/**
 * DebugFrame, just used to have debug output without console;
 * only build in Debug-Build
 * @note        [DONE]
 * @name        DebugFrame.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */



#include <wx/intl.h>
#include <wx/string.h>
#include <wx/artprov.h>

#include <wx/log.h>

#include "DebugFrame.h"

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

const long DebugFrame::ID_TextCtrl = wxNewId();

/**
 * constructor of DebugFrame
 * @param[in]       parent          parent of this frame
 */
DebugFrame::DebugFrame(wxWindow* parent)
{
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
	SetClientSize(wxSize(700,100));
	Move(wxPoint(0,608));
	SetIcon(wxICON(gnr_icon));
	TextCtrl = new wxTextCtrl(this, ID_TextCtrl, wxEmptyString, wxPoint(32,80), wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TextCtrl"));
}

/**
 * destructor of DebugFrame
 */
DebugFrame::~DebugFrame() {}
