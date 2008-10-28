/**
 * GNRGridRowData
 * @name                GNRGridRowData.cpp
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRGridRowData.h"

/**
 * Default Constructor.
 */
GNRGridRowData::GNRGridRowData()
{
	//ctor
}

/**
 * Constructor.
 * Assigns parameters to internal attributes.
 * @param       wxString        Name of Assembly.
 * @param       float           Length of Assembly.
 * @param       float           Width of Assembly.
 * @param       float           Depth of Assembly.
 * @param       bool            Visibility of Assembly.
 * @param       int             AssemblyId.
 */
GNRGridRowData::GNRGridRowData(wxString name, float length, float width, float depth, bool visible, int id)
{
	// we have 6 hard-coded columns
	m_col = 6;
	
	// set name
	m_name = name;
	
	// set length
	m_length = length;
	
	// set width
	m_width = width;
	
	// set depth
	m_depth = depth;
	
	// set visible
	m_visible = visible;
	
	// set id
	m_id = id;
}

/**
 * Virtual Destructor
 */
GNRGridRowData::~GNRGridRowData()
{
	//dtor
}

/**
 * @return      AssemblyId.
 */
int GNRGridRowData::getId()
{
	return m_id;
}

int GNRGridRowData::getCol()
{
	return m_col;
}

wxString GNRGridRowData::operator[](int val)
{
	// temporary attribute for converting
	wxString tmp;
	
	// switch, which column is chosen
	switch (val)
	{
	case 0:
		return m_name;
	case 1:
		tmp << m_length;
		return tmp;
	case 2:
		tmp << m_width;
		return tmp;
	case 3:
		tmp << m_depth;
		return tmp;
	case 4:
		if (m_visible)
		{
			return wxT("true");
		}
		else
		{
			return wxT("false");
		}
	case 5:
		tmp << m_id;
		return tmp;
	}
	
	return wxT("");
}
