#ifndef GNRASSEMBLYDATAFRAME_H
#define GNRASSEMBLYDATAFRAME_H

#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/frame.h>

#include "GNRAssembly.h"

class GNRAssemblyDataFrame: public wxFrame
{
public:

	GNRAssemblyDataFrame(wxWindow* parent = 0, wxWindowID id=1);
	virtual ~GNRAssemblyDataFrame();
	
	void fillFields(GNRAssembly* assembly);
	
protected:

private:
	// assembly-sizes
	float m_assemblyWidth, m_assemblyHeight, m_assemblyDepth;
	
	GNRAssembly* m_assembly;
	
	// text boxes
	wxTextCtrl* m_txcName;
	
	wxSpinCtrl* m_txcWidth;
	wxSpinCtrl* m_txcHeight;
	wxSpinCtrl* m_txcDepth;
	
	wxCheckBox* m_cbxVisible;
	wxCheckBox* m_cbxProportion;
	
	// buttons
	wxButton* m_btnChange;
	wxButton* m_btnCancel;
	
	// text labels
	wxStaticText* m_stxName;
	
	wxStaticText* m_stxWidth;
	wxStaticText* m_stxHeight;
	wxStaticText* m_stxDepth;
	
	wxStaticText* m_stxVisible;
	wxStaticText* m_stxProportion;
	
	// ids
	static const long idtxcName;
	static const long idSpcWidth;
	static const long idSpcHeight;
	static const long idSpcDepth;
	static const long idcbxVisible;
	static const long idcbxProportion;
	static const long idBtnChange;
	static const long idBtnCancel;
	
	void OnChange(wxCommandEvent& WXUNUSED(event));
	void OnCancel(wxCommandEvent& WXUNUSED(event));
	void OnClose(wxCloseEvent& WXUNUSED(event));
	void OnWidthChange(wxCommandEvent& WXUNUSED(event));
	void OnHeightChange(wxCommandEvent& WXUNUSED(event));
	void OnDepthChange(wxCommandEvent& WXUNUSED(event));
	
	DECLARE_EVENT_TABLE()
};

#endif
