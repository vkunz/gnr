/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRTreeLibraryController
 * @name                GNRTreeLibraryController.h
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
