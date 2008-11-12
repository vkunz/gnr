/**
 * This frame is used to allow the user to change some values of the assembly
 * @note        [DONE]
 * @name        AssemblyDataFrame.cpp
 * @date        2008-11-04
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "include/AssemblyDataFrame.h"

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/valtext.h>
#include <wx/icon.h>

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

/**
 * constructor of AssemblyDataFrame; creates the frame with its controls and connects needed events
 * @param[in]      parent          parent of this frame
 * @param[in]      id
 */
AssemblyDataFrame::AssemblyDataFrame(wxWindow* parent,wxWindowID id)
{
	Create(parent, id, wxT("Objekt-Eigenschaften"), wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSTATIC_BORDER, _T("id"));
	MakeModal();
	SetClientSize(wxSize(350, 300));
	CentreOnParent(wxBOTH);
	SetBackgroundColour(wxNullColour);
	SetIcon(wxICON(gnr_icon));
	
	m_panel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(350, 300), wxTAB_TRAVERSAL);
	
	m_stxName = new wxStaticText(m_panel, -1, wxT("Name:"), wxPoint(30,34), wxSize(80,22), 0);
	m_txcName = new wxTextCtrl(m_panel, idtxcName, wxT(""), wxPoint(120,30), wxSize(150,22), 0, wxDefaultValidator);
	
	m_stxWidth = new wxStaticText(m_panel, -1, wxT("Breite (mm):"), wxPoint(30,84), wxSize(80,22), 0);
	//m_txcWidth = new wxTextCtrl(this, idtxcWidth, wxT(""), wxPoint(120,80), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcWidth = new wxSpinCtrl(m_panel, idSpcWidth, wxT(""), wxPoint(120,80), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_stxHeight = new wxStaticText(m_panel, -1, wxT("Höhe (mm):"), wxPoint(30,114), wxSize(80,22), 0);
	//m_txcHeight = new wxTextCtrl(this, idtxcHeight, wxT(""), wxPoint(120,110), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcHeight = new wxSpinCtrl(m_panel, idSpcHeight, wxT(""), wxPoint(120,110), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_stxDepth = new wxStaticText(m_panel, -1, wxT("Tiefe (mm):"), wxPoint(30,144), wxSize(80,22), 0);
	//m_txcDepth = new wxTextCtrl(this, idtxcDepth, wxT(""), wxPoint(120,140), wxSize(150,22), 0, wxTextValidator(wxFILTER_NUMERIC));
	m_txcDepth = new wxSpinCtrl(m_panel, idSpcDepth, wxT(""), wxPoint(120,140), wxSize(150,22), wxTE_PROCESS_ENTER, SIZE_MINIMUM_VALUE, SIZE_MAXIMUM_VALUE, SIZE_MINIMUM_VALUE);
	
	m_cbxProportion = new wxCheckBox(m_panel, idcbxProportion, wxT("Proportionen beibehalten"), wxPoint(120, 170), wxSize(160, 22));
	m_cbxProportion->SetValue(true);
	
	m_stxVisible = new wxStaticText(m_panel, -1, wxT("Sichtbar:"), wxPoint(30,212), wxSize(80,22), 0);
	m_cbxVisible = new wxCheckBox(m_panel, idcbxVisible, wxEmptyString, wxPoint(120, 210), wxSize(80, 22));
	
	m_btnChange  = new wxButton(m_panel, idBtnChange, wxT("Ändern"), wxPoint(70,255), wxDefaultSize, 0);
	m_btnCancel  = new wxButton(m_panel, idBtnCancel, wxT("Abbrechen"), wxPoint(190,255), wxDefaultSize, 0);
	
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

/**
 * destructor of AssemblyDataFrame
 */
AssemblyDataFrame::~AssemblyDataFrame() {}

/**
 * fills the data-fields with information of the given assembly
 * @param[in]   assembly        assembly, the information can be taken from
 */
void AssemblyDataFrame::fillFields(Assembly* assembly)
{
	m_assembly = assembly;
	
	wxString str;
	
	m_txcName->ChangeValue(assembly->getName());
	
	m_txcWidth->SetValue((int)(assembly->getWidthMeters()*1000));
	m_txcHeight->SetValue((int)(assembly->getHeightMeters()*1000));
	m_txcDepth->SetValue((int)(assembly->getDepthMeters()*1000));
	
	m_cbxVisible->SetValue(m_assembly->isVisible());
	
	m_assemblyWidth  = (int)(assembly->getWidth()  * 1000);
	m_assemblyHeight = (int)(assembly->getHeight() * 1000);
	m_assemblyDepth  = (int)(assembly->getDepth()  * 1000);
}

/**
 * gets called when the users presses the change button in order to confirm his changes;
 * writes the new values to the assembly
 * @param[in]       WXUNUSED       command-event, triggered by the button
 */
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

/**
 * gets called when the user pressed the cancel button in order to discard the changes
 * @param[in]       WXUNUSED       event, triggerd by the button
 */
void AssemblyDataFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

/**
 * gets called when the user closes the window by the X in the top-right corner
 * @param[in]       WXUNUSED       event, triggerd by the button
 */
void AssemblyDataFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	MakeModal(false);
	Destroy();
}

/**
 * gets called when the user changes the width-value
 * @param[in]       WXUNUSED       event, fired on value-change
 */
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

/**
 * gets called when the user changes the height-value
 * @param[in]       WXUNUSED       event, fired on value-change
 */
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

/**
 * gets called when the user changes the depth-value
 * @param[in]       WXUNUSED       event, fired on value-change
 */
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
