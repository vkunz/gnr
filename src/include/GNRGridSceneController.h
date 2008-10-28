/**
 * GNRGridSceneController
 * @name                GNRGridSceneController.h
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

#include "GNRAssembly.h"
#include "GNRGridRowData.h"

/**
 * @class GNRGridSceneController
 *
 * This class manages the grid on the left side of the Application.
*/
class GNRGridSceneController
{
public:
	// ctor
	GNRGridSceneController(wxGrid* grid);
	
	// dtor
	virtual ~GNRGridSceneController();
	
	void addEntry(GNRAssembly* assembly);
	void removeEntry(int assemblyId);
	
protected:

private:
	// attributes
	// pointer to grid
	wxGrid* m_grid;
	
	// vector of name, height, weight, depth, isvisible, id
	std::vector<GNRGridRowData> m_vector;
	
	// random access iterator
	std::vector<GNRGridRowData>::iterator m_vectorit;
	
	// functions
	void buildGrid();
};

#endif // _GNRGRIDSCENECONTROLLER_H_
