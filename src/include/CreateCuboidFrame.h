#ifndef CREATECUBOIDFRAME_H
#define CREATECUBOIDFRAME_H

#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>

class CreateCuboidFrame: public wxFrame
{
public:

	CreateCuboidFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
	virtual ~CreateCuboidFrame();
	
	wxSpinCtrl* m_spcWidth;
	wxSpinCtrl* m_spcHeight;
	wxSpinCtrl* m_spcDepth;
	
	wxPanel* m_panColor;
	
	wxSpinCtrl* m_spcRed;
	wxSpinCtrl* m_spcGreen;
	wxSpinCtrl* m_spcBlue;
	
	wxButton* m_buCreate;
	wxButton* m_buCancel;
	
	wxStaticText* StaticText1;
	wxStaticText* StaticText2;
	wxStaticText* StaticText3;
	wxStaticText* StaticText4;
	wxStaticText* StaticText5;
	wxStaticText* StaticText6;
	wxStaticText* StaticText7;
	
protected:

	static const long idSpcWidth;
	static const long idSpcHeight;
	static const long idSpcDepth;
	static const long ID_STATICTEXT1;
	static const long ID_STATICTEXT2;
	static const long ID_STATICTEXT3;
	static const long idBtnCreate;
	static const long idBtnCancel;
	static const long ID_STATICTEXT4;
	static const long idPanColor;
	static const long idSpcRed;
	static const long idSpcGreen;
	static const long idSpcBlue;
	static const long ID_STATICTEXT5;
	static const long ID_STATICTEXT6;
	static const long ID_STATICTEXT7;
	
private:
	void OnSpcColorChange(wxSpinEvent& WXUNUSED(event));
	void OnCreate(wxCommandEvent& WXUNUSED(event));
	void OnCancel(wxCommandEvent& WXUNUSED(event));
	
	DECLARE_EVENT_TABLE()
};

#endif
