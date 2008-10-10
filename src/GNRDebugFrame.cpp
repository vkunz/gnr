/* vim: set expandtab sw=4 ts=4 sts=4: */
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

//(*InternalHeaders(GNRDebugFrame)
#include <wx/textctrl.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/log.h>

//(*IdInit(GNRDebugFrame)
const long GNRDebugFrame::ID_TextCtrl = wxNewId();
//*)

BEGIN_EVENT_TABLE(GNRDebugFrame,wxFrame)
	//(*EventTable(GNRDebugFrame)
	//*)
END_EVENT_TABLE()

GNRDebugFrame::GNRDebugFrame(wxWindow* parent,wxWindowID id,const wxSize& size)
{
	//(*Initialize(GNRDebugFrame)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(800,400));
	TextCtrl = new wxTextCtrl(this, ID_TextCtrl, wxEmptyString, wxPoint(32,80), wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TextCtrl"));
	//*)
}

GNRDebugFrame::~GNRDebugFrame()
{
	//(*Destroy(GNRDebugFrame)
	//*)
}

