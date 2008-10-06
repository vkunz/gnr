#ifndef GNRDEBUGFRAME_H
#define GNRDEBUGFRAME_H

//(*Headers(GNRDebugFrame)
#include <wx/frame.h>
class wxTextCtrl;
//*)

#include <wx/log.h>

class GNRDebugFrame: public wxFrame
{
	public:

		GNRDebugFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxSize& size=wxDefaultSize);
		virtual ~GNRDebugFrame();

		//(*Declarations(GNRDebugFrame)
		wxTextCtrl* TextCtrl;
		//*)

	protected:

		//(*Identifiers(GNRDebugFrame)
		static const long ID_TextCtrl;
		//*)

	private:

		//(*Handlers(GNRDebugFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
