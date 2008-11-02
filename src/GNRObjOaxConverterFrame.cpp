/**
 * GNRObjOaxConverterFrame
 * @name        GNRObjOaxConverterFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/spinctrl.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GNRNotifyEvent.h"
#include "GNRObjOaxConverterFrame.h"

const long GNRObjOaxConverterFrame::idBtnCreate     = wxNewId();
const long GNRObjOaxConverterFrame::idBtnCancel     = wxNewId();
const long GNRObjOaxConverterFrame::idCkbProportion = wxNewId();
const long GNRObjOaxConverterFrame::idCbxCategory   = wxNewId();
const long GNRObjOaxConverterFrame::idSpcWidth      = wxNewId();
const long GNRObjOaxConverterFrame::idSpcDepth      = wxNewId();
const long GNRObjOaxConverterFrame::idSpcHeight     = wxNewId();
const long GNRObjOaxConverterFrame::idStxName       = wxNewId();
const long GNRObjOaxConverterFrame::idStxCategory   = wxNewId();
const long GNRObjOaxConverterFrame::idStxWidth      = wxNewId();
const long GNRObjOaxConverterFrame::idStxDepth      = wxNewId();
const long GNRObjOaxConverterFrame::idStxHeight     = wxNewId();
const long GNRObjOaxConverterFrame::idTxcName       = wxNewId();

// ctor
GNRObjOaxConverterFrame::GNRObjOaxConverterFrame(wxWindow* parent, wxWindowID id)
{
	// create Frame
	Create(parent, id, wxT("OBJ importieren"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, wxT("ObjOaxConverter"));
	
	// set size
	SetClientSize(wxSize(550, 350));
	
	// Button create
	m_btnCreate     = new wxButton(this, idBtnCreate, wxT("Erstellen"), wxPoint(328,304), wxDefaultSize, 0);
	
	// Button cancel
	m_btnCancel     = new wxButton(this, idBtnCancel, wxT("Abbrechen"), wxPoint(432,304), wxDefaultSize, 0);
	
	// Checkbox proportion
	m_ckbProportion = new wxCheckBox(this, idCkbProportion, wxT("Proportionen behalten"), wxPoint(312,248), wxSize(130,24), 0);
	m_ckbProportion->SetValue(true);
	
	// Combobox category
	m_cbxCategory   = new wxComboBox(this, idCbxCategory, wxT("Sonstige"), wxPoint(384,90), wxSize(130,24), 0, 0, 0);
	
	// SpinCtrl width
	m_spcWidth      = new wxSpinCtrl(this, idSpcWidth, wxT("1"), wxPoint(384,130), wxSize(130,24), wxTE_PROCESS_ENTER, 1, 10000, 1);
	
	// SpinCtrl depth
	m_spcDepth      = new wxSpinCtrl(this, idSpcDepth, wxT("1"), wxPoint(384,170), wxSize(130,24), wxTE_PROCESS_ENTER, 1, 10000, 1);
	
	// SpinCtrl height
	m_spcHeight     = new wxSpinCtrl(this, idSpcHeight, wxT("1"), wxPoint(384,210), wxSize(130,24), wxTE_PROCESS_ENTER, 1, 10000, 1);
	
	// StaticText name
	m_stxName       = new wxStaticText(this, idStxName, wxT("Name:"), wxPoint(280,54), wxSize(100,24), 0);
	
	// StaticText category
	m_stxCategory   = new wxStaticText(this, idStxCategory, wxT("Kategorie:"), wxPoint(280,94), wxSize(72,24), 0);
	
	// StaticText width
	m_stxWidth      = new wxStaticText(this, idStxWidth, wxT("Breite (mm):"), wxPoint(280,134), wxSize(100 ,24), 0);
	
	// StaticText depth
	m_stxDepth      = new wxStaticText(this, idStxDepth, wxT("Tiefe (mm):"), wxPoint(280,174), wxSize(100,24), 0);
	
	// StaticText height
	m_stxHeight     = new wxStaticText(this, idStxHeight, wxT("H\u00F6he (mm):"), wxPoint(280,214), wxSize(100,24), 0);
	
	// TextCtrl name
	m_txcName       = new wxTextCtrl(this, idTxcName, wxT(""), wxPoint(384,50), wxSize(130,24), wxTE_PROCESS_ENTER);
	
	// connects m_btnCreate with OnBtnCreate()
	Connect(idBtnCreate,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnBtnCreate);
	
	// connects m_btnCancel with OnBtnCancel()
	Connect(idBtnCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnBtnCancel);
	
	// connects Close-Button with OnClose()
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnClose);
	
	// connects m_spcWidth with OnSpcWidthChanged
	Connect(idSpcWidth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcWidthChanged);
	
	// connects m_spcDepth with OnSpcDepthChanged
	Connect(idSpcDepth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcDepthChanged);
	
	// connects m_spcHeight with OnSpcHeightChanged
	Connect(idSpcHeight,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcHeightChanged);
	
	// connects m_spcWidth with OnSpcWidthChanged on press Enter
	Connect(idSpcWidth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcWidthChanged);
	
	// connects m_spcDepth with OnSpcDepthChanged on press Enter
	Connect(idSpcDepth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcDepthChanged);
	
	// connects m_spcHeight with OnSpcHeightChanged on press Enter
	Connect(idSpcHeight,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnSpcHeightChanged);
	
	// connects m_txcname with OnTxcNameChanged on press Enter
	Connect(idTxcName,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnTxcNameChanged);
	
	// connects cbxCategory with OnCbxCategoryChanged on selected
	Connect(idCbxCategory,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnCbxCategoryChanged);
	
	// connects cbxCategory with OnCbxCategoryChanged on press Enter
	Connect(idCbxCategory,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnCbxCategoryChanged);
	
	// connects cbxCategory with OnCbxCategoryChanged
	Connect(idCbxCategory,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnCbxCategoryChanged);
	
	// create canvas
	m_canvas = new GNRGLCanvasPreview(this, wxID_ANY, wxPoint(50, 50), wxSize(200, 200), wxSIMPLE_BORDER);
	
	// connects m_txcName with OnTxcNameChanged
	Connect(idTxcName,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnTxcNameChanged);
}

// dtor
GNRObjOaxConverterFrame::~GNRObjOaxConverterFrame()
{
	delete m_canvas;
	
	delete m_txcName;
	
	delete m_stxName;
	delete m_stxCategory;
	delete m_stxHeight;
	delete m_stxDepth;
	delete m_stxWidth;
	
	delete m_spcWidth;
	delete m_spcHeight;
	delete m_spcDepth;
	
	delete m_ckbProportion;
	
	delete m_cbxCategory;
	
	delete m_btnCreate;
	delete m_btnCancel;
}

void GNRObjOaxConverterFrame::setAllCategories(std::vector<wxString>* ptrCat)
{
	// set standard category -> "Sonstiges"
	m_category = (wxT("Sonstiges"));
	
	// set standard category -> "Sonstiges"
	m_cbxCategory->SetValue(wxT("Sonstiges"));
	
	// create temporary iterator to extract all categories
	std::vector<wxString>::iterator it;
	
	// walk through all entrys and get category-name
	for (it = ptrCat->begin(); it != ptrCat->end(); it++)
	{
		m_cbxCategory->AppendString(*it);
	}
	
	// append standard category, so it can be chosen again
	m_cbxCategory->AppendString(wxT("Sonstiges"));
	
	// we took ownership of ptrCat, so we need to delete it
	delete ptrCat;
}

void GNRObjOaxConverterFrame::setFrameData(GNRFrameData* data)
{
	m_frameData = data;
}

void GNRObjOaxConverterFrame::setData()
{
	// set data
	m_width    = m_frameData->m_width;
	m_depth    = m_frameData->m_depth;
	m_height   = m_frameData->m_height;
	m_name     = m_frameData->m_name;
	m_category = m_frameData->m_category;
	
	// if a dimension is greater than 10000, rescale
	if (m_width > 10000 || m_depth > 10000 || m_height > 10000)
	{
		// return max of dimenstions and get scale
		double scale = (max(m_width, m_depth, m_height)) / 10000.0;
		
		// divide by scale
		m_width = (int)(m_width / scale);
		m_depth = (int)(m_depth / scale);
		m_height = (int)(m_height / scale);
	}
	
	// update frame
	updateFrame();
}

GNRGLCanvasPreview* GNRObjOaxConverterFrame::getCanvasPointer()
{
	return m_canvas;
}


void GNRObjOaxConverterFrame::OnBtnCancel(wxCommandEvent& WXUNUSED(event))
{
	// create event
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	
	// set eventType
	gnrevent.setGNREventType(CANCELCONVERTION);
	
	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRObjOaxConverterFrame::OnBtnCreate(wxCommandEvent& WXUNUSED(event))
{
	// prepare data -> store into struct
	// get objName and store into struct
	m_frameData->m_name = m_txcName->GetValue();
	
	// get category and store into struct
	m_frameData->m_category = m_cbxCategory->GetValue();
	
	// calc width-scale
	m_frameData->m_scaleWidth = (((m_width) / m_frameData->m_width));
	
	// calc y-scale
	m_frameData->m_scaleDepth = (((m_depth) / m_frameData->m_depth));
	
	// calc z-scale
	m_frameData->m_scaleHeight = (((m_height) / m_frameData->m_height));
	
	// get width and store into struct
	m_frameData->m_width = (m_spcWidth->GetValue());
	
	// get depth and store into struct
	m_frameData->m_depth = (m_spcDepth->GetValue());
	
	// get height and store into struct
	m_frameData->m_height = (m_spcHeight->GetValue());
	
	// create event
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	
	// set eventType
	gnrevent.setGNREventType(OAXEXPORT);
	
	// set frameData pointer
	gnrevent.setFrameDataPointer(m_frameData);
	
	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRObjOaxConverterFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	// create event
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	
	// set eventType
	gnrevent.setGNREventType(CANCELCONVERTION);
	
	// broadcast event
	GetEventHandler()->ProcessEvent(gnrevent);
}

void GNRObjOaxConverterFrame::OnSpcWidthChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_frameData-value
		m_scaleWidth = (double)event.GetInt() / m_frameData->m_width;
		
		// set new m_width
		m_width = event.GetInt();
		
		// set new dimenstions with new scale
		m_depth = (m_scaleWidth * m_frameData->m_depth);
		m_height = (m_scaleWidth * m_frameData->m_height);
		
		// update frame
		updateFrame();
	}
}

void GNRObjOaxConverterFrame::OnSpcDepthChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_frameData-value
		m_scaleDepth = (float)event.GetInt() / m_frameData->m_depth;
		
		// set new m_width
		m_depth = event.GetInt();
		
		// set new dimenstions with new scale
		m_width = (int)(m_scaleDepth * m_frameData->m_width);
		m_height = (int)(m_scaleDepth * m_frameData->m_height);
		
		// update frame
		updateFrame();
	}
}

void GNRObjOaxConverterFrame::OnSpcHeightChanged(wxSpinEvent& event)
{
	// check if aspect ratio is enabled
	if (m_ckbProportion->GetValue())
	{
		// get scale, calc actual value divide by m_frameData-value
		m_scaleHeight = (float)event.GetInt() / m_frameData->m_height;
		
		// set new m_width
		m_height = event.GetInt();
		
		// set new dimenstions with new scale
		m_width = (int)(m_scaleHeight * m_frameData->m_width);
		m_depth = (int)(m_scaleHeight * m_frameData->m_depth);
		
		// update frame
		updateFrame();
	}
}

void GNRObjOaxConverterFrame::OnTxcNameChanged(wxCommandEvent& WXUNUSED(event))
{
	// get new Value
	m_name = m_txcName->GetValue();
}

void GNRObjOaxConverterFrame::OnCbxCategoryChanged(wxCommandEvent& WXUNUSED(event))
{
	// get new Value
	m_category = m_cbxCategory->GetValue();
}

void GNRObjOaxConverterFrame::updateFrame()
{
	// update name
	m_txcName->SetValue(m_name);
	
	// update category
	m_cbxCategory->SetValue(m_category);
	
	// update width
	m_spcWidth->SetValue((int)m_width);
	
	// update depth
	m_spcDepth->SetValue((int)m_depth);
	
	// update height
	m_spcHeight->SetValue((int)m_height);
}

double GNRObjOaxConverterFrame::max(double width, double depth, double height)
{
	double max = width;
	
	if (max < depth)
	{
		max = depth;
	}
	
	if (max < height)
	{
		max = height;
	}
	
	return max;
}
