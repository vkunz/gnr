/**
 * GNRHelpFrame
 * @name        GNRHelpFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GNRHelpFrame.h"

const long GNRHelpFrame::ID_HTMLWINDOW1     = wxNewId();

GNRHelpFrame::GNRHelpFrame(wxWindow* parent, wxWindowID id)
{
	Create(parent, id, wxT("Hilfe"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, wxT("ObjOaxConverter"));
	
	SetClientSize(wxSize(550, 350));
	
#warning "INFO: TODO QUICKLY!!!"
}

GNRHelpFrame::~GNRHelpFrame()
{
}
