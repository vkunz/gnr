#include "ProgressFrame.h"

#include <wx/icon.h>

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

int const idTimer = wxNewId();

BEGIN_EVENT_TABLE(ProgressFrame, wxDialog)
	EVT_TIMER(idTimer, ProgressFrame::OnTimer)
END_EVENT_TABLE()

ProgressFrame::ProgressFrame(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxT("Import"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU, _T("id"));
	MakeModal();
	CentreOnParent(wxBOTH);
	SetClientSize(wxSize(400, 100));
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(gnr_icon));
	
	// create controls
	m_stxInfo = new wxStaticText(this, -1, wxT("Daten werden importiert..."), wxPoint(20, 16), wxSize(200,22), 0);
	m_gauge = new wxGauge(this, wxID_ANY, 50, wxPoint(20, 50), wxSize(360, 25), wxGA_HORIZONTAL);
	
	// Timer to make gauge moving
	m_timer = new wxTimer(this, idTimer);
	m_timer->Start(60);
}

ProgressFrame::~ProgressFrame() {}

void ProgressFrame::pulseGauge()
{
	m_gauge->Pulse();
}

void ProgressFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	pulseGauge();
}

void ProgressFrame::close()
{
	delete m_timer;
	MakeModal(false);
	Destroy();
}
