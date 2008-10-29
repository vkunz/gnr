/**
 * GNRObjOaxConverterFrame
 * @name        GNRObjOaxConverterFrame.cpp
 * @date        2008-10-28
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
const long GNRObjOaxConverterFrame::idTxtName       = wxNewId();

// ctor
GNRObjOaxConverterFrame::GNRObjOaxConverterFrame(wxWindow* parent, wxWindowID id)
{
	// create Frame
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxSTAY_ON_TOP|wxMINIMIZE_BOX|wxSTATIC_BORDER, wxT("ObjOaxConverter"));
	
	// set size
	SetClientSize(wxSize(550, 350));
	
	// Button create
	m_btnCreate     = new wxButton(this, idBtnCreate, wxT("Erstellen"), wxPoint(328,304), wxDefaultSize, 0, wxDefaultValidator);
	
	// Button cancel
	m_btnCancel     = new wxButton(this, idBtnCancel, wxT("Abbrechen"), wxPoint(432,304), wxDefaultSize, 0, wxDefaultValidator);
	
	// Checkbox proportion
	m_ckbProportion = new wxCheckBox(this, idCkbProportion, wxT("Proportionen behalten"), wxPoint(312,248), wxSize(130,24), 0, wxDefaultValidator);
	m_ckbProportion->SetValue(true);
	
	// Combobox category
	m_cbxCategory   = new wxComboBox(this, idCbxCategory, wxEmptyString, wxPoint(384,90), wxSize(130,24), 0, 0, 0, wxDefaultValidator);
	
	// SpinCtrl width
	m_spcWidth      = new wxSpinCtrl(this, idSpcWidth, wxEmptyString, wxPoint(384,130), wxSize(130,24), 0, 0, 100, 0);
	
	// SpinCtrl depth
	m_spcDepth      = new wxSpinCtrl(this, idSpcDepth, wxEmptyString, wxPoint(384,170), wxSize(130,24), 0, 0, 100, 0);
	
	// SpinCtrl height
	m_spcHeight     = new wxSpinCtrl(this, idSpcHeight, wxEmptyString, wxPoint(384,210), wxSize(130,24), 0, 0, 100, 0);
	
	// StaticText name
	m_stxName       = new wxStaticText(this, idStxName, wxT("Name:"), wxPoint(280,54), wxSize(100,24), 0);
	
	// StaticText category
	m_stxCategory   = new wxStaticText(this, idStxCategory, wxT("Kategorie:"), wxPoint(280,94), wxSize(72,24), 0);
	
	// StaticText width
	m_stxWidth      = new wxStaticText(this, idStxWidth, wxT("Breite:"), wxPoint(280,134), wxSize(100 ,24), 0);
	
	// StaticText depth
	m_stxDepth      = new wxStaticText(this, idStxDepth, wxT("Tiefe:"), wxPoint(280,174), wxSize(100,24), 0);
	
	// StaticText height
	m_stxHeight     = new wxStaticText(this, idStxHeight, wxT("H\u00F6he:"), wxPoint(280,214), wxSize(100,24), 0);
	
	// TextCtrl name
	m_txcName       = new wxTextCtrl(this, idTxtName, wxEmptyString, wxPoint(384,50), wxSize(130,24), 0, wxDefaultValidator);
	
	// connects m_btnCancel with OnBtnCancel()
	Connect(idBtnCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnBtnCancel);
	
	// connects m_btnCancel with OnBtnCancel()
	Connect(idBtnCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnBtnCancel);
	
	// connects X with OnClose()
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&GNRObjOaxConverterFrame::OnClose);
	
	// create canvas
	m_canvas = new GNRGLCanvasPreview(this, wxID_ANY, wxPoint(50, 50), wxSize(200, 200), wxSIMPLE_BORDER);
}

// dtor
GNRObjOaxConverterFrame::~GNRObjOaxConverterFrame()
{
	// do nothing
}

void GNRObjOaxConverterFrame::OnBtnCancel(wxCommandEvent& WXUNUSED(event))
{
	// destroy frame, everything is lost
	Destroy();
}

void GNRObjOaxConverterFrame::OnBtnCreate(wxCommandEvent& WXUNUSED(event))
{

}

void GNRObjOaxConverterFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	// destroy frame, everything is lost
	Destroy();
}
