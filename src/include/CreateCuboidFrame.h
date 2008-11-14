#ifndef CREATECUBOIDFRAME_H
#define CREATECUBOIDFRAME_H

#include <wx/clrpicker.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>

class CreateCuboidFrame: public wxFrame
{
public:

	CreateCuboidFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
	virtual ~CreateCuboidFrame();
	
protected:

	static const long idSpcWidth;
	static const long idSpcHeight;
	static const long idSpcDepth;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	static const long ID_STATICTEXT3;
	static const long idBuCreate;
	static const long idBuCancel;
	static const long ID_STATICTEXT4;
	static const long idColourPicker;
	
private:
	wxPanel* m_panel;
	
	wxSpinCtrl* m_spcWidth;
	wxSpinCtrl* m_spcHeight;
	wxSpinCtrl* m_spcDepth;
	
	wxColourPickerCtrl* m_colourPicker;
	
	wxButton* m_buCreate;
	wxButton* m_buCancel;
	
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	wxStaticText* StaticText3;
	wxStaticText* StaticText4;
	
	void OnCreate(wxCommandEvent& event);
	void OnCancel(wxCommandEvent& event);
	
	
	DECLARE_EVENT_TABLE()
};

#endif
