/**
 * GNRGridTable
 * @name                GNRGridTable.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGRIDTABLE_H_
#define _GNRGRIDTABLE_H_

#include <vector>
#include <wx/arrstr.h>
#include <wx/grid.h>
#include <wx/string.h>

#include "GNRGridRowData.h"

class GNRGridTable : public wxGridTableBase
{
public:
	// ctor
	GNRGridTable();
	
	GNRGridTable(int numRows, int numCols);
	
	// dtor
	virtual ~GNRGridTable();
	
	// functions
	// return number of rows
	int GetNumberRows();
	
	// return number of cols
	int GetNumberCols();
	
	// get value of choosen cell
	wxString GetValue(int row, int col);
	
	// set value to choosen cell
	void SetValue(int row, int col, const wxString& s);
	
	// check if choosen cell is empty
	bool IsEmptyCell(int row, int col);
	
	// clear table
	void Clear();
	
	// insert rows at position pos
	bool InsertRows(size_t pos = 0, size_t numRows = 1);
	
	// insert rows at the end of the table
	bool AppendRows(size_t numRows = 1);
	
	// delete rows at position pos
	bool DeleteRows(size_t pos = 0, size_t numRows = 1);
	
//    bool InsertCols( size_t pos = 0, size_t numCols = 1 );
//    bool AppendCols( size_t numCols = 1 );
//    bool DeleteCols( size_t pos = 0, size_t numCols = 1 );

	// set row labels
	void SetRowLabelValue(int row, const wxString&);
	
	// set headers
	void SetColLabelValue(int col, const wxString&);
	
	// get row labels
	wxString GetRowLabelValue(int row);
	
	// get headers
	wxString GetColLabelValue(int col);
	
protected:

private:
	// attributes
	// vector of GNRGridRowData
	std::vector<GNRGridRowData> m_vector;
	
	// random access iterator
	std::vector<GNRGridRowData>::iterator m_vectorit;
	
	// row labels
	wxArrayString m_rowLabels;
	
	// col labels
	wxArrayString m_colLabels;
};

#endif // _GNRGRIDTABLE_H_
