#ifndef _GNRASSEMBLY_H_
#define _GNRASSEMBLY_H_

#include <wx/string.h>

class GNRAssembly
{
public:
	GNRAssembly();
	virtual ~GNRAssembly();
	
protected:

private:
	// stores the offset of the x-axis relative to the zero-point
	float m_xOffset;
	
	// stores the offset of the y-axis relative to the zero-point
	float m_yOffset;
	
	// stores the offset of the z-axis relative to the zero-point
	float m_zOffset;
	
	// stores the rotation relative to the x-asis
	float m_phi;
	
	// stores the rotation relative to the y-axis
	float m_theta;
	
	// stores the rotation relative to the z-axis
	float m_rho;
	
	// stores the groupid
	unsigned int m_groupid;
	
	// stores the MD5-Hash of the content of the .obj-File
	wxString m_MD5Hash;
};

#endif // _GNRASSEMBLY_H_
