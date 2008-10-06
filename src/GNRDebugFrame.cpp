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

