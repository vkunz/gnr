/**
 * GridSceneController
 * @name                GridSceneController.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGRIDSCENECONTROLLER_H_
#define _GNRGRIDSCENECONTROLLER_H_

#include <vector>
#include <wx/grid.h>

#include "Assembly.h"
#include "GridRowData.h"

/**
 * @class GridSceneController
 *
 * This class manages the grid on the left side of the Application.
*/
class GridSceneController
{
public:
	// ctor
	GridSceneController(wxGrid* grid);
	
	// dtor
	virtual ~GridSceneController();
	
	void addEntry(Assembly* assembly);
	void removeEntry(int assemblyId);
	
protected:

private:
	// attributes
	// pointer to grid
	wxGrid* m_grid;
	
	// vector of name, height, weight, depth, isvisible, id
	std::vector<GridRowData> m_vector;
	
	// random access iterator
	std::vector<GridRowData>::iterator m_vectorit;
	
	// functions
	void buildGrid();
};

#endif // _GNRGRIDSCENECONTROLLER_H_
