/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssembly
 * @name        GNRAssembly.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

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
	std::list<GNRAssembly*> m_parts;
	
	// stores the faces
	std::list<GNRFace> m_faces;
	
	// stores the AssemblyID
	int m_AssemblyID;
};

#endif // _GNRASSEMBLY_H_
