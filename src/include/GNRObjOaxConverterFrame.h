/**
 * GNRObjOaxConverterFrame
 * @name        GNRObjOaxConverterFrame.h
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNROBJOAXCONVERTERFRAME_H_
#define _GNROBJOAXCONVERTERFRAME_H_

#include <map>
#include <vector>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/string.h>

#include "GNRFrameData.h"
#include "GNRGLCanvasPreview.h"
#include "GNRGlobalDefine.h"

class GNRObjOaxConverterFrame : public wxFrame
{
public:
	// ctor
	GNRObjOaxConverterFrame(wxWindow* parent = 0, wxWindowID id = wxID_ANY);
	
	// ctor
	virtual ~GNRObjOaxConverterFrame();
	
	// functions
	
	// set categories to ComboBox
	void setAllCategories(std::vector<wxString>* ptrCat);
	
	// set Data to fill the frame
	void setFrameData(GNRFrameData* data);
	
	// set Data into internal attributes
	void setData();
	
	// get canvas
	GNRGLCanvasPreview* getCanvasPointer();
	
protected:

private:
	// attributes
	// id's
	static const long idBtnCreate;
	static const long idBtnCancel;
	static const long idCkbProportion;
	static const long idCbxCategory;
	static const long idSpcWidth;
	static const long idSpcDepth;
	static const long idSpcHeight;
	static const long idStxName;
	static const long idStxCategory;
	static const long idStxWidth;
	static const long idStxDepth;
	static const long idStxHeight;
	static const long idTxcName;
	
	// width, depth, height
	double m_width, m_depth, m_height;
	
	// scale width, depth, height
	double m_scaleWidth, m_scaleDepth, m_scaleHeight;
	
	// object-name
	wxString m_name;
	
	// object-category
	wxString m_category;
	
	// Canvas
	GNRGLCanvasPreview* m_canvas;
	
	// Button
	wxButton* m_btnCreate;
	wxButton* m_btnCancel;
	
	// Checkbox
	wxCheckBox* m_ckbProportion;
	
	// ComboBox
	wxComboBox* m_cbxCategory;
	
	// SpinCtrl
	wxSpinCtrl* m_spcWidth;
	wxSpinCtrl* m_spcDepth;
	wxSpinCtrl* m_spcHeight;
	
	// StaticText
	wxStaticText* m_stxName;
	wxStaticText* m_stxCategory;
	wxStaticText* m_stxWidth;
	wxStaticText* m_stxDepth;
	wxStaticText* m_stxHeight;
	
	// TextCtrl
	wxTextCtrl* m_txcName;
	
	// pointer to struc which contain all data needed by frame
	GNRFrameData* m_frameData;
	
	// functions
	// handler
	void OnBtnCancel(wxCommandEvent& event);
	void OnBtnCreate(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnSpcWidthChanged(wxSpinEvent& event);
	void OnSpcDepthChanged(wxSpinEvent& event);
	void OnSpcHeightChanged(wxSpinEvent& event);
	void OnTxcNameChanged(wxCommandEvent& event);
	void OnCbxCategoryChanged(wxCommandEvent& event);
	
	// update frame
	void updateFrame();
	
	// maxfunction, return scale
	double max(double width, double depth, double height);
};

#endif // _GNROBJOAXCONVERTERFRAME_H_
