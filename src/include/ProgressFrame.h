/**
 * ProgressFrame
 * @name        ProgressFrame.cpp
 * @date        2008-11-11
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
