#include "include/AssemblyDataFrame.h"

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/valtext.h>
#include <wx/spinctrl.h>

#include "NotifyEvent.h"
#include "GlobalDefine.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "resources/gnr_icon.xpm"
#endif

const long AssemblyDataFrame::idtxcName = wxNewId();
const long AssemblyDataFrame::idSpcWidth = wxNewId();
const long AssemblyDataFrame::idSpcHeight = wxNewId();
const long AssemblyDataFrame::idSpcDepth = wxNewId();
const long AssemblyDataFrame::idcbxVisible = wxNewId();
const long AssemblyDataFrame::idcbxProportion = wxNewId();
const long AssemblyDataFrame::idBtnChange = wxNewId();
const long AssemblyDataFrame::idBtnCancel = wxNewId();


BEGIN_EVENT_TABLE(AssemblyDataFrame,wxFrame)
	EVT_CLOSE(AssemblyDataFrame::OnClose)
	EVT_BUTTON(idBtnChange, AssemblyDataFrame::OnChange)
	EVT_BUTTON(idBtnCancel, AssemblyDataFrame::OnCancel)
END_EVENT_TABLE()

AssemblyDataFrame::AssemblyDataFrame(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxT("Objekt-Eigenschaften"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, _T("id"));
	MakeModal();
	SetClientSize(wxSize(350, 300));
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(_ICON));
	
	m_stxName = new wxStaticText(this, -1, wxT("Name:"), wxPoint(30,34), wxSize(80,22), 0);
	m_txcName = new wxTextCtrl(this, idtxcName, wxT(""), wxPoint(120,30), wxSize(150,22), 0, wxDefaultValidator);
	
	m_stxWidth = new wxStaticText(this, -1, wxT("Breite (mm):"), wxPoint(30,84), wxSize(80,22), 0);
	//m_txcWidth = new wxTextCtrl(this, idtxcWidth, wxT(""), wxPoint(120,80), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcWidth = new wxSpinCtrl(this, idSpcWidth, wxT(""), wxPoint(120,80), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_stxHeight = new wxStaticText(this, -1, wxT("Höhe (mm):"), wxPoint(30,114), wxSize(80,22), 0);
	//m_txcHeight = new wxTextCtrl(this, idtxcHeight, wxT(""), wxPoint(120,110), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcHeight = new wxSpinCtrl(this, idSpcHeight, wxT(""), wxPoint(120,110), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_stxDepth = new wxStaticText(this, -1, wxT("Tiefe (mm):"), wxPoint(30,144), wxSize(80,22), 0);
	//m_txcDepth = new wxTextCtrl(this, idtxcDepth, wxT(""), wxPoint(120,140), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcDepth = new wxSpinCtrl(this, idSpcDepth, wxT(""), wxPoint(120,140), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_cbxProportion = new wxCheckBox(this, idcbxProportion, wxT("Proportionen beibehalten"), wxPoint(120, 170), wxSize(160, 22));
	m_cbxProportion->SetValue(true);
	
	m_stxVisible = new wxStaticText(this, -1, wxT("Sichtbar:"), wxPoint(30,212), wxSize(80,22), 0);
	m_cbxVisible = new wxCheckBox(this, idcbxVisible, wxEmptyString, wxPoint(120, 210), wxSize(80, 22));
	
	m_btnChange  = new wxButton(this, idBtnChange, wxT("Ändern"), wxPoint(70,255), wxDefaultSize, 0);
	m_btnCancel  = new wxButton(this, idBtnCancel, wxT("Abbrechen"), wxPoint(190,255), wxDefaultSize, 0);
	
	// connects m_spcWidth with OnSpcWidthChange
	Connect(idSpcWidth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AssemblyDataFrame::OnWidthChange);
	
	// connects m_spcDepth with OnSpcDepthChange
	Connect(idSpcDepth,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AssemblyDataFrame::OnDepthChange);
	
	// connects m_spcHeight with OnSpcHeightChange
	Connect(idSpcHeight,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&AssemblyDataFrame::OnHeightChange);
	
	// connects m_spcWidth with OnSpcWidthChange on press Enter
	Connect(idSpcWidth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&AssemblyDataFrame::OnWidthChange);
	
	// connects m_spcDepth with OnSpcDepthChange on press Enter
	Connect(idSpcDepth,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&AssemblyDataFrame::OnDepthChange);
	
	// connects m_spcHeight with OnSpcHeightChange on press Enter
	Connect(idSpcHeight,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&AssemblyDataFrame::OnHeightChange);
}

AssemblyDataFrame::~AssemblyDataFrame()
{

}

void AssemblyDataFrame::fillFields(Assembly* assembly)
{
	m_assembly = assembly;
	
	wxString str;
	
	m_txcName->ChangeValue(assembly->getName());
	
	m_txcWidth->SetValue((int)(assembly->getWidth()*assembly->getScaleX()*1000));
	m_txcHeight->SetValue((int)(assembly->getHeight()*assembly->getScaleY()*1000));
	m_txcDepth->SetValue((int)(assembly->getDepth()*assembly->getScaleZ()*1000));
	
	m_cbxVisible->SetValue(m_assembly->isVisible());
	
	m_assemblyWidth  = (int)(assembly->getWidth()  * 1000);
	m_assemblyHeight = (int)(assembly->getHeight() * 1000);
	m_assemblyDepth  = (int)(assembly->getDepth()  * 1000);
}

void AssemblyDataFrame::OnChange(wxCommandEvent& WXUNUSED(event))
{
	m_assembly->setName(m_txcName->GetValue());
	
	float factor = (float)m_txcWidth->GetValue() / m_assemblyWidth;
	m_assembly->setScaleX(factor);
	
	//fix for keeping bottom of object on same level
	float old_h = m_assembly->getHeightMeters();
	float old_y = m_assembly->getY();
	
	//calculate new scale
	factor = (float)m_txcHeight->GetValue() / m_assemblyHeight;
	m_assembly->setScaleY(factor);
	
	//now correct y-level of center
	m_assembly->setY(old_y+(m_assembly->getHeightMeters()-old_h)/2.0);
	
	factor = (float)m_txcDepth->GetValue() / m_assemblyDepth;
	m_assembly->setScaleZ(factor);
	
	m_assembly->setVisible(m_cbxVisible->IsChecked());
	
	// send event to refresh canvas
	NotifyEvent myevent(wxEVT_COMMAND_GNR_NOTIFY);
	myevent.setGNREventType(GLREFRESH);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
	
	// send event to refresh tree
	myevent.setGNREventType(REFRESHSCENETREE);
	myevent.SetEventObject(this);
	GetEventHandler()->ProcessEvent(myevent);
	
	MakeModal(false);
	Destroy();
}

void AssemblyDataFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

void AssemblyDataFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

void AssemblyDataFrame::OnWidthChange(wxCommandEvent& WXUNUSED(event))
{
	if (m_cbxProportion->IsChecked() == true)
	{
		float width = m_txcWidth->GetValue();
		
		if (width >= SIZE_MAXIMUM_VALUE)
		{
			width = SIZE_MAXIMUM_VALUE;
		}
		else if (width <= SIZE_MINIMUM_VALUE)
		{
			width = SIZE_MINIMUM_VALUE;
		}
		
		int n_height = (int)((width / m_assemblyWidth) * m_assemblyHeight);
		int n_depth  = (int)((width / m_assemblyWidth) * m_assemblyDepth);
		
		m_txcHeight->SetValue(n_height);
		m_txcDepth->SetValue(n_depth);
	}
}

void AssemblyDataFrame::OnHeightChange(wxCommandEvent& WXUNUSED(event))
{
	if (m_cbxProportion->IsChecked() == true)
	{
		float height = m_txcHeight->GetValue();
		
		if (height >= SIZE_MAXIMUM_VALUE)
		{
			height = SIZE_MAXIMUM_VALUE;
		}
		else if (height <= SIZE_MINIMUM_VALUE)
		{
			height = SIZE_MINIMUM_VALUE;
		}
		
		int n_width  = (int)((height / m_assemblyHeight) * m_assemblyWidth);
		int n_depth  = (int)((height / m_assemblyHeight) * m_assemblyDepth);
		
		m_txcWidth->SetValue(n_width);
		m_txcDepth->SetValue(n_depth);
	}
}

void AssemblyDataFrame::OnDepthChange(wxCommandEvent& WXUNUSED(event))
{
	if (m_cbxProportion->IsChecked() == true)
	{
		float depth = m_txcDepth->GetValue();
		
		if (depth >= SIZE_MAXIMUM_VALUE)
		{
			depth = SIZE_MAXIMUM_VALUE;
		}
		else if (depth <= SIZE_MINIMUM_VALUE)
		{
			depth = SIZE_MINIMUM_VALUE;
		}
		
		int n_width  = (int)((depth / m_assemblyDepth) * m_assemblyWidth);
		int n_height = (int)((depth / m_assemblyDepth) * m_assemblyHeight);
		
		m_txcWidth->SetValue(n_width);
		m_txcHeight->SetValue(n_height);
	}
}
