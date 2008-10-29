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
#include <GL/glu.h>

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
	void getPosition(GNRVertex& result) const;
	
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(const GNRVertex& pos);
	
	float getPhi() const;
	float getRho() const;
	float getTheta() const;
	
	
	void setPhi(float phi);
	void setRho(float rho);
	void setTheta(float theta);
	
	float getGroupX() const;
	float getGroupY() const;
	float getGroupZ() const;
	
	void setGroupX(float x);
	void setGroupY(float y);
	void setGroupZ(float z);
	
	float getGroupPhi() const;
	float getGroupRho() const;
	float getGroupTheta() const;
	
	void setGroupPhi(float phi);
	void setGroupRho(float rho);
	void setGroupTheta(float theta);
	
	float getScale() const;
	
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;
	
	void setScale(float s);
	
	void setScaleX(float x);
	void setScaleY(float y);
	void setScaleZ(float z);
	
	void setOverGround(const float overground);
	
	void addPart(GNRAssembly* p_part);
	
	void setName(const string& name);
	const string& getName() const;
	
	float getOverGround();
	
	void setLocked(bool locked);
	bool getLocked() const;
	
	const GNRAssembly* getParent() const;
	void setParent(GNRAssembly* p);
	
	void draw();
	
protected:
	void draw_children();
	void virtual genDL();
	
	float m_x, m_y, m_z;
	float m_overground;
	
	float m_phi, m_theta, m_rho;
	
	float m_scale;
	float m_scaleX, m_scaleY, m_scaleZ;
	
	bool m_Locked, m_Wall, m_Visible;
	string m_name;
	
	GNRAssembly* m_parent;
	list<GNRAssembly*> m_part;
	
	bool m_DL_valid;
	int m_DL_id;
	
	unsigned m_at_depth;
};

#endif // _GNRASSEMBLY_H_
