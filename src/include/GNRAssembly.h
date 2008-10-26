/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRAssembly
 * @name                GNRAssembly.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRASSEMBLY_H_
#define _GNRASSEMBLY_H_

#include <list>
#include <vector>
#include <string>

#include "GNRFace.h"
#include "GNRVertex.h"
#include "GNRTCoord.h"

using std::list;
using std::vector;
using std::string;

class GNRAssembly
{
public:
	GNRAssembly();
	GNRAssembly(const string &name);
	
	virtual ~GNRAssembly();
	
	float getX() const;
	float getY() const;
	float getZ() const;
	
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	float getPhi() const;
	float getRho() const;
	float getTheta() const;
	
	void setPhi(float phi);
	void setRho(float rho);
	void setTheta(float theta);
	
	float getScale() const;
	
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;
	
	void setScale(float s);
	
	void setScaleX(float x);
	void setScaleY(float y);
	void setScaleZ(float z);
	
	void setOverGround(const float overground);
	
	void addFace(const GNRFace& newface);
	void addPart(GNRAssembly* p_part);
	
	void setName(const string& name);
	const string& getName() const;
	
	bool getIsRoot() const;
	void setIsRoot(bool isroot);
	float getOverGround();
	
	const GNRAssembly* getParent() const;
	void setParent(GNRAssembly* p);
	
	void setNormals();
	
	void draw() const;
	
private:

	float m_x, m_y, m_z;
	float m_overground;
	float m_phi, m_theta, m_rho;
	float m_scale;
	float m_scaleX, m_scaleY, m_scaleZ;
	
	bool m_locked, m_isWall, m_isroot;
	string m_name;
	
	list<GNRFace> m_face;
	
	GNRAssembly* m_parent;
	list<GNRAssembly*> m_part;
};

#endif // _GNRASSEMBLY_H_
