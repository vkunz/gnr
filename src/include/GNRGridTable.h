/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreeLibraryController
 * @name                GNRTreeLibraryController.cpp
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGRIDTABLE_H_
#define _GNRGRIDTABLE_H_

#include <wx/grid.h>
#include <wx/string.h>

class GNRGridTable : public wxGridTableBase
{
public:
	// ctor
	GNRGridTable();
	
	// dtor
	virtual ~GNRGridTable();
	
protected:

private:
	// attributes
	
	// functions
	// return number of rows
	int GetNumberRows();
	
	// return number of cols
	int GetNumberCols();
	
	// return if given cell is empty
	bool IsEmptyCell(int row, int col);
	
	// get value of given cell
	wxString GetValue(int row, int col);
	
	// set value of given cell
	void SetValue(int row, int col, const wxString& value);
	
	// get TypeName
	wxString GetTypeName(int row, int col);
};

#endif // _GNRGRIDTABLE_H_
