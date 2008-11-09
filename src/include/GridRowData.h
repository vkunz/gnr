/**
 * GridRowData
 * @name                GridRowData.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRGRIDROWDATA_H_
#define _GNRGRIDROWDATA_H_

#include <wx/string.h>

class GridRowData
{
public:
	// ctor
	GridRowData();
	
	// loads data
	GridRowData(wxString name, float length, float width, float depth, bool visible, int id);
	
	// dtor
	virtual ~GridRowData();
	
	// functions
	// get assemblyId
	int getId();
	
	// get number of columns
	int getCol();
	
	// index-operator
	wxString operator[](int val);
	
protected:

private:
	// attributes
	// number of columns
	int m_col;
	
	// assembly-name
	wxString m_name;
	
	// assembly-length
	float m_length;
	
	// assembly-width
	float m_width;
	
	// assembly-depth
	float m_depth;
	
	// assembly-isvisible
	bool m_visible;
	
	// assembly-id
	int m_id;
};

#endif // _GNRGRIDROWDATA_H_
