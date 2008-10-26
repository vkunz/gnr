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
GNRGridTable::GNRGridTable()
{
}

// dtor
GNRGridTable::~GNRGridTable()
{
}

int GNRGridTable::GetNumberRows()
{
	return WXSIZEOF(gs_GNRGridData);
}

int GNRGridTable::GetNumberCols()
{
	return Col_Max;
}

bool GNRGridTable::IsEmptyCell(int row, int col)
{
	return false;
}

wxString GNRGridTable::GetValue(int row, int col)
{
	const GNRGridData& gd = gs_GNRGridData[row];
	wxString tmp;
	
	switch (col)
	{
	case Col_Name:
		return gd.name;
	case Col_Length:
		tmp << gd.length;
		return tmp;
		tmp = wxT("");
	case Col_Width:
		tmp << gd.width;
		return tmp;
		tmp = wxT("");
	case Col_Depth:
		tmp << gd.depth;
		return tmp;
		tmp = wxT("");
	case Col_Visible:
		return gd.visible ? wxT("1") : wxT("0");
	case Col_Id:
		tmp << gd.id;
		return tmp;
	}
	
	return wxEmptyString;
}

void GNRGridTable::SetValue(int row, int col, const wxString& value)
{

}

wxString GNRGridTable::GetTypeName(int row, int col)
{
	switch (col)
	{
	case Col_Name:
		return wxGRID_VALUE_STRING;
	case Col_Length:
		return wxGRID_VALUE_FLOAT;
	case Col_Width:
		return wxGRID_VALUE_FLOAT;
	case Col_Depth:
		return wxGRID_VALUE_FLOAT;
	case Col_Visible:
		return wxGRID_VALUE_CHOICE;
	case Col_Id:
		return wxGRID_VALUE_LONG;
	}
	
	return wxEmptyString;
}

