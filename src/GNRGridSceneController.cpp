/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRGridSceneController
 * @name                GNRGridSceneController.cpp
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/string.h>

#include "GNRGridSceneController.h"
#include "GNRGridTable.h"

/**
 * Constructor.
 * @param       wxGrid*         Assigns pointer to wxGrid.
 */
GNRGridSceneController::GNRGridSceneController(wxGrid* grid)
{
	// store pointer to grid
	m_grid = grid;
	
	// build grid
	buildGrid();
}

/**
 * Virtual Destructor.
 */
GNRGridSceneController::~GNRGridSceneController()
{
	// do nothing
}

/**
 * Builds Grid on actual data.
 */
void GNRGridSceneController::buildGrid()
{
	// creat own table
	//wxGridTableBase* table = new GNRGridTable();
	
	// set table
	//m_grid->SetTable(table, true);
	
	// create grid, 1 row, 5 cols
	m_grid->CreateGrid(1, 5);
	
	// disable rowlabel
	m_grid->SetRowLabelSize(0);
	
	// set headers
	m_grid->SetColLabelValue(0, wxT("Name"));
	m_grid->SetColLabelValue(1, wxT("L\u00E4nge"));
	m_grid->SetColLabelValue(2, wxT("Breite"));
	m_grid->SetColLabelValue(3, wxT("Tiefe"));
	m_grid->SetColLabelValue(4, wxT("Sichtbar"));
	
	// enalbe lines
	m_grid->EnableGridLines(true);
	
	// set row size
	m_grid->SetRowSize(0, 20);
	
	m_grid->AutoSize();
}
