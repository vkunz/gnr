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

#include "GNREnum.h"
#include "GNRFace.h"
#include "GNRVertex.h"

using std::list;
using std::vector;
using std::string;

class GNRAssembly
{
public:

	GNRAssembly(const string& name);
	GNRAssembly(GNRAssembly* parent, const string &name);
	GNRAssembly(const assemblyType& type, const string& name);
	
	virtual ~GNRAssembly();
	
	float getX() const;
	float getY() const;
	float getZ() const;
	
	float getHeight() const;
	float getWidth() const;
	float getDepth() const;
	float getMaximumSize() const;
	GNRVertex& GNRAssembly::getCenterVertex() const;
	
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setXY(const float x,const float y);
	void setXZ(const float x,const float z);
	void setXYZ(const float x, const float y, const float z);
	void setCenterVertex(const GNRVertex& center);
	
	void setHeight(const float height);
	void setWidth(const float width);
	void setDepth(const float depth);
	void setSize(const float width,const float height,const float depth);
	
	float getPhi() const;
	float getRho() const;
	float getTheta() const;
	
	void setPhi(const float phi);
	void setRho(const float rho);
	void setTheta(const float theta);
	void setPhiTheta(const float phi,const float theta);
	void setPhiRho(const float phi,const float rho);
	
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;
	
	void setScaleX(const float x);
	void setScaleY(const float y);
	void setScaleZ(const float z);
	void setScale(const float x,const float y,const float z);
	
	void addFace(const GNRFace& newface);
	void addPart(GNRAssembly* part);
	void delPart(GNRAssembly* part);
	
	void setName(const string& name);
	const string& getName() const;
	
	void setType(const assemblyType& type);
	assemblyType getType() const;
	bool isType(const assemblyType& type);
	
	GNRAssembly* getParent() const;
	GNRAssembly* getMaster() const;
	void setParent(GNRAssembly* p);
	
	float getOverGround() const;
	void putOnGround();
	void setNormals();
	
	void draw() const;
	void debugInfo() const;
	list<GNRAssembly*> getPartList();
	
private:

	float m_x, m_y, m_z;
	float m_phi, m_theta, m_rho;
	float m_scale_x, m_scale_y, m_scale_z;
	float m_width, m_height, m_depth;
	assemblyType m_type;
	string m_name;
	
	GNRAssembly* m_parent;
	
	list<GNRFace> m_face;
	list<GNRAssembly*> m_part;
};

#endif // _GNRASSEMBLY_H_
