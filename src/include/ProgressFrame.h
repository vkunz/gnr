#ifndef PROGRESSFRAME_H
#define PROGRESSFRAME_H

#include <wx/dialog.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <wx/timer.h>

class ProgressFrame: public wxDialog
{
public:
	ProgressFrame(wxWindow* parent = 0, wxWindowID id=1);
	virtual ~ProgressFrame();
	
	void pulseGauge();
	void close();
protected:
private:
	wxGauge* m_gauge;
	wxStaticText* m_stxInfo;
	
	wxTimer* m_timer;
	
	void OnTimer(wxTimerEvent& WXUNUSED(event));
	
	DECLARE_EVENT_TABLE()
};

#endif // PROGRESSFRAME_H
