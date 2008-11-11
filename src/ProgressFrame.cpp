/**
 * ProgressFrame displays a progressbar (gauge) to show application-progress
 * @note        [DONE]
 * @name        ProgressFrame.cpp
 * @date        2008-11-11
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "ProgressFrame.h"

#include <wx/icon.h>

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

int const idTimer = wxNewId();

BEGIN_EVENT_TABLE(ProgressFrame, wxDialog)
	EVT_TIMER(idTimer, ProgressFrame::OnTimer)
END_EVENT_TABLE()

/**
 * constructor that initializes frame, places controls on it and starts timer
 */
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

/**
 * destructor of ProgressFrame
 */
ProgressFrame::~ProgressFrame() {}

/**
 * fetches the timer-event and moves the gauge step by step forward
 */
void ProgressFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	m_gauge->Pulse();
}

/**
 * stops timer and frees the frame
 */
void ProgressFrame::close()
{
	delete m_timer;
	MakeModal(false);
	Destroy();
}
