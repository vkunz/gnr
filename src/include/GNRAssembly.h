#ifndef _GNRASSEMBLY_H_
#define _GNRASSEMBLY_H_

#include <list>
#include <string>

#include "GNRFace.h"
#include "GNRVertex.h"

class GNRAssembly
{
public:
	GNRAssembly();
	virtual ~GNRAssembly();
	
protected:

private:
	// stores the AssemblyTitle
	std::string m_AssemblyTitle;
	
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
	
	// stores the MD5-Hash of the content of the .obj-File
	std::string m_MD5Hash;
	
	// stores the subordinates
	std::list<GNRAssembly> m_LAssembly;
	
	// stores the faces
	std::list<GNRFace> m_LFace;
	
	// stores the normales
	std::list<GNRVertex> m_LNormales;
	
	// stores the vertex
	std::list<GNRVertex> m_LVertex;
	
	// stores the AssemblyID
	int m_AssemblyID;
};

#endif // _GNRASSEMBLY_H_
