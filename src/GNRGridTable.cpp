/**
 * GNRGridTable
 * @name                GNRGridTable.cpp
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGridTable.h"

enum Columns
{
	Col_Name,
	Col_Length,
	Col_Width,
	Col_Depth,
	Col_Visible,
	Col_Id,
	Col_Max
};

static struct GNRGridData
{
	wxString name;
	float length;
	float width;
	float depth;
	bool visible;
	int id;
} gs_GNRGridData [] =
{
	{ wxT("Test"), 17.05f, 17.05f, 17.05f, true, 111},
};

static const wxChar *headers[Col_Max] =
{
	wxT("Name"),
	wxT("Länge"),
	wxT("Breite"),
	wxT("Tiefe"),
	wxT("Sichtbar"),
};

// ctor
GNRGridTable::GNRGridTable() : wxGridTableBase()
{
}

GNRGridTable::GNRGridTable(int numRows, int WXUNUSED(numCols))
{
	m_vector.resize(numRows);
}

// dtor
GNRGridTable::~GNRGridTable()
{
}

int GNRGridTable::GetNumberRows()
{
	return m_vector.size();
}

int GNRGridTable::GetNumberCols()
{
	return 6;
}

wxString GNRGridTable::GetValue(int row, int col)
{
	wxString tmp;
	GNRGridRowData grdtmp = m_vector[row];
	
	tmp = grdtmp[col];
	
	return tmp;
}

void GNRGridTable::SetValue(int row, int col, const wxString& s)
{
	m_vector[row][col] = s;
}

bool GNRGridTable::IsEmptyCell(int row, int col)
{
	return false;
}

void GNRGridTable::Clear()
{
	m_vector.clear();
}

bool GNRGridTable::InsertRows(size_t pos, size_t numRows)
{

}

bool GNRGridTable::AppendRows(size_t numRows)
{

}

bool GNRGridTable::DeleteRows(size_t pos, size_t numRows)
{

}

void GNRGridTable::SetRowLabelValue(int row, const wxString&)
{

}

void GNRGridTable::SetColLabelValue(int col, const wxString& value)
{
	if (col > (int)(m_colLabels.GetCount()) - 1)
	{
		int n = m_colLabels.GetCount();
		int i;
		
		for (i = n; i <= col; i++)
		{
			m_colLabels.Add(wxGridTableBase::GetColLabelValue(i));
		}
	}
	
	m_colLabels[col] = value;
}

wxString GNRGridTable::GetRowLabelValue(int row)
{

}

wxString GNRGridTable::GetColLabelValue(int col)
{
	if (col > (int)(m_colLabels.GetCount()) - 1)
	{
		// using default label
		//
		return wxGridTableBase::GetColLabelValue(col);
	}
	else
	{
		return m_colLabels[col];
	}
}
